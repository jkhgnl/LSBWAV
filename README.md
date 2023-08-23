# WavLSB
- ***WavLSB is a programme which can stegan File of all kinds of formats into the  File with extension name wav*** 
****
## Platform
**X86 Windows**          
**X64 Windows**           
**~~Linux~~(Under development)**
## Command Format
- ### Hide File
  1.Prepare the file to be hidden And a wav file to store hidden file's information.          
  2.switch into the file directory
  ~~~
  cd /dir/to/file
  ~~~
  3.Run the stegan.exe
  ~~~
  stegan.exe [File1] [File2]
  ~~~
  >File1:The wav file
  >File2:Hidden file
- ### Extract Hidden File
1.Prepare the file to decode(.wav)       
2.Run the decode.exe
~~~
decode.exe [XXX.wav] [NewFile] (seek)
~~~
(seek 4 is now supported)