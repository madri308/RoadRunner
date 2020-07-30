import os
from cv2 import cv2

def main():
    print("Procesando imagen..")
    RGB_images =  cv2.cvtColor(cv2.imread(r"C:\Users\emema\Documents\TEC\2020\SEM_I\Analisis\RoadRunner\documentation\rutaVacia.png"), cv2.COLOR_BGR2RGB)
    with open(os.path.join(r'C:\Users\emema\Documents\TEC\2020\SEM_I\Analisis\RoadRunner\documentation',"limits.txt"), "w") as output:
        #print("{",file=output)
        for y in range(40,880):
            for x in range(len(RGB_images[0])):
                if RGB_images[y][x][0] < 15:
                    print(str(x)+" "+str(y),file=output)
        #print("}",file=output)
    print("Proceso terminado!")
if __name__ == "__main__":
    main()
        