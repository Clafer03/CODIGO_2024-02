import time
import datetime as dt
import pywhatkit as pwk
import pandas as pd
import pyautogui
from selenium import webdriver
from selenium.webdriver.chrome.options import Options
from selenium.webdriver.support.ui import WebDriverWait
from selenium.webdriver.support import expected_conditions as EC
from selenium.webdriver.common.by import By
from selenium.webdriver.common.action_chains import ActionChains

def descargar_archivos():
    # Configuración de Selenium
    driver_path = r'D:\comedriver\chromedriver.exe'
    options = Options()
    options.add_argument("--disable-notifications")
    options.binary_location = r"C:\Program Files\Google\Chrome\Application\chrome.exe"
    options.add_argument(f"chromedriver.exe={driver_path}")

    # Inicializar el controlador de Selenium
    driver = webdriver.Chrome(options=options)

    url = 'https://www.plandeobras.com/obra2.0/login'
    driver.get(url)
    time.sleep(5)

    usuario = "grodriguez"  #b5c34048ab6942b34aa011fe162cbdfc
    contraseña = "Grodriguezz9"  #2f810254b138c12ac019be4d3ad8d067

    username = WebDriverWait(driver, 20).until(EC.element_to_be_clickable((By.XPATH, "//input[@id='username']")))
    password = WebDriverWait(driver, 20).until(EC.element_to_be_clickable((By.XPATH, "//input[@id='password']")))
    username.clear()
    password.clear()
    username.send_keys(usuario)
    password.send_keys(contraseña)

    login_button = WebDriverWait(driver, 20).until(EC.element_to_be_clickable((By.CSS_SELECTOR, "#btnLoginAdminPass")))
    ActionChains(driver).move_to_element(login_button).click().perform()

    #alternativa 1
    tarjeta1 = WebDriverWait(driver, 20).until(EC.element_to_be_clickable((By.XPATH, "//a[@href='getPanel']")))
    ActionChains(driver).move_to_element(tarjeta1).click().perform()
    #alternativa2
    # pyautogui.press("tab", presses=2, interval=1)

    mod_po = WebDriverWait(driver, 20).until(EC.element_to_be_clickable((By.XPATH, "//a[normalize-space()='Módulos - PO']")))
    ActionChains(driver).move_to_element(mod_po).click().perform()

    mod_despliegue_f = WebDriverWait(driver, 20).until(EC.element_to_be_clickable((By.CSS_SELECTOR, "img[src='https://www.plandeobras.com/obra2.0/public/img/iconsSistem/paquetizado.jpg']" )))
    ActionChains(driver).move_to_element(mod_despliegue_f).click().perform()
    time.sleep(2)

    nav_bar = WebDriverWait(driver, 20).until(EC.element_to_be_clickable((By.XPATH, "//div[@class='navigation-trigger']")))
    ActionChains(driver).move_to_element(nav_bar).click().perform()
    time.sleep(2)

    nav_reportes = WebDriverWait(driver, 20).until(EC.element_to_be_clickable((By.XPATH, "//a[normalize-space()='Reportes']")))
    ActionChains(driver).move_to_element(nav_reportes).click().perform()

    nav_exrtactor = WebDriverWait(driver, 20).until(EC.element_to_be_clickable((By.XPATH, "//a[normalize-space()='Extractor']")))
    ActionChains(driver).move_to_element(nav_exrtactor).click().perform()
    time.sleep(2)

    mod_online = WebDriverWait(driver, 20).until(EC.element_to_be_clickable((By.XPATH, "//a[normalize-space()='Online']")))
    ActionChains(driver).move_to_element(mod_online).click().perform()
    time.sleep(2)

    dwl_sisego = WebDriverWait(driver, 20).until(EC.element_to_be_clickable((By.XPATH, "//a[@href='generar_excelCvSisego']//img")))
    ActionChains(driver).move_to_element(dwl_sisego).click().perform()
    time.sleep(120)

try:
    descargar_archivos()
except:
    message = "HUB LEAN :\n STATUS: FAILED 💀"
    pwk.sendwhatmsg_instantly("+51964695238", message, 10, tab_close=True)