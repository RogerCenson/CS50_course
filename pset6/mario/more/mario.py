while 1:
    # Get Height
    height = input("Height: ")
    if height.isdigit():
        height = int(height)
        if height >= 1 and height <= 8:
            break
# Numeber of lines
for ii in range(height):
    # Maximum number of collouns
    for jj in range( 2 * height + 2):
        # Left part
        if jj >= height - ii - 1 and jj < height:
            print("#", end = "")
        # Right part
        elif jj > height + 1 and jj <= height + ii + 2:
            print("#", end = "")
        else:
        # Blanck parts
            print(" ", end = "")
        if jj == height + ii + 2:
        # Next line
            print("")
            break