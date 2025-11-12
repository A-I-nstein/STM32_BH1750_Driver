#ifndef BH1750_H
#define BH1750_H

#define BH1750_ADDR_L			0x23
#define BH1750_ADDR_H			0x5C

#define BH1750_I2C_ADDR_L		(BH1750_ADDR_L << 1)
#define BH1750_I2C_ADDR_H		(BH1750_ADDR_H << 1)

#define BH1750_POWER_ON			0x01
#define BH1750_CONT_H_RES_MODE	0x10

#define BH1750_CONV_FACTOR    1.69f
typedef enum {
	BH1750_OK,
	BH1750_ERROR_INIT_REQUIRED,
	BH1750_ERROR_I2C_TX_FAILED,
	BH1750_ERROR_I2C_RX_FAILED
} bh1750_status;

typedef struct {
	I2C_HandleTypeDef *hi2c;
	uint8_t i2c_addr;
	uint16_t raw;
	float lux;
	bh1750_status status;
} bh1750_handle_t;

bh1750_status bh1750_init(bh1750_handle_t *handle, I2C_HandleTypeDef *hi2c,
		uint8_t i2c_addr);
void bh1750_read_lux(bh1750_handle_t *handle);
const char* bh1750_status_to_string(bh1750_status status);

#endif
