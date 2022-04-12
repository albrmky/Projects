import RPi.GPIO as gpio
import time


LCD_pins={	"E": 0,"R_S": 0,"R_W": 0,
			"D7": 0,"D6": 0,"D5": 0,"D4": 0,"Vo": 0}


command = {	"Clear_Display":0b00000001,
			"Return_Home":0b00000010,
			"Shift_Left":0b00011000,
			"Shift_Right":0b00011100,
			"Cursor_Left":0b00010000,
			"Cursor_Right":0b00010100}
LINE1 = 0
LINE2 = 1


def LCD_init(**pins):
    global LCD_pins
    gpio.setmode(gpio.BCM)
    for i in LCD_pins.keys():
        LCD_pins[i]= pins[i]
        print("LCD_pins",i,"equal",LCD_pins[i])

    for i in LCD_pins.values():
        gpio.setup(i,gpio.OUT)
        print("value = ",i)
    
    time.sleep(0.03)
    
    gpio.output(LCD_pins["R_S"],gpio.LOW)
    gpio.output(LCD_pins["R_W"],gpio.LOW)
    gpio.output(LCD_pins["E"],gpio.HIGH)

    gpio.output(LCD_pins["D7"],0)
    gpio.output(LCD_pins["D6"],0)
    gpio.output(LCD_pins["D5"],1)
    gpio.output(LCD_pins["D4"],0)

    time.sleep(0.001) #1ms  delay

    gpio.output(LCD_pins["E"],gpio.LOW)

    LCD_SendCommand(0x28)
    time.sleep(0.001) #1ms  delay
    LCD_SendCommand(0x0E)
    time.sleep(0.001) #1ms  delay
    LCD_SendCommand(0x01)
    time.sleep(0.001) #1ms  delay
    LCD_SendCommand(0x06)


def GET_BIT(data,pin):
    return int(int(data>>pin) & 0x1)


def LCD_SendCommand(command):
    for i in range(2):

        time.sleep(0.001) #1ms  delay

        gpio.output(LCD_pins["R_S"],gpio.LOW)
        gpio.output(LCD_pins["R_W"],gpio.LOW)
        gpio.output(LCD_pins["E"],gpio.HIGH)

        gpio.output(LCD_pins["D7"],GET_BIT(command,7 - (i%2*4)))
        gpio.output(LCD_pins["D6"],GET_BIT(command,6 - (i%2*4)))
        gpio.output(LCD_pins["D5"],GET_BIT(command,5 - (i%2*4)))
        gpio.output(LCD_pins["D4"],GET_BIT(command,4 - (i%2*4)))

        time.sleep(0.001) #1ms  delay

        gpio.output(LCD_pins["E"],gpio.LOW)


def LCD_SendData(command):
    
    command = ord(command)
    for i in range(2):
        time.sleep(0.001) #1ms  delay
        gpio.output(LCD_pins["R_S"],gpio.HIGH)
        gpio.output(LCD_pins["R_W"],gpio.LOW)
        gpio.output(LCD_pins["E"],gpio.HIGH)

        gpio.output(LCD_pins["D7"],GET_BIT(command,7 - (i%2*4)))
        gpio.output(LCD_pins["D6"],GET_BIT(command,6 - (i%2*4)))
        gpio.output(LCD_pins["D5"],GET_BIT(command,5 - (i%2*4)))
        gpio.output(LCD_pins["D4"],GET_BIT(command,4 - (i%2*4)))

        time.sleep(0.001) #1ms  delay

        gpio.output(LCD_pins["E"],gpio.LOW)

def LCD_DisplayString(data):
    for i in range(len(data)):
        LCD_SendData(data[i])
        
def LCD_GoToPos(row,col):
    value = 0x40 * row + col + 0b10000000
    LCD_SendCommand(value)


# LCD_init(E=17,R_S=22,R_W=27,D7=2,D6=3,D5=4,D4=14,Vo=15)
#p = gpio.PWM(LCD_pins["Vo"],50)
#p.start(10)


#LCD_SendData(55)
# LCD_DisplayString('hand ball')
# LCD_GoToPos(LINE2,0)
# LCD_DisplayString('football')
	
#while True:
	

	
	
	
    



	
