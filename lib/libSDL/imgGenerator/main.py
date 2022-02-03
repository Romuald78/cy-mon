from PIL import Image

COLS = 67 * 2
ROWS = 18 * 2

im1 = Image.open("Pyrogen.png")
w,h = im1.size
ratio = max(w/COLS, h/ROWS)

im1 = im1.resize( (int(w/ratio),int(h/ratio)) )
im1.save("Pyrogen_small.png")
im1.close()
