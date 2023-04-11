#include "mailbox.h"

#define MAILBOX_FULL 0x80000000
#define MAILBOX_EMPTY 0x40000000

#define MAILBOX_BASE 0x3F00B880
#define MAILBOX_READ 0x00
#define MAILBOX_STATUS 0x18
#define MAILBOX_WRITE 0x20

volatile unsigned int *mailbox = (unsigned int *)MAILBOX_BASE;

void mailbox_write(unsigned int channel, unsigned int data) {
    while (mailbox[MAILBOX_STATUS / 4] & MAILBOX_FULL);

    mailbox[MAILBOX_WRITE / 4] = (data & 0xFFFFFFF0) | (channel & 0xF);
}

unsigned int mailbox_read(unsigned int channel) {
    unsigned int data;

    while (1) {
        while (mailbox[MAILBOX_STATUS / 4] & MAILBOX_EMPTY);

        data = mailbox[MAILBOX_READ / 4];

        if ((data & 0xF) == channel) {
            return (data & 0xFFFFFFF0);
        }
    }
}