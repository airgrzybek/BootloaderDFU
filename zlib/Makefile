# drivers makefile

include ../config.mk

LIB := zlib.a

# ST Library source files.
COBJS-$(CONFIG_ZLIB) += adler32.o
COBJS-$(CONFIG_ZLIB) += compress.o
COBJS-$(CONFIG_ZLIB) += crc32.o
COBJS-$(CONFIG_ZLIB) += deflate.o
COBJS-$(CONFIG_ZLIB) += gzclose.o
COBJS-$(CONFIG_ZLIB) += gzlib.o
COBJS-$(CONFIG_ZLIB) += gzread.o
COBJS-$(CONFIG_ZLIB) += gzwrite.o
COBJS-$(CONFIG_ZLIB) += infback.o
COBJS-$(CONFIG_ZLIB) += inffast.o
COBJS-$(CONFIG_ZLIB) += inflate.o
COBJS-$(CONFIG_ZLIB) += inftrees.o
COBJS-$(CONFIG_ZLIB) += trees.o
COBJS-$(CONFIG_ZLIB) += uncompr.o
COBJS-$(CONFIG_ZLIB) += zutil.o

COBJS	:= $(COBJS-y)

SRCS	:= $(COBJS:.o=.c)
OBJS	:= $(COBJS)

all:	$(LIB)

$(LIB): $(OBJS)
	$(AR) $(ARFLAGS) $@ $(OBJS) 

clean:
	@rm -f $(OBJS)
	@rm -f $(LIB)
