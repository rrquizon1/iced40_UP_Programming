// data.h
#ifndef ICE40_SPI_H
#define ICE40_SPI_H

#define chunk_size 4
#define num_chunks (g_iDataSize+chunk_size-1)/chunk_size

int configure_output(struct gpiod_line *line, const char *consumer, int value);
int spi_init(int spi_speed,struct gpiod_line **crst,struct gpiod_line **cs);
static int rbpi_ioctl(unsigned char *tx_buf, unsigned char *rx_buf, int len);
int rbpi_tx(unsigned char *buf, int bytes);
int rbpi_exit();


#endif
