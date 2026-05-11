import serial
import csv
import time
import os
from datetime import datetime

## Configuration de la connection Serial avec Arduino

SERIAL_PORT = "/dev/ttyUSB0"
BAUD_RATE = 115200
CSV_FILENAME = f"vitesse_moteur_{datetime.now().strftime('%Y%m%d_%H%M%S')}.csv"

print(f"Connection au port: {SERIAL_PORT}, à {BAUD_RATE} baud ...")
print(f"Données sauvegardées dans: {CSV_FILENAME}")

## Connection à Arduino et lecture des données

try:
    ser = serial.Serial(SERIAL_PORT, BAUD_RATE, timeout=1)
    time.sleep(2) # Attendre que l'Arduino reinitialize

    with open(CSV_FILENAME, 'w', newline='') as csvfile:
        writer = csv.writer(csvfile)
        writer.writerow(['timestamp', 'duty_cycle', 'speed_mps'])

        print("Début de la collecte. Pressez Ctrl+C pour arrêter ...\n")

        while True:
            if ser.in_waiting > 0:
                line = ser.readline().decode('utf-8').strip()

                if line and ',' in line:
                    try:
                        duty_str, speed_str = line.split(',')
                        duty_cycle = int(duty_str.strip())
                        speed_mps = float(speed_str.strip())

                        timestamp = datetime.now().strftime('%H:%M:%S.%f')[:-3]

                        # Écriture du fichier CSV
                        with open(CSV_FILENAME, 'a', newline='') as csvfile:
                            writer = csv.writer(csvfile)
                            writer.writerow([timestamp, duty_cycle, round(speed_mps, 4)])

                            # Afficher la donnée collectée dans le terminal
                            print(f"{timestamp} | Duty: {duty_cycle:3d} | Speed: {speed_mps:.4f} m/s")

                    except ValueError:
                        pass # Ne pas considérer les données malformées

except serial.SerialException:
    print(f"Je n'arrive pas à me connecter au port : {SERIAL_PORT}. Vérifiez la connexion et le nom du port.")
    print(f"Exécutez: ls /dev/tty* dans le terminal pour voir tous les ports")

except KeyboardInterrupt:
    print("\n\n Collect des données arrêtée par l'utilisateur.")
    print(f"Données sauvegardées dans : {CSV_FILENAME}")

finally:
    if 'ser' in locals() and ser.is_open:
        ser.close()
