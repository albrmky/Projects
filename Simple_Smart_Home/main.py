import RPi.GPIO as gpio
import requests
import time
import lcd

Motor = 6
Light = 5

# set the pins for the fan and the light
gpio.setmode(gpio.BCM)
gpio.setup(Motor,gpio.OUT)
gpio.setup(Light,gpio.OUT)

#set the pwm signal
p_motor = gpio.PWM(Motor,50)
p_light = gpio.PWM(Light,50)

lcd.LCD_init(E=17,R_S=22,R_W=27,D7=2,D6=3,D5=4,D4=14,Vo=15)
lcd.LCD_GoToPos(lcd.LINE2,0)
lcd.LCD_DisplayString("F:OFF")
lcd.LCD_GoToPos(lcd.LINE2,9)
lcd.LCD_DisplayString("L:OFF")

p_motor.start(0)
p_light.start(0)

light_high = 60
light_low =30
fan_high = 9
fan_low = 5

while True:
    data = input("enter data: ")
    #data = requests.get("http://noureldeen.pythonanywhere.com/")
    #print(data.text)
    #data = data.text.strip().lower()
    
    print(data)
    
    if data == "turn on the light":
        p_light.ChangeDutyCycle(light_low)
        lcd.LCD_GoToPos(lcd.LINE2,11)
        lcd.LCD_DisplayString("low ")
    elif (data == "turn off the light"):
        p_light.ChangeDutyCycle(0)
        lcd.LCD_GoToPos(lcd.LINE2,11)
        lcd.LCD_DisplayString("off ")
    elif (data == "increase the light"):
        p_light.ChangeDutyCycle(light_high)
        lcd.LCD_GoToPos(lcd.LINE2,11)
        lcd.LCD_DisplayString("high")
    elif (data == "decrease the light"):
        p_light.ChangeDutyCycle(light_low)
        lcd.LCD_GoToPos(lcd.LINE2,11)
        lcd.LCD_DisplayString("low ")
        
    elif (data == "turn on the fan"):
        p_motor.ChangeDutyCycle(fan_low)
        lcd.LCD_GoToPos(lcd.LINE2,2)
        lcd.LCD_DisplayString("slow")
    elif (data == "turn off the fan"):
        p_motor.ChangeDutyCycle(0)
        lcd.LCD_GoToPos(lcd.LINE2,2)
        lcd.LCD_DisplayString("off ")
    elif (data == "increase the fan"):
        p_motor.ChangeDutyCycle(fan_high)
        lcd.LCD_GoToPos(lcd.LINE2,2)
        lcd.LCD_DisplayString("fast")
    elif (data == "decrease the fan"):
        p_motor.ChangeDutyCycle(fan_low)
        lcd.LCD_GoToPos(lcd.LINE2,2)
        lcd.LCD_DisplayString("slow")
        
    elif (data == "i am back"):
        lcd.LCD_GoToPos(lcd.LINE1,2)
        lcd.LCD_DisplayString("welcome nour")
        p_motor.ChangeDutyCycle(5)
        lcd.LCD_GoToPos(lcd.LINE2,2)
        lcd.LCD_DisplayString("slow")
        p_light.ChangeDutyCycle(30)
        lcd.LCD_GoToPos(lcd.LINE2,11)
        lcd.LCD_DisplayString("low ")
        
    elif (data == "i am leaving"):
        lcd.LCD_GoToPos(lcd.LINE1,2)
        lcd.LCD_DisplayString("                ")
        p_motor.ChangeDutyCycle(0)
        lcd.LCD_GoToPos(lcd.LINE2,2)
        lcd.LCD_DisplayString("off ")
        p_light.ChangeDutyCycle(0)
        lcd.LCD_GoToPos(lcd.LINE2,11)
        lcd.LCD_DisplayString("off ")    
        
    else:
        print("invalid")
        

