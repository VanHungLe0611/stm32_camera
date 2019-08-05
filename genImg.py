import serial

ser = serial.Serial('/dev/ttyUSB0')
ser.baudrate=115200
ser.bytesize=8
ser.parity='N'
print("open " + ser.name + "\nbaud: " + str(ser.baudrate) + "\ndata format:" + str(ser.bytesize) + str(ser.parity) + str(ser.stopbits))

fileRaw=open("file.raw","wb+")

picSize160x120=38400
picSize = picSize160x120
for pixel in range(picSize):
    test = ser.read()
    print(test)
    fileRaw.write(test)
    #print('\n')

print('\n'+'total'+str(picSize))
