/*
 Copyright (c) 2016 Jacob Gordon. All rights reserved.
 
 Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:
 
 1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.
 
 2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the
 documentation and/or other materials provided with the distribution.
 
 THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR
 TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef JHGPixels_JHGPixelslib_h
#define JHGPixels_JHGPixelslib_h

typedef float JHGFloat ;
typedef int JHGInt ;
typedef unsigned char JHGsubpixel ;
typedef JHGsubpixel* JHGRawData ;
typedef enum { JHGBYTERGB, JHGBYTERBG, JHGINT8888REVBGRA} JHGPixelFormatType ;
typedef struct { JHGsubpixel r ; JHGsubpixel g ; JHGsubpixel b ; } JHGPixelcolor_Object ;
typedef void (*JHGPixelsFormatFunc)(JHGRawData pixelarray, int rk, JHGsubpixel red, JHGsubpixel blue, JHGsubpixel green) ;
typedef void (*JHGPixelsGetFunc)(JHGRawData pixelarray, int rk, JHGsubpixel* red, JHGsubpixel* blue, JHGsubpixel* green) ;
typedef struct { JHGPixelcolor_Object background ;  JHGRawData pixelarray ; JHGPixelsFormatFunc format ; JHGPixelsGetFunc get ;
int f_size ; int x ; int y ; } JHGPixels_scene_object ;
typedef JHGPixels_scene_object* JHGPixels_scene ;

JHGPixels_scene JHGPixels_newscene( int x, int y, JHGPixelcolor_Object background, JHGPixelFormatType format ) ;
void JHGPixels_SetBackGroundColor(JHGPixels_scene scene, JHGsubpixel red, JHGsubpixel blue, JHGsubpixel green) ;
void JHGPixels_BlockCopy( JHGPixels_scene scene, int x, int y, int src_size, JHGRawData src ) ;
void JHGPixels_SetPixel( JHGPixels_scene scene, int x, int y, JHGsubpixel red, JHGsubpixel blue, JHGsubpixel green ) ;
void JHGPixels_GetPixel( JHGPixels_scene scene, int x, int y, JHGsubpixel* red, JHGsubpixel* blue, JHGsubpixel* green ) ;
void JHGPixels_FastMonoColorSet( JHGsubpixel pixelarray[], const JHGsubpixel value, const int size ) ;
void JHGPixels_FastColorSet( JHGsubpixel pixelarray[], const JHGsubpixel red, const JHGsubpixel blue, const JHGsubpixel green, const int size, const int f_size, JHGPixelsFormatFunc format ) ;
void JHGPixels_Reset( JHGPixels_scene scene, JHGsubpixel red, JHGsubpixel blue, JHGsubpixel green ) ;
void JHGPixels_ResetFast( JHGPixels_scene scene, JHGsubpixel value ) ;
void JHGPixels_ResetWithBackGround( JHGPixels_scene scene ) ;
void JHGPixels_ResetWithNoBackGround( JHGPixels_scene scene ) ;
void JHGPixels_scenefree( JHGPixels_scene scene ) ;

void* JHG_DrawPixels(JHGPixels_scene pixelframe, int *x, int *y) ;

#endif
