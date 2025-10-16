import sys
import numpy as np
from PIL import Image

# Contrast on a scale -10 -> 10
contrast = 10
density = ('$@B%8&WM#*oahkbdpqwmZO0QLCJUYXzcvunxrjft/\|'
           '()1{}[]?-_+~<>i!lI;:,"^`\'.            ')
density = density[:-11+contrast]
n = len(density)

img_name = sys.argv[1]
try:
    width = int(sys.argv[2])
except IndexError:
    # Default ASCII image width.
    width = 100

# Read in the image, keep original colors and create greyscale version.
img = Image.open(img_name)
img_rgb = img.convert('RGB')  # Keep original colors
img_gray = img.convert('L')   # Greyscale for brightness calculation
# Resize both images as required.
orig_width, orig_height = img.size
r = orig_height / orig_width
# The ASCII character glyphs are taller than they are wide. Maintain the aspect
# ratio by reducing the image height.
height = int(width * r * 0.5)
img_rgb = img_rgb.resize((width, height), Image.LANCZOS)
img_gray = img_gray.resize((width, height), Image.LANCZOS)

# Function to convert RGB to ANSI color code
def rgb_to_ansi(r, g, b):
    """Convert RGB values to ANSI 256-color escape sequence"""
    return f"\033[38;2;{r};{g};{b}m"

def reset_color():
    """Reset color to default"""
    return "\033[0m"

# Now map the pixel brightness to the ASCII density glyphs with colors.
arr_gray = np.array(img_gray)  # For brightness calculation
arr_rgb = np.array(img_rgb)    # For color information

for i in range(height):
    for j in range(width):
        # Get brightness from grayscale image
        p = arr_gray[i,j]
        k = int(np.floor(p/256 * n))
        
        # Get RGB color from original image
        r, g, b = arr_rgb[i,j]
        
        # Apply color and print ASCII character
        color_code = rgb_to_ansi(r, g, b)
        ascii_char = density[n-1-k]
        print(f"{color_code}{ascii_char}{reset_color()}", end='')
    print()