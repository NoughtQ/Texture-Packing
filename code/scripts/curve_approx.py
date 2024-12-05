import matplotlib.pyplot as plt
import numpy as np

plt.rc("font", family="Noto Serif SC", size=13, weight="bold")          # Set one of my favorite fonts

size = [1000, 2000, 4000, 6000, 8000, 10000]                             # Item size(x axis)
BLRatio = [1.7505, 1.5405, 1.5969, 1.6438, 1.4148, 1.4156]
FFDHRatio = [1.2540, 1.2675, 1.3949, 1.1423, 1.1959, 1.1470]

  
plt.figure(figsize=(12, 6))                                             # Set the window size
plt.ticklabel_format(style='plain')
plt.title("Approximation Ratio Tests with Diffrent Widths", weight="bold", size=25)   # Title
plt.xlabel("Widths", weight="bold", size=15)                   # X label
plt.ylabel("Approximation Ratio", weight="bold", size=15)                       # Y label
plt.grid(linewidth=0.7)                                                 # Set grids in the diagram
plt.xlim(0, 10500)                                                     # X range
plt.ylim(1, 2)                                                         # Y range

# Adjust the position of axes
ax = plt.gca()
ax.spines['top'].set_visible(False)
ax.spines['right'].set_visible(False)
ax.minorticks_on()
ax.grid(which='minor', color='gray', linestyle=':', linewidth=0.5)

for x_, y_ in zip(size, BLRatio):                                          # Set the text on the data points
    plt.text(x_, y_, f"({x_}, {y_})", ha="right", va="bottom", color='blue', size=8)

for x_, y_ in zip(size, FFDHRatio):                                          # Set the text on the data points
    plt.text(x_, y_, f"({x_}, {y_})", ha="right", va="bottom", color='red', size=8)


# Draw the fitting curve and the actual data points
plt.plot(size, BLRatio, color='green', label='BL Algorithm')
plt.scatter(size, BLRatio, color='blue')
plt.plot(size, FFDHRatio, '--', color='orange', label='FFDH Algorithm')
plt.scatter(size, FFDHRatio, marker='x', color='red')

plt.legend()
plt.savefig('../../documents/images/approx_width.png')     # Save the diagram as a PNG image

plt.show()                                                 # Show the diagram!
