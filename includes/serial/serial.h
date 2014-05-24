/*
 * serial.h
 *
 *  Created on: 1 maj 2014
 *      Author: grzybek
 */

#ifndef SERIAL_H_
#define SERIAL_H_

int	serial_init   (void);
void	serial_exit   (void);
void	serial_addr   (unsigned int);
void	serial_setbrg (void);
void	serial_putc   (const char);
void	serial_putc_raw(const char);
void	serial_puts   (const char *);
int	serial_getc   (void);
int	serial_tstc   (void);

#endif /* SERIAL_H_ */
