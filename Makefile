ARCH := arm-none-eabi
CC := $(ARCH)-gcc
CFLAGS := -mcpu=cortex-a72 -fpic -ffreestanding -std=gnu99 -O2 -Wall -Wextra -Isrc/kernel -Isrc/kernel/drivers
LDFLAGS := -ffreestanding -O2 -nostdlib
ASFLAGS := -mcpu=cortex-a72

OBJS := $(patsubst %.S,%.o,$(wildcard src/boot/*.S)) $(patsubst %.c,%.o,$(wildcard src/kernel/*.c)) $(patsubst %.c,%.o,$(wildcard src/kernel/drivers/*.c))

all: build/kernel.img

build/%.o: src/boot/%.S
	$(CC) -c $(ASFLAGS) $< -o $@

build/%.o: src/kernel/%.c
	$(CC) -c $(CFLAGS) $< -o $@

build/%.o: src/kernel/drivers/%.c
	$(CC) -c $(CFLAGS) $< -o $@

build/kernel.img: src/kernel/link.ld $(OBJS)
	$(CC) $(LDFLAGS) -T src/kernel/link.ld -o $@ $(OBJS)
	$(ARCH)-objcopy -O binary $@ build/kernel.bin

clean:
	rm -rf build/*