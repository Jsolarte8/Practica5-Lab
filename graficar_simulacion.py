from pathlib import Path

import matplotlib.pyplot as plt
import pandas as pd


BASE_DIR = Path(__file__).resolve().parents[1]
RUTA_DATOS = BASE_DIR / "salida_simulacion.txt"
RUTA_OBSTACULOS = BASE_DIR / "obstaculos_simulacion.txt"


def main():
    datos = pd.read_csv(RUTA_DATOS)

    fig, ax = plt.subplots(figsize=(10, 7))

    for pid, grupo in datos.groupby("id"):
        ax.plot(grupo["x"], grupo["y"], linewidth=1.8, label=f"Particula {pid}")
        ax.scatter(grupo["x"].iloc[0], grupo["y"].iloc[0], s=30, marker="o")
        ax.scatter(grupo["x"].iloc[-1], grupo["y"].iloc[-1], s=45, marker="x")

    if RUTA_OBSTACULOS.exists():
        obstaculos = pd.read_csv(RUTA_OBSTACULOS)
        for _, obs in obstaculos.iterrows():
            rect = plt.Rectangle(
                (obs["x"], obs["y"]),
                obs["ancho"],
                obs["alto"],
                fill=True,
                alpha=0.25,
                edgecolor="black",
                facecolor="gray",
            )
            ax.add_patch(rect)
            ax.text(
                obs["x"] + obs["ancho"] / 2,
                obs["y"] + obs["alto"] / 2,
                f"O{int(obs['id'])}",
                ha="center",
                va="center",
                fontsize=9,
            )

    eventos = datos[datos["evento"].fillna("") != ""]
    for _, evento in eventos.iterrows():
        ax.scatter(evento["x"], evento["y"], s=60, marker="*", color="red")

    ax.set_title("Trayectorias de particulas con colisiones")
    ax.set_xlabel("x")
    ax.set_ylabel("y")
    ax.set_xlim(0, 900)
    ax.set_ylim(700, 0)
    ax.set_aspect("equal", adjustable="box")
    ax.grid(True, linestyle="--", alpha=0.4)
    ax.legend(loc="upper right")
    plt.tight_layout()
    plt.show()


if __name__ == "__main__":
    main()
