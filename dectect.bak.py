import cv2
import numpy as np
import os
from datetime import datetime

font = cv2.FONT_HERSHEY_COMPLEX
print("Current Time =", datetime.now().strftime("%H:%M:%S.%f"))

img = cv2.imread("shapes.jpg", cv2.IMREAD_GRAYSCALE)
_, threshold = cv2.threshold(img, 240, 255, cv2.THRESH_BINARY)
_, contours, _ = cv2.findContours(threshold, cv2.RETR_TREE, cv2.CHAIN_APPROX_SIMPLE)




for cnt in contours:
    approx = cv2.approxPolyDP(cnt, 0.01*cv2.arcLength(cnt, True), True)
    cv2.drawContours(img, [approx], 0, (0), 5)
    x = approx.ravel()[0]
    y = approx.ravel()[1]
    if len(approx) == 3:
        cv2.putText(img, "Triangle555", (x, y), font, 1, (0))
    elif len(approx) == 4:
        cv2.putText(img, "23Rectangle", (x, y), font, 1, (0))
    elif len(approx) == 5:
        cv2.putText(img, "Pentagon", (x, y), font, 1, (0))
    elif 6 < len(approx) < 15:
        cv2.putText(img, "Ellipse", (x, y), font, 1, (0))
    else:
        cv2.putText(img, "Circle", (x, y), font, 1, (0))


cv2.imwrite('output.jpg', img) 

print("Current Time =", datetime.now().strftime("%H:%M:%S.%f"))
# List files and directories   
# in 'C:/Users / Rajnish / Desktop / GeeksforGeeks'   
print("Please view the image")   


