import matplotlib.pyplot as plt
import numpy as np

plt.rc("font", family="Noto Serif SC", size=13, weight="bold")          # Set one of my favorite fonts

size = [10,50, 100,500, 1000,5000, 10000]                             # Item size(x axis)
time = [0.00029159,0.000112231,0.0004264,0.001882206,0.006107088,0.0226485,0.0588621]      # Running time(y axis)

 

plt.figure(figsize=(12, 6))                                             # Set the window size
plt.ticklabel_format(style='plain')
plt.title("Curve Diagram for FFDH Algorithm", weight="bold", size=25)   # Title
plt.xlabel("Number of Items", weight="bold", size=15)                   # X label
plt.ylabel("Duration(s)", weight="bold", size=15)                       # Y label
plt.grid(linewidth=0.7)                                                 # Set grids in the diagram
plt.xlim(0, 180000)                                                     # X range
plt.ylim(0, 12)                                                         # Y range

# Adjust the position of axes
ax = plt.gca()
ax.spines['top'].set_visible(False)
ax.spines['right'].set_visible(False)
ax.minorticks_on()
ax.grid(which='minor', color='gray', linestyle=':', linewidth=0.5)

for x_, y_ in zip(size, time):                                          # Set the text on the data points
    plt.text(x_, y_, f"({x_}, {y_})", ha="right", va="bottom", color='blue', size=8)

# Draw the fitting curve(quadratic curve)
x_fit = np.linspace(0, 200000, 100000)
coefficients = np.polyfit(size, time, 2)
y_fit = np.polyval(coefficients, x_fit)

# Mark the equation beside the curve
a, b, c = coefficients
equation = f"y = {a:.2e}·x² + {b:.2e}·x + {c:.2e}"
plt.text(110000, 9, equation, fontsize=15, color='green', ha='center')

# Draw the fitting curve and the actual data points
plt.plot(x_fit, y_fit, color='green')
plt.scatter(size, time, color='blue')

plt.savefig('BL_diagram.png')     # Save the diagram as a PNG image
plt.show()                                                 # Show the diagram!
