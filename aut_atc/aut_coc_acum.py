import pandas as pd
import numpy as np
import openpyxl}
import os
from io import BytesIO
from datetime import datetime
from ftplib import FTP

def cocAcumulado():
    #DESCARGAR DATA
    # Configuración de la conexión FTP
    ftp = FTP('www.lari.pe')  # Hostname o dirección IP del servidor FTP
    ftp.login(user='rrivero@lari.pe', passwd='RR@7390.*')  # Nombre de usuario y contraseña
    remote_folder_path = '/CONTACTABILIDAD/'
    local_folder_path = "D:\@Perfil\Desktop\proyectos_L\Proyecto Llamadas - ATC\V230824"
    # Cambiar al directorio donde se encuentran los archivos CSV
    ftp.cwd(remote_folder_path)

    # Descargar los archivos CSV en un búfer de memoria
    coc = BytesIO()
    
    try:
        # Descargar el archivo coc.xlsx
        ftp.retrbinary('RETR coc.xlsx', coc.write)
    except Exception as e:
        print(f"Error al descargar el archivo: {e}")
        ftp.quit()
        return

    ftp.quit()  # Terminar la sesión correctamente

    ##########################################################################################################################
    #PROCESAR DATA
    try:
        coc.seek(0)
        df_coc = pd.read_excel(coc)
    except pd.errors.EmptyDataError:
        print("El archivo coc.xlsx está vacío o no contiene datos.")
        return
    except Exception as e:
        print(f"Error al leer el archivo Excel: {e}")
        return

    # Obtener la fecha de hoy en formato DD/MM/YYYY
    today_str = pd.to_datetime("today").strftime("%d/%m/%Y")

    # Juntar todos los valores del cod de req
    df_coc["APPTNUMBER_O"] = np.where(df_coc["APPTNUMBER"] == "", df_coc["CODREQ"], df_coc["APPTNUMBER"])
    
    # Crear ID combinando fecha y APPTNUMBER_O
    df_coc["ID_FR"] = today_str + df_coc["APPTNUMBER_O"].astype(str)
    
    # Crear columna con la fecha actual
    df_coc["fecha"] = today_str

    # Guardar el archivo en la ruta especificada
    try:
        df_coc.to_excel(r"D:\@Perfil\Desktop\proyectos_L\Proyecto Llamadas - ATC\V230824\coc_hoy.xlsx", index=False)
        print("Archivo guardado exitosamente.")
    except Exception as e:
        print(f"Error al guardar el archivo Excel: {e}")

    archivo_acum = "D:\@Perfil\Desktop\proyectos_L\Proyecto Llamadas - ATC\V230824\coc_acum.xlsx"
    df_acum = pd.read_excel(archivo_acum)
    arhivo_dia =  "D:\@Perfil\Desktop\proyectos_L\Proyecto Llamadas - ATC\V230824\coc_hoy.xlsx"
    df_dia = pd.read_excel(arhivo_dia)

    df_final = pd.concat([df_acum, df_dia])

    df_final.to_excel(archivo_acum)
    print("Data historico guardada.") 

    ##########################################################################################################################
    #GUARDAR DATA EN FTP
    # Obtener la lista de archivos en la carpeta local (excluyendo archivos ocultos)
    file_list = [file for file in os.listdir(local_folder_path) if not file.startswith('.')]
    # Subir cada archivo regular de la carpeta local a la carpeta remota
    print(file_list)

    file = "coc_acum.xlsx"
    for file_name in file_list:
        if file_name == file:
            local_file_path = os.path.join(local_folder_path, file_name)
            remote_file_path = os.path.join(remote_folder_path, file_name)
            with open(local_file_path, 'rb') as file:
                ftp.storbinary(f'STOR {remote_file_path}', file)
        #     Actualizar la carpeta remota después de cada transferencia de archivo
            ftp.dir(remote_folder_path)
    # Cerrar la conexión FTP
    ftp.quit()

cocAcumulado()
