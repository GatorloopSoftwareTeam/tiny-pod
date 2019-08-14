#include <stdint.h>
#include <stdbool.h>
#include <stdarg.h>


#ifndef I2C_WRAP_H_
#define I2C_WRAP_H_


extern void InitI2C0(void);
extern void I2CSend(uint8_t slave_addr, uint8_t num_of_args, ...);
extern uint8_t I2CReceive(uint32_t slave_addr, uint8_t reg);

#endif /* I2C_WRAP_H_ */
