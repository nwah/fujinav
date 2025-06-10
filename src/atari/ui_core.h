#ifndef UI_CORE_H
#define UI_CORE_H

#include <stdint.h>

void set_dlist(void *dlist_ptr, uint8_t size);
void set_default_dlist(void);
void start_dli(void *dli);
void set_dlist_dli_logo_with_text(void);
void highlight_row(uint8_t row);

#endif
