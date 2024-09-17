from imutils.video import VideoStream
import argparse
import datetime
import imutils
import time
import cv2

ap = argparse.ArgumentParser()

ap.add_argument("-v", "--video", help="path to the video file")
ap.add_argument("-a", "--min-area", type=int, default=500, help="minium area size")
args = vars(ap.parse_args())

if args.get("video", None) is None:
    vs = VideoStream(src=0).start()
    time.sleep(2.0)

else : vs = cv2.videoCapture(args["video"])

firstFrame = None
noMovementCount = 0

while True:
    frame = vs.read()
    frame = frame if args.get("video", None) is None else frame[1]
    text = "Sin Movimiento"

    if frame is None :  break

    # cambiar el frame a escala de grises y desenfocarlo
    frame = imutils.resize(frame, width=500)
    gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
    gray = cv2.GaussianBlur(gray, (21,21), 0)

    if firstFrame is None:
        firstFrame = gray
        continue

    # saca la diferencia absoluta entre el frame actual y el primer frame
    frameDelta = cv2.absdiff(firstFrame, gray)
    thresh = cv2.threshold(frameDelta, 25, 255, cv2.THRESH_BINARY)[1]
    
    thresh = cv2.dilate(thresh, None, iterations=2)
    cnts = cv2.findContours(thresh.copy(), cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)
    cnts = imutils.grab_contours(cnts)

    movementDetected = False

    for c in cnts:
        if cv2.contourArea(c)  < args["min_area"]:
            continue
        (x, y, w, h) = cv2.boundingRect(c)
        cv2.rectangle(frame, (x, y), (x + w, y + h), (0, 255, 0), 2)
        text = "Movimiento"
        movementDetected = True

    # Si no se detecta movimiento durante 100 cuadros, se actualiza el primer frame
    if not movementDetected:
        noMovementCount += 1
    else:
        noMovementCount = 0

    if noMovementCount >= 100:  # Actualizar el `firstFrame` después de 100 cuadros sin movimiento
        firstFrame = gray
        noMovementCount = 0  # Reiniciar el contador

    cv2.putText(frame, "Status: {}".format(text), (10, 20), cv2.FONT_HERSHEY_SIMPLEX, 0.5, (0, 0, 255), 2)
    cv2.putText(frame, datetime.datetime.now().strftime("%A %d %B %Y %I:%M:%S%p"), (10, frame.shape[0] - 10), 
                cv2.FONT_HERSHEY_SIMPLEX, 0.35, (0, 0, 255), 1)

    cv2.imshow("Security Feed", frame)
    cv2.imshow("Thresh", thresh)
    cv2.imshow("Frame Delta", frameDelta)
    key = cv2.waitKey(1) & 0xFF

    if key == ord("q"):
        break

vs.stop() if args.get("video", None) is None else vs.release()
cv2.destroyAllWindows()