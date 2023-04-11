#ifndef MAILBOX_H
#define MAILBOX_H

void mailbox_write(unsigned int channel, unsigned int data);
unsigned int mailbox_read(unsigned int channel);

#endif