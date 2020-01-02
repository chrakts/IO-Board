import sys, os

from cmulti import CMULTI

class IOBoard(CMULTI):
  def __init__(self,source,target,comPort="", baudRate=57600, backChannel="TLog", withCrc = True, timeout=3):
    super(self.__class__,self).__init__(source,comPort , baudRate, backChannel, withCrc, timeout)
    self.target = target
    self.source = source
    
    
  def setSecurityKey(self,key):
    mode = ["CUSTOMER","PRODUCTION","DEVELOPMENT"]
    self.sendStandard(key,self.target,"S","0","K","T")
    return(  mode[ int( self.errorHandler(self.input()) ) ]  )

  def getSecurityKey(self):
    mode = ["CUSTOMER","PRODUCTION","DEVELOPMENT"]
    self.sendCommand(self.target,"S","0","k")
    return(  mode[ int( self.errorHandler(self.input()) ) ]  )
    
  def getCompilationDate(self):
    self.sendCommand(self.target,"S","0","C")
    return(   self.errorHandler(self.input())   )

  def getCompilationTime(self):
    self.sendCommand(self.target,"S","0","T")
    return(   self.errorHandler(self.input())   )

  def getFreeMemory(self):
    self.sendCommand(self.target,"S","0","m")
    return( int( self.errorHandler(self.input()) )  )

  def setOutputState(self,bit,state):
    self.sendStandard(str(state),self.target,"Q",str(bit),"S","T")
    self.errorHandler(self.input()) 
    return True

  def setAllOutputs(self):
    for i in range(0,4):
      self.setOutputState(i,1)
    self.errorHandler(self.input()) 
    return True
     
  def clearAllOutputs(self):
    for i in range(0,4):
      self.setOutputState(i,0)

  def getInputState(self,bit):
    self.sendCommand(self.target,"I",str(bit),"g")
    result = self.errorHandler( self.input() )
    if result == '0':
      return False
    else:
      return True

  def getAllInputs(self):
    bit = 1
    result = 0
    for i in range(0,4):
      if self.getInputState(i)==True:
        result |= bit
      bit = bit << 1
    return(result)
    
  def errorHandler(self,result):
    if result[3]==False:
      raise ValueError("Timeout, Gerät hat nicht in der vordefinierten Zeit geantwortet!")
    if result[2]==False:
      raise ValueError("CRC-Fehler bei der Kommunikation!")
    if result[1]==False:
      raise ValueError("Gerät gab Fehler zurück!")
    return(result[0])
    
test = IOBoard('PC','I1',comPort="/dev/ttyUSB0", baudRate=115200)

test.open()
print( test.getSecurityKey() )
print( test.setSecurityKey("Phe6%!kdf?+2aQ") )
print( test.getSecurityKey() )
print( test.setSecurityKey("D=&27ane%24dez") )
print( test.getCompilationDate() )
print( test.getCompilationTime() )
print( test.getFreeMemory() )
print( test.setOutputState(2,1) )
print( test.getInputState(0) )
print( test.getAllInputs() )
test.close()

#print( test.clearAllOutputs() )

