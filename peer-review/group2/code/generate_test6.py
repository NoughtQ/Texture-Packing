import random
import os

def generate_test_data(file_name, n, W, H):

    items = []
    total_area = W * H  
    remaining_area = total_area
    
    for i in range(n):
        while True: 
            
            max_width = min(W, remaining_area // (n - len(items)))  

            
            rect_width = random.randint(1, max_width)

            max_height = remaining_area // rect_width
            if i==n:  
                rect_height = max_height  
                break

            rect_height = random.randint(1, max_height)  
            


            if rect_width * rect_height < remaining_area:
                items.append((rect_width, rect_height))
                remaining_area -= rect_width * rect_height
                break  


    with open(file_name, 'w') as f:
        f.write(f"{n} {W}\n")  
        for width, height in items:
            f.write(f"{width} {height}\n")  
    print(f"Test data generated: {file_name}")

if __name__ == "__main__":
    output_dir = "test_cases"
    if not os.path.exists(output_dir):
        os.makedirs(output_dir)

    n = int(input("Enter the number of rectangles (n): "))
    W = int(input("Enter the width of the container (W): "))
    H = int(input("Enter the optimal height of the container (H): "))

    file_name = os.path.join(output_dir, f"test_{n}_{W}_{H}.txt")
    generate_test_data(file_name, n, W, H)
