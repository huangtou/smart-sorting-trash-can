from maix import uart,time,app,camera, display, image, nn
import struct
import math
detector = nn.YOLOv5(model="/root/models/model_167094.mud", dual_buff = True)
cam = camera.Camera(detector.input_width(), detector.input_height(), detector.input_format())
dis = display.Display()
device = "/dev/ttyS0"
serial = uart.UART(device, 9600)

def sending_data(type1,x,y,n):    #发送函数
    global uart
    data = struct.pack("<bbhhhhb",  
                   0x2C,
                   0x2E,
                   int(type1),
                   int(x),
                   int(y),
                   int(n),
                   0x5B)
    serial.write(data)
def slopee(x1,y1,x2,y2):
    x = (y2 - y1) / (x2 - x1)
    return x

def calculate_angle(p1, p2, y_axis_down=True):
    dx = p2[0] - p1[0]
    dy = p2[1] - p1[1] if not y_axis_down else p1[1] - p2[1]  # 处理Y轴方向
    theta_rad = math.atan2(dy, dx)
    theta_deg = math.degrees(theta_rad)
    theta_deg = theta_deg % 360
    return theta_deg

while not app.need_exit():
    img = cam.read()
    objs = detector.detect(img, conf_th = 0.5, iou_th = 0.45)
    for obj in objs:
        img.draw_rect(obj.x, obj.y, obj.w, obj.h, color = image.COLOR_RED)
        msg = f'{detector.labels[obj.class_id]}: {obj.score:.2f}'
        img.draw_string(obj.x, obj.y, msg, color = image.COLOR_RED)
        pointx=int(obj.x+obj.w/2)
        pointy=int(obj.y+obj.h/2)
        img.draw_cross(pointx,pointy, image.Color.from_rgb(255, 0, 0), size=5, thickness=1)

        P1=(obj.x,obj.y)
        P2=(obj.x+obj.w,obj.y+obj.h)
        angle=calculate_angle(P1,P2)
        print(angle)
        time.sleep_ms(60)

        #print(obj.class_id)
        #电池0 易拉罐1 石头2 胡萝卜3,id-1
        receive=serial.read()
        #print(receive)
        if receive:
            if obj.class_id==0:
                sending_data(1,0,0,0)
            elif obj.class_id==1:
                sending_data(2,0,0,0)
            elif obj.class_id==2:
                sending_data(3,0,0,0)#bu
            elif obj.class_id==3:
                sending_data(4,0,0,0)

            #sending_data(1,2,3,4)
            time.sleep_ms(60)
            receive=0
        else:
            pass
    dis.show(img)









