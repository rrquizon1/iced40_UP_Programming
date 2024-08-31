This is an SSPI CRAM programming implementation of ice40 UltraPlus using Raspberry pi 5.

This example uses lgpiod library for manual control of CS and CRESET so makesure to install it: sudo apt-get install gpiod libgpiod-dev

The instructions used for programming for this example is taken from FPGA-TN-02001-3.4( [ice40 Programming and Configuration](https://www.latticesemi.com/view_document?document_id=46502)) technical note. See below for the waveform instructions from the document.
![image](https://github.com/user-attachments/assets/d9d8a3fe-a73e-4d5b-aea2-df623fe39120)

For this example, the dedicated resources of raspberry pi 5 is used for SPI communication. In [ice40 ultralite programming example](https://github.com/rrquizon1/ice40_UL_programming), we have already adjusted the buffer to 65536 bytes.
However, this approach is insufficient for programming high-density devices like the ICE40 UP5K, which has around 100k bytes of data. To address this, I've divided the data into chunks and transmitted it through SPI one chunk at a time. 
It's important to note that when sending data in chunks, the CS must be held low, which is why I manually control the CS.


Source files:

main.c-contains the programming procedure

fastconfig_data.c- contains the bitstream data to be sent. This can be modified to send bitsream on different devices

ice40_spi.c- contains the functions used for SPI transaction and gpio control

Makefile-compiles the project

You can modify g_iDataSize and g_pucDataArray with your bitstream information. With this example, ice40 UP 5k breakout board is used which has around 100k of data. This is beyond the buffer size limit that's why we need to send data by chunks. 

![image](https://github.com/user-attachments/assets/3fc5a287-e801-4b68-9822-ac081261dd96)

Main.c follows the instructions from FPGA-TN-02001-3.4. This is very similar with the ice40UL example except that we add an additional step to divide the bitstream into chunks.

![image](https://github.com/user-attachments/assets/157006b0-ab0a-4097-a8b1-1861cf04c5a9)

See sample waveform transaction below:
![image](https://github.com/user-attachments/assets/073d1997-4830-43d6-942f-cdb6db1aa78d)

Aside from, dividing the bitstream by chunks, I would like to emphasize the need for additional clock cycles after CDONE goes high. If CDONE,goes high and no extra clock cyclers are sent, IO settings in the bitstream will not activate.
This is stated clearly at chapter 13.2 of FPGA-TN-02001-3.4.
![image](https://github.com/user-attachments/assets/44497b46-5932-4022-99e2-b4b5c612d482)


