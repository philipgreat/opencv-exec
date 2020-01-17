import cv2
import numpy as np
import os
from datetime import datetime

font = cv2.FONT_HERSHEY_COMPLEX
print("Current Time =", datetime.now().strftime("%H:%M:%S.%f"))

#imgOrg = cv2.imread("input_02.jpg")
#img = cv2.imread("input_02.jpg", cv2.IMREAD_GRAYSCALE)
img = cv2.imread('input_02.jpg')
img_bw = 255*(cv2.cvtColor(img, cv2.COLOR_BGR2GRAY) > 5).astype('uint8')

se1 = cv2.getStructuringElement(cv2.MORPH_RECT, (5,5))
se2 = cv2.getStructuringElement(cv2.MORPH_RECT, (2,2))
mask = cv2.morphologyEx(img_bw, cv2.MORPH_CLOSE, se1)
mask = cv2.morphologyEx(mask, cv2.MORPH_OPEN, se2)

mask = np.dstack([mask, mask, mask]) / 255
out = img * mask

img = out.copy()

_, threshold = cv2.threshold(img, 240, 255, cv2.THRESH_BINARY)
_, contours, _ = cv2.findContours(threshold, cv2.RETR_TREE, cv2.CHAIN_APPROX_SIMPLE)




for cnt in contours:
    approx = cv2.approxPolyDP(cnt, 0.01*cv2.arcLength(cnt, True), True)
    color = (255,0,255)
    #cv2.drawContours(img, [approx], 0, color, 5)
    rect = cv2.minAreaRect(cnt)
    
    x = approx.ravel()[0]
    y = approx.ravel()[1]
    if len(approx) == 4:
        box = cv2.boxPoints(rect) # cv2.boxPoints(rect) for OpenCV 3.x
        box = np.int0(box)
        cv2.drawContours(img,[box],0,(0,255,255),10)

        cv2.putText(img, "Rectangle", (x, y), font, 1, (255,255,255))

### 

cv2.imwrite('output01.jpg', img) 

print("Current Time =", datetime.now().strftime("%H:%M:%S.%f"))
# List files and directories   
# in 'C:/Users / Rajnish / Desktop / GeeksforGeeks'   
print("Please view the image")   


