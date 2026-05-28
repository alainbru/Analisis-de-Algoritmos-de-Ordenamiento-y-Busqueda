import csv
import random

# CONFIGURACIÓN DE ARCHIVOS
archivo_grande = "datos_apto.csv"     # <-- Pon aquí el nombre exacto de tu archivo de 97k datos
archivo_salida = "muestras_dni_500.csv"     # El archivo nuevo donde se guardarán los 500 DNIs

print("Leyendo el padrón para extraer las muestras... 🕵️‍♂️")

lista_dnis = []

try:
    # Abrimos el archivo grande usando punto y coma como separador
    with open(archivo_grande, mode='r', encoding='utf-8') as f:
        lector = csv.reader(f, delimiter=';')
        
        # Omitimos la cabecera (Nro;Modalidad;DNI...) para no mezclarla con los DNIs
        cabecera = next(lector)
        
        # Recorremos las 97,528 filas y guardamos solo el DNI (está en la columna índice 2)
        for fila in lector:
            if len(fila) >= 3:  # Validación para asegurarnos de que la fila no esté vacía
                dni = fila[2].strip()
                if dni:  # Si el DNI no está en blanco, lo guardamos
                    lista_dnis.append(dni)

    total_datos = len(lista_dnis)
    print(f"¡Éxito! Se cargaron {total_datos} DNIs correctamente.")

    # CONTROL DE SEGURIDAD: Verificar si tenemos suficientes datos
    if total_datos < 500:
        print("⚠️ Alerta: El archivo tiene menos de 500 datos. Seleccionaremos todos los disponibles.")
        cantidad_a_seleccionar = total_datos
    else:
        cantidad_a_seleccionar = 1000

    # LA MAGIA ALEATORIA: 'random.sample' garantiza que NO se repitan los DNIs
    print(f"Seleccionando {cantidad_a_seleccionar} DNIs al azar sin repetir... 🎲")
    dnis_aleatorios = random.sample(lista_dnis, cantidad_a_seleccionar)

    # EXPORTAR AL NUEVO CSV
    with open(archivo_salida, mode='w', newline='', encoding='utf-8') as f_salida:
        escritor = csv.writer(f_salida, delimiter=';')
        
        # Le ponemos una cabecera simple a tu nuevo archivo
        escritor.writerow(["DNI_Buscado"])
        
        # Escribimos los 500 DNIs en filas separadas
        for dni in dnis_aleatorios:
            escritor.writerow([dni])

    print(f"\n¡PROCESO COMPLETADO! 🎉")
    print(f"Se ha creado el archivo '{archivo_salida}' con los 500 DNIs aleatorios.")
    print("¡Ya tienes tu lote de pruebas listo para destrozar los algoritmos de búsqueda!")

except FileNotFoundError:
    print(f"❌ Error: No se encontró el archivo '{archivo_grande}'. Verifica que el nombre esté idéntico.")
except Exception as e:
    print(f"❌ Ocurrió un error inesperado: {e}")