

#include <stdio.h>
#include <windows.h>
int main(int argc, char **argv)
{
	GLuint textureId;
 	 glGenTextures(1, &textureId);
 	 glBindTexture(GL_TEXTURE_2D, textureId);
	EGLImageKHR eglImage;

 	     Pixmap tmpPixmap(pd);
 	     EGLint attribs[] = {
 	         EGL_IMAGE_PRESERVED_KHR, EGL_TRUE,
 	         EGL_NONE
 	     };
 	     {


 	     eglImage = eglCreateImageKHR(QEgl::display(), EGL_NO_CONTEXT, EGL_NATIVE_PIXMAP_KHR,
 	                                  (EGLClientBuffer)QEgl::nativePixmap(&tmpPixmap), attribs);
 	     GLContext* ctx = q;
 	     glEGLImageTargetTexture2DOES(GL_TEXTURE_2D, eglImage);
 	     GLint err = glGetError();
 	     if (err == GL_NO_ERROR)
 	         textureIsBound = true;
 	     // Once the egl image is bound, the texture becomes a new sibling image and we can safely
 	     // destroy the EGLImage we created for the pixmap:
 	     if (eglImage != EGL_NO_IMAGE_KHR)
 	         eglDestroyImageKHR(QEgl::display(), eglImage);
 	     }

	// creating input

    myBitmap.SetPixel(Xcount, Ycount, Color.Black);
    ///////////////////////////////////////////////////////////////////////
    unsigned char pixels[1280*1080*3];
    // fill pixels
    for (int i=0; i<1280*1080*3; i++){
        pixels[i] = (i%4==1)*255;        // An BGR (not RGB) 160x120 image.

    // at this point we have some input

    BITMAPINFOHEADER bmih;
    bmih.biSize     = sizeof(BITMAPINFOHEADER);//the size of header struct
    bmih.biWidth    = 1280;//width in pixel
    bmih.biHeight   = 1080;
    bmih.biPlanes   = 1;
    bmih.biBitCount = 24;   //bits per pixel
    bmih.biCompression  = BI_RGB ;
    bmih.biSizeImage    = 0;    //length of image data in bytes
    bmih.biXPelsPerMeter    =   10;
    bmih.biYPelsPerMeter    =   10;
    bmih.biClrUsed    =0;       //the number of color used in bmp
    bmih.biClrImportant =0;

    BITMAPINFO dbmi;
    ZeroMemory(&dbmi, sizeof(dbmi));
    dbmi.bmiHeader = bmih;
    dbmi.bmiColors->rgbBlue = 0;
    dbmi.bmiColors->rgbGreen = 0;
    dbmi.bmiColors->rgbRed = 0;
    dbmi.bmiColors->rgbReserved = 0;

    //HDC hdc = ::GetDC(NULL);
    HDC hdc= CreateCompatibleDC(NULL);
    HBITMAP hbmp = CreateDIBitmap(hdc, &bmih, CBM_INIT, pixels, &dbmi, DIB_RGB_COLORS);
    if (hbmp == NULL) {
        ::MessageBox(NULL, L"Could not load the desired image image", L"Error", MB_OK);
        return;
    }


	// cleanup
    DeleteObject(hbmp);
////////////////////////////////////////////////////////////////////
	BYTE buffer[16*16*3];
::memset(buffer,255,sizeof(buffer));


CClientDC dc(this);
CBitmap bmp;


HBITMAP hBitmap=CreateBitmap(16,16,1,24,buffer);//with all the parameters filled.
bmp.Attach(hBitmap);
CDC dcSource;
dcSource.CreateCompatibleDC(&dc);
BITMAP bmpInfo;

bmp.GetBitmap(&bmpInfo);
dcSource.SelectObject(&bmp);

CRect rectDest;
GetClientRect(&rectDest);
int st= dc.BitBlt(0,0,bmpInfo.bmWidth, bmpInfo.bmHeight, &dcSource, 0, 0, SRCCOPY); //returned 1

//////////////////////////////////////////////////////////////////////////////////////
HDC dc= CreateCompatibleDC(NULL);
BITMAPINFO i;
ZeroMemory( &i.bmiHeader, sizeof(BITMAPINFOHEADER) );
i.bmiHeader.biWidth=5;     // Set size you need
i.bmiHeader.biHeight=5;    // Set size you need
i.bmiHeader.biPlanes=1;
i.bmiHeader.biBitCount=24; // Can be 8, 16, 32 bpp or
                           // other number
i.bmiHeader.biSizeImage=0;
i.bmiHeader.biSize=sizeof(BITMAPINFOHEADER);
i.bmiHeader.biClrUsed= 0;
i.bmiHeader.biClrImportant= 0;
VOID *pvBits;
HBITMAP hbmp= CreateDIBSection( dc,
                                &i,
                                DIB_RGB_COLORS,
                                &pvBits,
                                NULL,
                                0 );
// You don't have to use 'pvBits', later DeleteObject(hbmp)
// will free this bit array.
/////////////////////////////////////////////////////////////////////
static HBITMAP Create8bppBitmap(HDC hdc, int width, int height, LPVOID pBits = NULL)
{
    BITMAPINFO *bmi = (BITMAPINFO *)malloc(sizeof(BITMAPINFOHEADER) + sizeof(RGBQUAD) * 256);
    BITMAPINFOHEADER &bih(bmi->bmiHeader);
    bih.biSize = sizeof (BITMAPINFOHEADER);
    bih.biWidth         = width;
    bih.biHeight        = -height;
    bih.biPlanes        = 1;
    bih.biBitCount      = 8;
    bih.biCompression   = BI_RGB;
    bih.biSizeImage     = 0;
    bih.biXPelsPerMeter = 14173;
    bih.biYPelsPerMeter = 14173;
    bih.biClrUsed       = 0;
    bih.biClrImportant  = 0;
    for (int I = 0; I <= 255; I++)
    {
        bmi->bmiColors[I].rgbBlue = bmi->bmiColors[I].rgbGreen = bmi->bmiColors[I].rgbRed = (BYTE)I;
        bmi->bmiColors[I].rgbReserved = 0;
    }

    void *Pixels = NULL;
    HBITMAP hbmp = CreateDIBSection(hdc, bmi, DIB_RGB_COLORS, &Pixels, NULL, 0);

    if(pBits != NULL)
    {
        //fill the bitmap
        BYTE* pbBits = (BYTE*)pBits;
        BYTE *Pix = (BYTE *)Pixels;
        memcpy(Pix, pbBits, width * height);
    }

    free(bmi);

    return hbmp;
}

static HBITMAP CreateBitmapFromPixels( HDC hDC, UINT uWidth, UINT uHeight, UINT uBitsPerPixel, LPVOID pBits)
    {
           if(uBitsPerPixel < 8) // NOT IMPLEMENTED YET
              return NULL;

          if(uBitsPerPixel == 8)
              return Create8bppBitmap(hDC, uWidth, uHeight, pBits);

          HBITMAP hBitmap = 0;
          if ( !uWidth || !uHeight || !uBitsPerPixel )
             return hBitmap;
          LONG lBmpSize = uWidth * uHeight * (uBitsPerPixel/8) ;
          BITMAPINFO bmpInfo = { 0 };
          bmpInfo.bmiHeader.biBitCount = uBitsPerPixel;
          bmpInfo.bmiHeader.biHeight = uHeight;
          bmpInfo.bmiHeader.biWidth = uWidth;
          bmpInfo.bmiHeader.biPlanes = 1;
          bmpInfo.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
               // Pointer to access the pixels of bitmap
          UINT * pPixels = 0;
          hBitmap = CreateDIBSection( hDC, (BITMAPINFO *)&
                                      bmpInfo, DIB_RGB_COLORS, (void **)&
                                      pPixels , NULL, 0);

          if ( !hBitmap )
              return hBitmap; // return if invalid bitmaps

          //SetBitmapBits( hBitmap, lBmpSize, pBits);
          // Directly Write
          memcpy(pPixels, pBits, lBmpSize );

          return hBitmap;
    }
////////////////////////////////////////tested on linux
	#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <malloc.h>
#define _height 600
#define _width 800
#define _bitsperpixel 24
#define _planes 1
#define _compression 0
#define _pixelbytesize _height*_width*_bitsperpixel/8
#define _filesize _pixelbytesize+sizeof(bitmap)
#define _xpixelpermeter 0x130B //2835 , 72 DPI
#define _ypixelpermeter 0x130B //2835 , 72 DPI
#define pixel 0xFF
#pragma pack(push,1)
typedef struct{
    uint8_t signature[2];
    uint32_t filesize;
    uint32_t reserved;
    uint32_t fileoffset_to_pixelarray;
} fileheader;
typedef struct{
    uint32_t dibheadersize;
    uint32_t width;
    uint32_t height;
    uint16_t planes;
    uint16_t bitsperpixel;
    uint32_t compression;
    uint32_t imagesize;
    uint32_t ypixelpermeter;
    uint32_t xpixelpermeter;
    uint32_t numcolorspallette;
    uint32_t mostimpcolor;
} bitmapinfoheader;
typedef struct {
    fileheader fileheader;
    bitmapinfoheader bitmapinfoheader;
} bitmap;
#pragma pack(pop)

int main (int argc , char *argv[]) {
    FILE *fp = fopen("test.bmp","wb");
    bitmap *pbitmap  = (bitmap*)calloc(1,sizeof(bitmap));
    uint8_t *pixelbuffer = (uint8_t*)malloc(_pixelbytesize);
    strcpy(pbitmap->fileheader.signature,"BM");
    pbitmap->fileheader.filesize = _filesize;
    pbitmap->fileheader.fileoffset_to_pixelarray = sizeof(bitmap);
    pbitmap->bitmapinfoheader.dibheadersize =sizeof(bitmapinfoheader);
    pbitmap->bitmapinfoheader.width = _width;
    pbitmap->bitmapinfoheader.height = _height;
    pbitmap->bitmapinfoheader.planes = _planes;
    pbitmap->bitmapinfoheader.bitsperpixel = _bitsperpixel;
    pbitmap->bitmapinfoheader.compression = _compression;
    pbitmap->bitmapinfoheader.imagesize = _pixelbytesize;
    pbitmap->bitmapinfoheader.ypixelpermeter = _ypixelpermeter ;
    pbitmap->bitmapinfoheader.xpixelpermeter = _xpixelpermeter ;
    pbitmap->bitmapinfoheader.numcolorspallette = 0;
    fwrite (pbitmap, 1, sizeof(bitmap),fp);
    memset(pixelbuffer,pixel,_pixelbytesize);
    fwrite(pixelbuffer,1,_pixelbytesize,fp);
    fclose(fp);
    free(pbitmap);
    free(pixelbuffer);
}

	return 0;
}

