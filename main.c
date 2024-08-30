#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/ioctl.h>
#include <linux/spi/spidev.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <gpiod.h>
#include "fastconfig_data.h"
#include "ice40_spi.h"

struct gpiod_line *crst;
struct gpiod_line *cs;





int main() {
	unsigned char write_buf[1] = { 0xFF };
	unsigned char chunkedArray[num_chunks][chunk_size]; // Chunked bitstream
	
	
	spi_init(3000,&crst,&cs);
	gpiod_line_set_value(crst, 0);
	gpiod_line_set_value(cs, 0);
	
	usleep(1); //200 ns
	gpiod_line_set_value(crst, 1);
	usleep(1500); //1200 us
	
	
	gpiod_line_set_value(cs, 1);
	rbpi_tx(write_buf,1);//send 0xFF
	gpiod_line_set_value(cs, 0);
	
	
	chunk_array(chunkedArray); //Divide bitstream into chunks 
	
	//for (int i = 0; i <num_chunks; i++) { // optional prininting of chunks
      //  printf("Chunk %d: ", i);
       // printChunk(chunkedArray[i], chunk_size);
	//}

	
	usleep(1);
	
	for(int k=0;k<num_chunks;k++){
	rbpi_tx(chunkedArray[k],chunk_size);//Send bitstream by chunks.
	}
	
	
	usleep(1);
	gpiod_line_set_value(cs, 1);
	
	for(int l=0;l<149;l++){
		
		rbpi_tx(write_buf,1);//send 0xFF after CDONE goes high.
		
		
	}	
	

	rbpi_exit();
	
	
}
