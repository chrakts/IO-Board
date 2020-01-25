import sys, os

from cmulti import CMULTI

class IOBoard(CMULTI):
  def __init__(self,source,target,comPort="", baudRate=115200, withCrc = True, timeout=3):
    super(self.__class__,self).__init__(source,comPort , baudRate, withCrc, timeout)
    self.target = target
    self.source = source
    self.iname = {"sensor0":0,"sensor1":1,"sensor2":2,"sensor3":3}
    self.oname = {"aktor0":0,"aktor1":1,"aktor2":2,"aktor3":3}
    
    
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
    if type(bit) == str:
      bit = self.oname[bit]
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
    if type(bit) == str:
      bit = self.iname[bit]
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
   
  def mapInputs(self,names):
    self.iname = names 

  def mapOutputs(self,names):
    self.oname = names 

  def errorHandler(self,result):
    if result[3]==False:
      raise ValueError("Timeout, Gerät hat nicht in der vordefinierten Zeit geantwortet!")
    if result[2]==False:
      raise ValueError("CRC-Fehler bei der Kommunikation!")
    if result[1]==False:
      raise ValueError("Gerät gab Fehler zurück!")
    return(result[0])

ichannel = {"LS_Eingang":0,"LS_Ausgang":1,"sensor3":2,"sensor4":3}
ochannel = {"Zylinder":0,"aktor1":1,"aktor2":2,"aktor3":3}

anlage = IOBoard('PC','I1',comPort="/dev/ttyUSB0")

anlage.mapInputs(ichannel)
anlage.mapOutputs(ochannel)

anlage.open()
print( anlage.getSecurityKey() )
print( anlage.setSecurityKey("Phe6%!kdf?+2aQ") )
print( anlage.getSecurityKey() )
print( anlage.setSecurityKey("D=&27ane%24dez") )
print( anlage.getCompilationDate() )
print( anlage.getCompilationTime() )
print( anlage.getFreeMemory() )
print( anlage.clearAllOutputs() )
print( anlage.setOutputState( "Zylinder",1 ) )
print( anlage.getInputState("LS_Eingang") )
print( anlage.getInputState("LS_Ausgang") )
print( anlage.getAllInputs() )
anlage.close()

#print( test.clearAllOutputs() )

