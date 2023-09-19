# :mind_blown_emoji
from PIL import Image, ImageFilter

before = Image.open("picture.jpg")
after = before.filter(ImageFilter.BoxBlur(3))
after.save("picture_blur.jpg")