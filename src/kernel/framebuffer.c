#include "framebuffer.h"
#include "mailbox.h"

static unsigned int width;
static unsigned int height;

void framebuffer_init(unsigned int fb_width, unsigned int fb_height) {
    width = fb_width;
    height = fb_height;

    volatile unsigned int mailbuffer[256] __attribute__((aligned(16)));

    mailbuffer[0] = 8 * 4;  // Total size of our message in bytes
    mailbuffer[1] = 0;      // Request code

    mailbuffer[2] = 0x48003;  // Display size
    mailbuffer[3] = 8;
    mailbuffer[4] = 0;
    mailbuffer[5] = fb_width;  // Framebuffer width
    mailbuffer[6] = fb_height; // Framebuffer height

    mailbuffer[7] = 0; // End tag

    mailbox_write(8, (unsigned int)((unsigned long)mailbuffer & ~0xF));
    mailbox_read(8);
}

void framebuffer_set_color(unsigned int color) {
    volatile unsigned int mailbuffer[256] __attribute__((aligned(16)));

    mailbuffer[0] = 32 * 4; // Total size of our message in bytes
    mailbuffer[1] = 0;      // Request code

    mailbuffer[2] = 0x48005; // Set virtual offset
    mailbuffer[3] = 8;
    mailbuffer[4] = 0;
    mailbuffer[5] = 0;
    mailbuffer[6] = 0;

    mailbuffer[7] = 0x48009; // Set palette
    mailbuffer[8] = 16;
    mailbuffer[9] = 0;
    mailbuffer[10] = 0;       // First palette index
    mailbuffer[11] = color;   // RGBA8 color
    mailbuffer[12] = 0;       // Color for the second palette index (unused)
    mailbuffer[13] = 0;       // Color for the third palette index (unused)
    mailbuffer[14] = 0;       // Color for the fourth palette index (unused)

    mailbuffer[15] = 0; // End tag

    mailbox_write(8, (unsigned int)((unsigned long)mailbuffer & ~0xF));
    mailbox_read(8);
}