#define RTC_PORT_COMMAND    0x70
#define RTC_PORT_DATA       0x71

#define RTC_MAX_FREQ        1024//32768
#define RTC_INIT_FREQ       2

static int rtc_int_flag;

// Intialize the RTC
void init_rtc();

// Handles the RTC when it is called in an interrupt
void rtc_handler();

extern int32_t rtc_open(const uint8_t * filename);
extern int32_t rtc_close(int32_t fd);
extern int32_t rtc_read(int32_t fd, void * buf, int32_t nbytes);
extern int32_t rtc_write(int32_t fd, const void * buf, int32_t nbytes);