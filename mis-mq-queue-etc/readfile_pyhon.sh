#!/usr/bin/python
import os
print("hello python")

size=os.path.getsize("odb.bin")
print("size is %d" %size)


fp=open("odb.bin","rb+")



fp.seek(2,0)
#fp.seek(2,os.SEEK_SET)
cp=fp.tell()
print("cp is %d"% cp)

nb=fp.write(b'\x3c')
print("write %d bytes" % nb)

fp.flush()



#con=fp.read(1)
#con=fp.read()



#print("it is %x" % con.hex())
#print("it is %x" % int(con.hex()))




#print(list(con))
#for i in list(con):
#	print(hex(i))

#print(type(con))



#rv= int(con.hex(),16)
#print(hex(rv))


#rv= int(con,16)
#print(con.hex())
#print(int.from_bytes(con,byteorder='big'))
#print(type(con.hex()))


fp.close()

