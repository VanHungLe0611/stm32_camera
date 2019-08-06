import serial
import os

#####################################################
# connect to serial port
#####################################################
if os.name=='posix':
    ser = serial.Serial('/dev/ttyUSB0')
elif os.name=='nt':
    print("choose device index:")
    comlist = serial.tools.list_ports.comports()
    for i, elem in enumerate(comlist):
        print(str(i) + ":" + elem.device)
        sys.stdout.flush()
    idx = int(input())
    ser_port = serial.Serial(comlist[idx].device, 115200)

#####################################################
# port config
#####################################################
ser.baudrate=115200
ser.bytesize=8
ser.parity='N'
print("open " + ser.name + "\nbaud: " + str(ser.baudrate) + "\ndata format:" + str(ser.bytesize) + str(ser.parity) + str(ser.stopbits))


#####################################################
# pic format config
#####################################################
fileRaw=open("image.raw","wb+")
picSize160x120=38400
picSize = picSize160x120

for pixel in range(picSize):
    test = ser.read()
    fileRaw.write(test)

fileRaw.close()
print('\n'+'total'+str(picSize))
