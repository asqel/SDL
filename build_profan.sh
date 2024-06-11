profan_path="../profanOS"
CFLAGS="-ffreestanding -fno-exceptions -m32 -I$profan_path/include/zlibs -I$profan_path/include/addons -O1 -nostdinc -U_WIN32 -U__linux__ -Iinclude -Isrc -D__profanOS__=1"
#LDFLAGS="-m elf_i386 -nostdlib -L $profan_path/out/zlibs -T $profan_path/tools/link_elf.ld -lc"
LDFLAGS="-shared -nostdlib -m32"
LD=gcc
CC=gcc

prefix="."
bins="$prefix/bins"
rm -rf bins/*
rm sdl.elf

mkdir -p $bins

#files="$prefix/src/*.c $prefix/src/*/*.c $prefix/src/*/dummy/*.c"
files="src/*.c src/atomic/*.c src/audio/*.c src/cpuinfo/*.c src/events/*.c src/file/*.c src/haptic/*.c src/joystick/*.c src/power/*.c src/render/*.c src/render/software/*.c src/stdlib/*.c src/thread/*.c src/timer/*.c src/video/*.c src/audio/disk/*.c src/audio/dummy/*.c src/filesystem/profanOS/*.c src/video/dummy/*.c src/haptic/dummy/*.c src/joystick/dummy/*.c src/main/dummy/*.c src/thread/generic/*.c src/timer/dummy/*.c src/loadso/dummy/*.c"
count=0
for i in $files; do
    if [[ "$i" != "$prefix/src/joystick/"* ]]; then
        echo "Compiling $i..."
        $CC $CFLAGS -c $i -o $bins/$count.o 
        if [ ! -f $bins/$count.o ]; then
            echo "Cannot compile $i"
            exit 1
        fi
    else
        echo "Skipping $i"
    fi
    count=$((count + 1))
done


$LD $LDFLAGS -o libSDL2.elf $bins/*.o


rm -rf $profan_path/out/zlibs/SDL2.so
rm -rf $profan_path/include/addons/SDL2/
mkdir $profan_path/include/addons/SDL2/
cp libSDL2.elf $profan_path/out/zlibs/libSDL2.so
cp include/*.h $profan_path/include/addons/SDL2/