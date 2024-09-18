from imutils.video import VideoStream
import argparse
import datetime
import imutils
import time
import cv2

# Argument parser para pasar argumentos de línea de comandos (video y área mínima)
ap = argparse.ArgumentParser()

# Argumento opcional para el video de entrada
ap.add_argument("-v", "--video", help="path to the video file")
# Argumento opcional para el tamaño mínimo del área que se considerará como movimiento
ap.add_argument("-a", "--min-area", type=int, default=500, help="minimum area size")
# Parsear los argumentos de línea de comandos y convertirlos a un diccionario
args = vars(ap.parse_args())

# Si no se proporciona un archivo de video, se usa la cámara web como fuente de video
if args.get("video", None) is None:
    vs = VideoStream(src=0).start()  # Iniciar la transmisión desde la cámara web
    time.sleep(2.0)  # Esperar un momento para que la cámara se inicialice

# Si se proporciona un archivo de video, se usa como fuente de video
else:
    vs = cv2.VideoCapture(args["video"])

# Inicializar el primer frame para poder calcular las diferencias con el tiempo
firstFrame = None
# Contador de cuadros estáticos sin movimiento
staticFrames = 0
# Umbral de cuadros consecutivos sin movimiento para actualizar el frame inicial
staticThreshold = 50

# Bucle principal para procesar los cuadros del video
while True:
    frame = vs.read()  # Leer el cuadro actual del video
    # Si estamos leyendo de la cámara, el frame será directamente 'frame', si es de un archivo será 'frame[1]'
    frame = frame if args.get("video", None) is None else frame[1]
    text = "Sin Movimiento Detectado"  # Estado inicial, sin movimiento detectado

    # Si no hay más cuadros (por ejemplo, fin del video), salir del bucle
    if frame is None:
        break

    # Redimensionar el frame para que todos los cuadros tengan el mismo tamaño
    frame = imutils.resize(frame, width=500)
    # Convertir el frame a escala de grises para simplificar el análisis
    gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
    # Desenfocar la imagen para reducir el ruido y detalles irrelevantes
    gray = cv2.GaussianBlur(gray, (21, 21), 0)

    # Si aún no se ha establecido el primer frame, usar el actual como referencia
    if firstFrame is None:
        firstFrame = gray
        continue  # Saltar al siguiente cuadro

    # Calcular la diferencia entre el primer frame y el frame actual (diferencia absoluta)
    frameDelta = cv2.absdiff(firstFrame, gray)
    # Aplicar un umbral binario para resaltar las áreas con suficiente diferencia
    thresh = cv2.threshold(frameDelta, 25, 255, cv2.THRESH_BINARY)[1]
    
    # Dilatar el umbral para llenar los agujeros y hacer más visibles las áreas en movimiento
    thresh = cv2.dilate(thresh, None, iterations=2)
    # Encontrar los contornos de las áreas que han cambiado
    cnts = cv2.findContours(thresh.copy(), cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)
    cnts = imutils.grab_contours(cnts)  # Convertir los contornos en una lista de contornos

    movementDetected = False  # Variable para indicar si se detecta movimiento

    # Recorrer todos los contornos detectados
    for c in cnts:
        # Si el área del contorno es menor que el área mínima establecida, ignorarlo
        if cv2.contourArea(c) < args["min_area"]:
            continue
        # Calcular el cuadro delimitador (bounding box) para el contorno
        (x, y, w, h) = cv2.boundingRect(c)
        # Dibujar un rectángulo verde alrededor del área en movimiento
        cv2.rectangle(frame, (x, y), (x + w, y + h), (0, 0, 255), 2)  # Color rojo en formato RGB
        text = "Movimiento Detectado"  # Cambiar el texto para indicar que hay movimiento
        movementDetected = True  # Indicar que se ha detectado movimiento

    # Si no se ha detectado movimiento en este cuadro, incrementar el contador de cuadros estáticos
    if not movementDetected:
        staticFrames += 1
    else:
        staticFrames = 0  # Reiniciar el contador si se detecta movimiento

    # Si ha pasado un umbral de cuadros sin movimiento, actualizar el primer frame
    if staticFrames >= staticThreshold:
        firstFrame = gray  # Establecer el frame actual como nuevo frame de referencia
        staticFrames = 0  # Reiniciar el contador de cuadros estáticos

    # Dibujar el estado del movimiento (con o sin movimiento) en la parte superior izquierda del frame
    cv2.putText(frame, "Status: {}".format(text), (10, 20), cv2.FONT_HERSHEY_SIMPLEX, 0.5, (0, 0, 255), 2)
    # Dibujar la fecha y la hora en la parte inferior izquierda del frame
    cv2.putText(frame, datetime.datetime.now().strftime("%A %d %B %Y %I:%M:%S%p"), (10, frame.shape[0] - 10), 
                cv2.FONT_HERSHEY_SIMPLEX, 0.35, (0, 0, 255), 1)

    # Mostrar el feed de la cámara con los rectángulos dibujados
    cv2.imshow("Security Feed", frame)
    # Mostrar el umbral binarizado
    cv2.imshow("Thresh", thresh)
    # Mostrar la diferencia entre el primer frame y el frame actual
    cv2.imshow("Frame Delta", frameDelta)

    # Esperar 1 milisegundo para revisar si se ha presionado una tecla
    key = cv2.waitKey(1) & 0xFF

    # Si se presiona la tecla 'q', salir del bucle
    if key == ord("q"):
        break

# Detener la transmisión de video si estamos usando la cámara, o liberar el archivo de video
vs.stop() if args.get("video", None) is None else vs.release()
# Cerrar todas las ventanas abiertas de OpenCV
cv2.destroyAllWindows()
