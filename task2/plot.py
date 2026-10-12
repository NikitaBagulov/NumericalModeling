import matplotlib.pyplot as plt
import pandas as pd
import numpy as np

# Исходные графики
df = pd.read_csv("results.csv").sort_values(by="x").reset_index(drop=True)
df.columns = ["x", "h", "f_x"]

fig, (ax1, ax2) = plt.subplots(2, 1, figsize=(10, 8), sharex=True)

ax1.plot(df["x"], df["f_x"], color="blue", label="f(x)", zorder=1)
ax1.scatter(df["x"], df["f_x"], color="crimson", s=20, label="points", zorder=2)
ax1.set_title("Function with adaptive integration grid")
ax1.set_ylabel("f(x)")
ax1.grid(True, linestyle="--")
ax1.legend()

ax2.plot(df["x"], df["h"], "o-", color="purple", ms=4)
ax2.set_title("Step size distribution")
ax2.set_xlabel("X")
ax2.set_ylabel("Step size (h)")
ax2.grid(True, linestyle="--")

plt.tight_layout()
plt.savefig("result.png")
plt.show()

df_eps = pd.read_csv("eps_vs_speed.csv")
df_parts = pd.read_csv("parts.csv")

fig, (ax1, ax2) = plt.subplots(1, 2, figsize=(15, 6))

ax1.plot(df_eps["eps"], df_eps["steps"], "o-",
         color="teal", linewidth=2, label="Number of steps")

ax1.set_xscale("log")
# ax1.set_yscale("log")
ax1.invert_xaxis()

ax1.set_title("Integration  vs accuracy")
ax1.set_xlabel("Eps")
ax1.set_ylabel("Steps")
ax1.grid(True, which="both", linestyle="--")
ax1.legend()

ax2.plot(df_parts["parts"], df_parts["error"], "o-",
         color="darkorange", ms=4, label="Absolute error")

ax2.set_title("Integration error vs parts")
ax2.set_xlabel("N")
ax2.set_ylabel("Absolute error")
ax2.grid(True, linestyle="--")
ax2.legend()


plt.tight_layout()
plt.savefig("integration_analysis.png")
plt.show()