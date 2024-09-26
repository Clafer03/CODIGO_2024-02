import tkinter as tk
from tkinter import messagebox
import time
import threading
import random

def show_alert():
    mensajes = ["hola", "hola2", "hola3", "hola4", "hola5", "hola6"]
    root = tk.Tk()
    root.withdraw()
    root.attributes('-topmost', True)
    root.iconbitmap(r'D:/@Perfil/Pictures/lari_logo.ico')
    messagebox.showinfo("MENSAJE INFORMATIVO", random.choice(mensajes))
    root.destroy()

def start_timer(interval):
    while True:
        time.sleep(interval)
        show_alert()
    
interval_in_hours = 2
interval_in_seconds = interval_in_hours * 3600

t = threading.Thread(target =start_timer, args=(10,))
t.start()
