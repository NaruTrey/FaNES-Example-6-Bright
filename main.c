#include <FaNES.h>
#include "image.h"

const uchar palette[16] = {
    0x0F, 0x00, 0x10, 0x30,
    0x01, 0x11, 0x21, 0x31,
    0x06, 0x16, 0x26, 0x36,
    0x0A, 0x1A, 0x2A, 0x3A
};

static uchar i, j, spriteID = 0;
static uchar brightBackground = 4, brightSprites = 4;

void main(void) {
    setPaletteBackground(palette);
    setPaletteSprites(palette);
    unpackNametableRLE(image, NAMETABLE_A);
    for(i = 0; i < 4; ++i) {
        for(j = 0; j < 4; ++j) {
            spriteID = newSprite(64 + 8 * (getRandomUchar() % 16), 64 + 8 * (getRandomUchar() % 14), 0x0D, i & 3, spriteID);
        }
    }
	onGraphics();
	while(TRUE) {
        uchar pad = padPush(PAD_PORT_PLAYER_1);
        if (pad & PAD_BUTTON_UP && brightBackground < 8)
            brightBackground++;
        if (pad & PAD_BUTTON_DOWN && brightBackground > 0)
            brightBackground--;
        if (pad & PAD_BUTTON_LEFT && brightSprites > 0)
            brightSprites--;
        if (pad & PAD_BUTTON_RIGHT && brightSprites < 8)
            brightSprites++;
        setPaletteBackgroundBright(brightBackground);
        setPaletteSpritesBright(brightSprites);
		waitFrame();
	}
}
