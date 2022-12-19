.PHONY: run
.PHONY: clean
.PHONY: build

FLAGS = -masm=intel -O1 -Wno-error -c -nostdinc -nostdlib -fno-builtin -fno-stack-protector -ffreestanding -m32
run: build
	@qemu-system-i386 -drive format=raw,file=bin/b.bin

build:
	@nasm boot/boot.asm -f bin -o bin/bootloader.bin
	@nasm protocol/protocol_util.asm -f elf32 -o bin/protocol_util.o
	@gcc ${FLAGS} -o bin/main.o OS/main.c
	@gcc ${FLAGS} -o bin/kernel.o OS/kernel.c
#@gcc -std=gnu2x ${FLAGS} -o second_stage.o second_stage_boot.c
#@ld -m elf_i386 -Tlinker2.ld -nostdlib --nmagic -o second_stage.out second_stage.o
	@ld -m elf_i386 -TOS/linker.ld -nostdlib --nmagic -o bin/boot.out bin/main.o bin/protocol_util.o
	@ld -m elf_i386 -TOS/kernel.ld -nostdlib --nmagic -o bin/kernel.out bin/kernel.o bin/protocol_util.o
# Literally taking the file and turning it into a binary file
#@ { head -c 1536 > boot.bin; } < boot.out
	@objcopy -O binary bin/boot.out bin/boot.bin
	@objcopy -O binary bin/kernel.out bin/kernel.bin
#@objcopy -O binary second_stage.out second_stage.bin
#@cat boot.bin second_stage.bin > b.bin
	@cat bin/bootloader.bin bin/boot.bin bin/kernel.bin > bin/b.bin

clean:
	@rm -rf bin/*.out
	@rm -rf bin/*.o
	@rm -rf bin/*.bin
