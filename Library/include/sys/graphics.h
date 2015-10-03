#ifndef _SYS_GRAPHICS_H
#define _SYS_GRAPHICS_H

/* We use the same structure for modes */
struct display {
  uint8_t mode;			/* Mode number */
  uint16_t width, height;	/* Logical display size */
  uint16_t stride, lines;	/* Physical layout */
  uint8_t vstep, hstep;		/* Scrolling step if supported or 0xFF */
  uint8_t format;
#define FMT_MONO_BW	0
#define FMT_MONO_WB	1
#define FMT_COLOUR4	2
#define FMT_COLOUR16	3
/* Those sufficiently funky */
#define FMT_SPECTRUM	128
#define FMT_VDP		129	/* VDP graphics engines */
  uint8_t hardware;
#define HW_UNACCEL	1	/* Simple display */
#define HW_VDP_9918	128	/* Not neccessarily MSX... */
#define HW_VDP_9938	129
#define HW_TRS80GFX	130	/* TRS80 model 4 graphics board */
  uint16_t features;
#define GFX_MAPPABLE	1	/* Can map into process memory */
#define GFX_PALETTE	2	/* Has colour palette */
#define GFX_OFFSCREEN	4	/* Offscreen memory */
#define GFX_VBLANK	8
#define GFX_ENABLE	16	/* Separate mode we enable/disable */
#define GFX_MULTIMODE	32	/* Has multiple modes */
#define GFX_PALETTE_SET	64	/* Has settable colour palette */
#define GFX_TEXT	128	/* Console text works in this mode */
  uint16_t memory;		/* Memory size in KB (may be 0 if not relevant) */
  uint16_t commands;
#define GFX_DRAW	1	/* Supports the draw command */
#define GFX_RAW		2	/* Raw command streams to the GPU */
#define GFX_ADRAW	4	/* Supports draw attributes */
#define GFX_CLIP	8	/* Supports clipping */
#define GFX_BLIT	16	/* Supports screen to screen blits */
#define GFX_READ	32	/* Supports reading back a buffer */
#define GFX_AREAD	64	/* Supports reading back an attribute buffer */
#define GFX_PDRAW	128	/* Supports planar draw (draw buffer with a
				   leading plane mask) indicating which planes
				   to run the command on */
#define GFX_WRITE	256	/* Supports writing a buffer */
#define GFX_AWRITE	512	/* Supports writing an attribute buffer */
 /* We may want to add some hardware ones as we hit machines that have them */
};

/* FIXME: need a way to describe/set modes if multiple supported */

struct palette {
  uint8_t n;
  uint8_t r,g,b;
};

/* Returned from a successful GFXIOC_MAP */
struct videomap {
  uaddr_t mmio;			/* Memory mapped register base */
  uaddr_t pio;			/* I/O space register base */
  uaddr_t fbmem;		/* Frame buffer memory */
  usize_t fbsize;
  uint8_t mmio_seg;		/* For the 8086 */
  uint8_t fbmem_seg;
  uint8_t spacing;		/* Multiplier for non standard register spacing */
  uint8_t flags;		/* Which maps are valid */
#define MAP_MMIO	1
#define MAP_MMIO_SEG	2
#define MAP_PIO		4
#define MAP_FBMEM	8
#define MAP_FBMEM_SEG	16
#define MAP_FBMEM_SIMPLE 32	/* Normal mapping of linear framebuffer as
				   mode would imply */
};

#define GFXIOC_GETINFO		0x0300	/* Query display info for this tty */
#define GFXIOC_ENABLE		0x0301	/* Enter graphics mode */
#define GFXIOC_DISABLE		0x0302	/* Exit graphics mode */
#define GFXIOC_GETPALETTE	0x0303	/* Get a palette entry */
#define GFXIOC_SETPALETTE	0x0304	/* Set a palette entry */
#define GFXIOC_MAP		0x0305	/* Map into process if supported */
#define GFXIOC_UNMAP		0x0306	/* Unmap from process */
#define GFXIOC_DRAW		0x0307	/* Draw a buffer */
#define GFXIOC_RAW		0x0308	/* GPU direct buffer */
#define GFXIOC_ADRAW		0x0309	/* Draw an attribute buffer */
#define GFXIOC_CLIP		0x030A	/* Set clip rectangle */
#define GFXIOC_BLIT		0x030B	/* Screen to screen blit */
#define GFXIOC_READ		0x030C	/* Read back screen */
#define GFXIOC_AREAD		0x030D	/* Read back attributes */
#define GFXIOC_PDRAW		0x030E	/* Planar draw */
#define GFXIOC_PAN		0x030F	/* Panning */
#define GFXIOC_WAITVB		0x0310	/* Wait for vblank */
#define GFXIOC_GETMODE		0x0311	/* Get info on a mode */
#define GFXIOC_SETMODE		0x0312	/* Set video mode */
#define GFXIOC_WRITE		0x0313	/* Write to screen direct */
#define GFXIOC_AWRITE		0x0314	/* Write to attributes direct */
#endif