import time
from PyCRC.CRCCCITT import CRCCCITT
import serial

class CMULTI(object):
  def __init__(self,source,comPort="", baudRate=57600, backChannel="Klima", withCrc = False, timeout=3):
    #self.interface = serial.Serial(comPort, baudRate, timeout=3)
    self.comPort  = comPort
    self.baudRate = baudRate
    self.timeout  = timeout
    self.crc = withCrc
    self.source = source
    if self.crc == False:
      self.header = chr(64)
    else:
      self.header = chr(64+4)

  def open(self):
    self.interface = serial.Serial(self.comPort, self.baudRate, timeout=self.timeout)

  def close(self):
    if type(self.interface)!=str:
       self.interface.close()

  def send(self,text,target,infoHeader,function,address,job,datatype):
    if self.crc == False:
      lengthMsg = len(text)+10
    else:
      lengthMsg = len(text)+14
    if ( (infoHeader=='S') | (infoHeader=='R') | (infoHeader=='r')):
      lengthMsg+=3;
      extraInfo = "{}{}{}{}".format(function,address,job,datatype)
    else:
      extraInfo = ""
    if len(text)>0:
      text += "<"
    toSend = "#{0:02x}{1:s}{2:s}{3:s}{4:s}{5:s}{6:s}".format(lengthMsg,self.header,target,self.source,infoHeader,extraInfo,text)
    crcString = ("%04x" % (CRCCCITT().calculate(toSend)))
    toSend += crcString + "\r\n"
    #print(toSend)
    self.outputTTY(toSend)
    
  def sendStandard(self,text,target,function,address,job,datatype):
    self.send(text,target,'S',function,address,job,datatype)

  def sendCommand(self,target,function,address,job):
    self.send("",target,'S',function,address,job,"?")

  def outputTTY(self,text):
    towrite = text
    self.interface.write(towrite.encode('ascii'))
  
  def _readline(self):
    eol = b'\n'
    leneol = len(eol)
    line = bytearray()
    while True:
       c =  self.interface.read(1)
       if c:
          line += c
          if line[-leneol:] == eol:
             break
       else:
          break
    return bytes(line)
 
  def input(self):
    inTime = True
    hello = self._readline().decode('utf-8')
    if len(hello) == 0:
      return("",False,False,False)
    crcState = True
    crcString = ""
    if hello[0] != '#':
      print("!! start character error")
    if hello[-1] != '\n':
      print("!! end character error")
    if self.crc != False:
      crcString = hello[-6:-2]
      signString = hello[8]
      answerString = hello[13:-6]
      toCheckString = hello[0:-6]
      if len(answerString)>0:
        answerString = answerString[0:-1] # das Parameterendekennzeichen '>' abtrennen
      #print(crcString,"--",signString,"--",answerString,"--",toCheckString)
      if crcString == ("%04x" % (CRCCCITT().calculate(toCheckString))):
        crcState = True
      else:
        crcState = False
        print("!! CRC error")
    else:
       answerString = hello[1:-2]
       signString = hello[-2:-1]
    if signString == 'R':
       return(answerString,True,crcState,inTime)
    elif signString == 'r':
       return(answerString,False,crcState,inTime)
    else:
       print("!! sign character error")
       return(answerString,False,crcState,inTime)


