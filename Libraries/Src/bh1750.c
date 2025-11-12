#include "main.h"

#include "bh1750.h"

#define BH1750_I2C_TIMEOUT	100

const char* bh1750_status_to_string(bh1750_status status) {
	switch (status) {
	case BH1750_OK:
		return "Success";
	case BH1750_ERROR_INIT_REQUIRED:
		return "BH1750 Initialization failed.";
	case BH1750_ERROR_I2C_TX_FAILED:
		return "BH1750 I2C transceiver operation failed.";
	case BH1750_ERROR_I2C_RX_FAILED:
			return "BH1750 I2C receiver operation failed.";
	default:
		return "Unknown Status";
	}
}

void bh1750_send_cmd(bh1750_handle_t *handle, uint8_t cmd) {
	uint8_t tx_buf[1] = { cmd };
	if (HAL_I2C_Master_Transmit(handle->hi2c, handle->i2c_addr, tx_buf, 1,
	BH1750_I2C_TIMEOUT) == HAL_OK) {
		handle->status = BH1750_OK;
	} else {
		handle->status = BH1750_ERROR_I2C_TX_FAILED;
	}
}

bh1750_status bh1750_init(bh1750_handle_t *handle, I2C_HandleTypeDef *hi2c,
		uint8_t i2c_addr) {
	if (handle == NULL || hi2c == NULL) {
		handle->status = BH1750_ERROR_INIT_REQUIRED;
		return handle->status;
	}

	handle->hi2c = hi2c;
	handle->i2c_addr = i2c_addr;
	handle->raw = 0;
	handle->lux = 0.0f;

	bh1750_send_cmd(handle, BH1750_POWER_ON);
	if (handle->status != BH1750_OK) {
		return handle->status;
	}

	bh1750_send_cmd(handle, BH1750_CONT_H_RES_MODE);
	if (handle->status != BH1750_OK) {
		return handle->status;
	}

	HAL_Delay(180);
	handle->status = BH1750_OK;
	return handle->status;
}

void bh1750_read_raw(bh1750_handle_t *handle) {
	uint8_t rx_buf[2] = { 0, 0 };
	if (HAL_I2C_Master_Receive(handle->hi2c, handle->i2c_addr, rx_buf, 2,
	BH1750_I2C_TIMEOUT) == HAL_OK) {
		handle->raw = (uint16_t) (rx_buf[0] << 8) | (uint16_t) (rx_buf[1]);
		handle->status = BH1750_OK;
	} else {
		handle->raw = 0;
		handle->status = BH1750_ERROR_I2C_RX_FAILED;
	}
}

float bh1750_convert_to_lux(uint16_t raw) {
	return (float) raw / BH1750_CONV_FACTOR;
}

void bh1750_read_lux(bh1750_handle_t *handle) {

	bh1750_read_raw(handle);
	if (handle->status == BH1750_OK) {
		handle->lux = bh1750_convert_to_lux(handle->raw);
	} else {
		handle->lux = 0.0f;
		handle->raw = 0;
	}
}
