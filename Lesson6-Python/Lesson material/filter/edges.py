from PIL import Image, ImageFilter

before = Image.open("picture.jpg")
after = before.filter(ImageFilter.FIND_EDGES())
after.save("picture_edges.jpg")