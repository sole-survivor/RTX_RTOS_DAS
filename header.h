typedef unsigned int u32;
typedef unsigned char u8;
typedef signed int s32;
typedef signed char s8;
typedef unsigned short int u16;

extern void delay_sec(unsigned int, unsigned int);
extern void delay_ms(unsigned int, unsigned int);

extern void lcd_data(unsigned char);
extern void lcd_cmd(unsigned char);
extern void lcd_init(void);
extern void lcd_string(char *);
extern void lcd_int(int);
extern void lcd_float(float);
extern void lcd_cgram(char *);

extern void uart0_init(unsigned int);
extern void uart0_tx(unsigned char);
extern void uart0_tx_string(s8 *);
extern u8 uart0_rx(void);
extern void uart0_ascii(u8);
extern void uart0_hex(u8);
extern void uart0_tx_int(s32);
extern void uart0_tx_float(float);
extern void uart0_rx_string(s8 *, s32);

void adc_init(void);
u32 adc_read(int);
void adc_uart_tx_int(s32);

void config_vic(void);
void en_uart0_intr(void);

void spi0_init(void);
unsigned char spi0(unsigned char);
unsigned short int mcp3204_adc_read(unsigned int);

void i2c_init(void);
void i2c_wr(u8, u8, u8);
u8 i2c_rd(u8, u8);
