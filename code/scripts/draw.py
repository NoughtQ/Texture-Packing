import matplotlib
matplotlib.use('Agg')
import matplotlib.pyplot as plt
import matplotlib.patches as patches

# 读取文件并解析数据
def read_rectangles_from_file(file_path):
    rectangles = []
    with open(file_path, 'r') as file:
        canvas_width = float(file.readline().strip())
        for line in file:
            parts = line.strip().split()
            x, y, width, height = map(float, parts)
            rectangles.append((x, y, width, height))
    return rectangles,canvas_width

# 绘制矩形
def draw_rectangles(rectangles,canvas_width,output_file):
    fig, ax = plt.subplots()

    ax.axvline(x=canvas_width, color='b', linestyle='--')
    for x, y, width, height in rectangles:
        rect = patches.Rectangle((x, y), width, height, linewidth=1, edgecolor='k', facecolor='g')
        ax.add_patch(rect)

    # 设置坐标轴的显示范围
    x_coords = [x for x, y, width, height in rectangles] + [x + width for x, y, width, height in rectangles]
    y_coords = [y for x, y, width, height in rectangles] + [y + height for x, y, width, height in rectangles]
    ax.axhline(y=max(y_coords), color='r', linestyle='--')
    ax.text(canvas_width + 0.5, max(y_coords), f'{max(y_coords):.2f}', color='r', va='center')
    ax.text(canvas_width + 0.5, 0, f'{canvas_width}', color='b', va='center')
    ax.set_xlim(min(x_coords), max(max(x_coords),canvas_width+1))
    ax.set_ylim(min(y_coords), max(y_coords)*1.05)

    plt.savefig(output_file, bbox_inches='tight', dpi=300)  # 保存图片到文件

for i in range(0, 2):
    # 文件路径
    file_path = f'fig/recs/rectangles{i}.txt'
    output_file = f'fig/fig{i}.png'

    # 读取数据并绘制
    rectangles,width = read_rectangles_from_file(file_path)
    draw_rectangles(rectangles,width,output_file)
