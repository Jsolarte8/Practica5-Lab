import pandas as pd
import matplotlib.pyplot as plt
from matplotlib.patches import Rectangle
import os

archivo_simulacion = "salida_simulacion.txt"
archivo_obstaculos = "obstaculos_simulacion.txt"

if not os.path.exists(archivo_simulacion):
    print("No se encontro salida_simulacion.txt. Ejecuta primero el programa C++.")
    exit()

datos = pd.read_csv(archivo_simulacion)

plt.figure(figsize=(9, 7))

for pid in sorted(datos["id"].unique()):
    datos_p = datos[datos["id"] == pid]
    plt.plot(
        datos_p["x"],
        datos_p["y"],
        marker="o",
        markersize=2,
        linewidth=1,
        label=f"Particula {pid}"
    )

ax = plt.gca()

if os.path.exists(archivo_obstaculos):
    obstaculos = pd.read_csv(archivo_obstaculos)
    for _, obs in obstaculos.iterrows():
        rect = Rectangle(
            (obs["x"], obs["y"]),
            obs["ancho"],
            obs["alto"],
            fill=True,
            alpha=0.25
        )
        ax.add_patch(rect)
        plt.text(
            obs["x"] + obs["ancho"] / 2,
            obs["y"] + obs["alto"] / 2,
            f"O{int(obs['id'])}",
            ha="center",
            va="center"
        )

plt.title("Trayectorias de particulas con colisiones")
plt.xlabel("x")
plt.ylabel("y")
plt.grid(True)
plt.legend()
plt.gca().invert_yaxis()
plt.axis("equal")
plt.show()