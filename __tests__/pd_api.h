#include <stdint.h>
#include <stdlib.h>

typedef struct PlaydateAPI PlaydateAPI;

struct PlaydateAPI
{
    const struct playdate_sys *system;
    const struct playdate_file *file;
    const struct playdate_graphics *graphics;
    const struct playdate_sprite *sprite;
    const struct playdate_display *display;
    const struct playdate_sound *sound;
    const struct playdate_lua *lua;
    const struct playdate_json *json;
    const struct playdate_scoreboards *scoreboards;
};

typedef enum
{
    kEventInit,
    kEventInitLua,
    kEventLock,
    kEventUnlock,
    kEventPause,
    kEventResume,
    kEventTerminate,
    kEventKeyPressed, // arg is keycode
    kEventKeyReleased,
    kEventLowPower
} PDSystemEvent;

typedef uintptr_t LCDColor; // LCDSolidColor or pointer to LCDPattern

typedef enum
{
    kColorBlack,
    kColorWhite,
    kColorClear,
    kColorXOR
} LCDSolidColor;

typedef uint8_t LCDBitmap; // TODO

typedef enum
{
    kDrawModeCopy,
    kDrawModeWhiteTransparent,
    kDrawModeBlackTransparent,
    kDrawModeFillWhite,
    kDrawModeFillBlack,
    kDrawModeXOR,
    kDrawModeNXOR,
    kDrawModeInverted
} LCDBitmapDrawMode;

typedef enum
{
    kLineCapStyleButt,
    kLineCapStyleSquare,
    kLineCapStyleRound
} LCDLineCapStyle;

typedef uint8_t LCDFont; // TODO

typedef enum
{
    kBitmapUnflipped,
    kBitmapFlippedX,
    kBitmapFlippedY,
    kBitmapFlippedXY
} LCDBitmapFlip;

typedef enum
{
    kASCIIEncoding,
    kUTF8Encoding,
    k16BitLEEncoding
} PDStringEncoding;

typedef struct LCDBitmapTable LCDBitmapTable;
typedef struct LCDFontPage LCDFontPage;
typedef struct LCDFontGlyph LCDFontGlyph;

typedef struct
{
    int left;
    int right; // not inclusive
    int top;
    int bottom; // not inclusive
} LCDRect;

typedef enum
{
    kPolygonFillNonZero,
    kPolygonFillEvenOdd
} LCDPolygonFillRule;

struct playdate_graphics
{
    const struct playdate_video *video;

    // Drawing Functions
    void (*clear)(LCDColor color);
    void (*setBackgroundColor)(LCDSolidColor color);
    void (*setStencil)(LCDBitmap *stencil); // deprecated in favor of setStencilImage, which adds a "tile" flag
    void (*setDrawMode)(LCDBitmapDrawMode mode);
    void (*setDrawOffset)(int dx, int dy);
    void (*setClipRect)(int x, int y, int width, int height);
    void (*clearClipRect)(void);
    void (*setLineCapStyle)(LCDLineCapStyle endCapStyle);
    void (*setFont)(LCDFont *font);
    void (*setTextTracking)(int tracking);
    void (*pushContext)(LCDBitmap *target);
    void (*popContext)(void);

    void (*drawBitmap)(LCDBitmap *bitmap, int x, int y, LCDBitmapFlip flip);
    void (*tileBitmap)(LCDBitmap *bitmap, int x, int y, int width, int height, LCDBitmapFlip flip);
    void (*drawLine)(int x1, int y1, int x2, int y2, int width, LCDColor color);
    void (*fillTriangle)(int x1, int y1, int x2, int y2, int x3, int y3, LCDColor color);
    void (*drawRect)(int x, int y, int width, int height, LCDColor color);
    void (*fillRect)(int x, int y, int width, int height, LCDColor color);
    void (*drawEllipse)(int x, int y, int width, int height, int lineWidth, float startAngle, float endAngle, LCDColor color); // stroked inside the rect
    void (*fillEllipse)(int x, int y, int width, int height, float startAngle, float endAngle, LCDColor color);
    void (*drawScaledBitmap)(LCDBitmap *bitmap, int x, int y, float xscale, float yscale);
    int (*drawText)(const void *text, size_t len, PDStringEncoding encoding, int x, int y);

    // LCDBitmap
    LCDBitmap *(*newBitmap)(int width, int height, LCDColor bgcolor);
    void (*freeBitmap)(LCDBitmap *);
    LCDBitmap *(*loadBitmap)(const char *path, const char **outerr);
    LCDBitmap *(*copyBitmap)(LCDBitmap *bitmap);
    void (*loadIntoBitmap)(const char *path, LCDBitmap *bitmap, const char **outerr);
    void (*getBitmapData)(LCDBitmap *bitmap, int *width, int *height, int *rowbytes, int *hasmask, uint8_t **data);
    void (*clearBitmap)(LCDBitmap *bitmap, LCDColor bgcolor);
    LCDBitmap *(*rotatedBitmap)(LCDBitmap *bitmap, float rotation, float xscale, float yscale, int *allocedSize);

    // LCDBitmapTable
    LCDBitmapTable *(*newBitmapTable)(int count, int width, int height);
    void (*freeBitmapTable)(LCDBitmapTable *table);
    LCDBitmapTable *(*loadBitmapTable)(const char *path, const char **outerr);
    void (*loadIntoBitmapTable)(const char *path, LCDBitmapTable *table, const char **outerr);
    LCDBitmap *(*getTableBitmap)(LCDBitmapTable *table, int idx);

    // LCDFont
    LCDFont *(*loadFont)(const char *path, const char **outErr);
    LCDFontPage *(*getFontPage)(LCDFont *font, uint32_t c);
    LCDFontGlyph *(*getPageGlyph)(LCDFontPage *page, uint32_t c, LCDBitmap **bitmap, int *advance);
    int (*getGlyphKerning)(LCDFontGlyph *glyph, uint32_t glyphcode, uint32_t nextcode);
    int (*getTextWidth)(LCDFont *font, const void *text, size_t len, PDStringEncoding encoding, int tracking);

    // raw framebuffer access
    uint8_t *(*getFrame)(void);         // row stride = LCD_ROWSIZE
    uint8_t *(*getDisplayFrame)(void);  // row stride = LCD_ROWSIZE
    LCDBitmap *(*getDebugBitmap)(void); // valid in simulator only, function is NULL on device
    LCDBitmap *(*copyFrameBufferBitmap)(void);
    void (*markUpdatedRows)(int start, int end);
    void (*display)(void);

    // misc util.
    void (*setColorToPattern)(LCDColor *color, LCDBitmap *bitmap, int x, int y);
    int (*checkMaskCollision)(LCDBitmap *bitmap1, int x1, int y1, LCDBitmapFlip flip1, LCDBitmap *bitmap2, int x2, int y2, LCDBitmapFlip flip2, LCDRect rect);

    // 1.1
    void (*setScreenClipRect)(int x, int y, int width, int height);

    // 1.1.1
    void (*fillPolygon)(int nPoints, int *coords, LCDColor color, LCDPolygonFillRule fillrule);
    uint8_t (*getFontHeight)(LCDFont *font);

    // 1.7
    LCDBitmap *(*getDisplayBufferBitmap)(void);
    void (*drawRotatedBitmap)(LCDBitmap *bitmap, int x, int y, float rotation, float centerx, float centery, float xscale, float yscale);
    void (*setTextLeading)(int lineHeightAdustment);

    // 1.8
    int (*setBitmapMask)(LCDBitmap *bitmap, LCDBitmap *mask);
    LCDBitmap *(*getBitmapMask)(LCDBitmap *bitmap);

    // 1.10
    void (*setStencilImage)(LCDBitmap *stencil, int tile);
};