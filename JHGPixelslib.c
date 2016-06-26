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


//There are several major bugs here, good thing JHGPixels forms the basis of the graphics stack! --sarcasm--

#include <stdlib.h>
#include <string.h>
#include "JHGPixelslib.h"

void JHGPixels_FastMonoColorSet( JHGsubpixel pixelarray[], const JHGsubpixel value, const int size ) {
    
    int rk = 0 ;
    
    while ( rk < size ) {
        
        pixelarray[rk] = value ;
        
        rk++ ;
    }
}

void JHGPixels_FastColorSet( JHGsubpixel pixelarray[], const JHGsubpixel red, const JHGsubpixel blue, const JHGsubpixel green, const int size, const int f_size, JHGPixelsFormatFunc format ) {
    
    int rk = 0 ;
    
    while ( rk < size ) {

        format(pixelarray, rk, red, blue, green) ;
        
        rk+=f_size ;
    }
}

void JHGPixels_Reset( JHGPixels_scene scene, JHGsubpixel red, JHGsubpixel blue, JHGsubpixel green ) {
    
    JHGPixels_FastColorSet( scene->pixelarray, red, blue, green, ( scene->x * (scene->y * scene->f_size) ), scene->f_size, scene->format ) ;
}

void JHGPixels_ResetFast( JHGPixels_scene scene, JHGsubpixel value ) {
    
    JHGPixels_FastMonoColorSet( scene->pixelarray, value, ( scene->x * (scene->y * scene->f_size) ) ) ;
}

void JHGPixels_ResetWithBackGround( JHGPixels_scene scene ) {
 
    JHGPixels_Reset( scene, scene->background.r, scene->background.b, scene->background.g ) ;
}

void JHGPixels_ResetWithNoBackGround( JHGPixels_scene scene ) {
    
    JHGPixels_ResetFast( scene, 0 ) ;
}

static void JHGPixels_init( JHGPixels_scene scene )  {
    
    int i = 0 ;
    
    int j = 0 ;
        
          while ( i < (scene->x ) ) {
            
              j = 0 ;
            
              while ( j < (scene->y ) ) {
                
                  JHGPixels_SetPixel(scene, i, j, scene->background.r, scene->background.b, scene->background.g) ;
                
                 j++;
              }
         i++ ;
    }
}

static void JHGPixels_INT_8_8_8_8_REV_BGRA( JHGRawData pixelarray, int rk, JHGsubpixel red, JHGsubpixel blue, JHGsubpixel green ) {
    
    pixelarray[rk] = blue ;
    
    pixelarray[rk + 1] = green ;
    
    pixelarray[rk + 2] = red ;
    
    pixelarray[rk + 3] = 0 ;
}

static void JHGPixels_INT_8_8_8_8_REV_BGRA_GET( JHGRawData pixelarray, int rk, JHGsubpixel* red, JHGsubpixel* blue, JHGsubpixel* green ) {
    
    *blue = pixelarray[rk] ;
    
    *green = pixelarray[rk + 1] ;
    
    *red = pixelarray[rk + 2] ;
    
    //pixelarray[rk + 3] ;
}


static void JHGPixels_BYTE_RGB( JHGRawData pixelarray, int rk, JHGsubpixel red, JHGsubpixel blue, JHGsubpixel green ) {
    
    pixelarray[rk] = red ;
    
    pixelarray[rk + 1] = green ;
    
    pixelarray[rk + 2] = blue ;
}

static void JHGPixels_BYTE_RGB_GET( JHGRawData pixelarray, int rk, JHGsubpixel* red, JHGsubpixel* blue, JHGsubpixel* green ) {
    
    *red = pixelarray[rk] ;
    
    *green = pixelarray[rk + 1] ;
    
    *blue = pixelarray[rk + 2] ;
}

static void JHGPixels_BYTE_RBG( JHGRawData pixelarray, int rk, JHGsubpixel red, JHGsubpixel blue, JHGsubpixel green ) {
    
    pixelarray[rk] = red ;
    
    pixelarray[rk + 1] = blue ;
    
    pixelarray[rk + 2] = green ;
}

static void JHGPixels_BYTE_RBG_GET( JHGRawData pixelarray, int rk, JHGsubpixel* red, JHGsubpixel* blue, JHGsubpixel* green ) {
    
    *red = pixelarray[rk] ;
    
    *blue = pixelarray[rk + 1] ;
    
    *green = pixelarray[rk + 2] ;
}

static void JHGPixels_SetFormat( JHGPixels_scene scene, JHGPixelFormatType format ) {
    
    scene->format_type = format ;
    
    switch (format) {
            
        case JHGBYTERGB:
            
            scene->format = JHGPixels_BYTE_RGB ;
            
            scene->get = JHGPixels_BYTE_RGB_GET ;
            
            scene->f_size = 3 ;
            
            break;
            
        case JHGBYTERBG:
            
            scene->format = JHGPixels_BYTE_RBG ;
            
            scene->get = JHGPixels_BYTE_RBG_GET ;
            
            scene->f_size = 3 ;
            
            break;
            
        case JHGINT8888REVBGRA:
            
            scene->format = JHGPixels_INT_8_8_8_8_REV_BGRA ;
            
            scene->get = JHGPixels_INT_8_8_8_8_REV_BGRA_GET ;
            
            scene->f_size = 4 ;
            
            break;
            
        default:
            break;
    }
}

JHGPixels_scene JHGPixels_newscene( int x, int y, JHGPixelcolor_Object background, JHGPixelFormatType format ) {
    
    JHGPixels_scene newscene ;
    
    newscene = (JHGPixels_scene) malloc(sizeof(JHGPixels_scene_object)) ;
    
    if ( newscene == NULL ) return NULL ;
    
    JHGPixels_SetFormat(newscene,format) ;
    
    newscene->x = x ;
    
    newscene->y = y ;
    
    newscene->background = background ;
    
    newscene->pixelarray = (JHGRawData) malloc( (newscene->x * newscene->y * newscene->f_size) ) ;
        
    if ( newscene->pixelarray == NULL ) return NULL ;
    
    JHGPixels_init(newscene) ;
    
    return newscene ;
}

void JHGPixels_SetBackGroundColor( JHGPixels_scene scene, JHGsubpixel red, JHGsubpixel blue, JHGsubpixel green ) {
    
    scene->background.r = red ;
    
    scene->background.b = blue ;
    
    scene->background.g = green ;
}

JHGPixels_scene JHGPixels_SceneClone( JHGPixels_scene scene ) {
    
    JHGPixels_scene clone = JHGPixels_newscene(scene->x, scene->y, scene->background, scene->format_type) ;
    
    JHGPixels_FullCopy(clone, scene) ;
    
    return clone ;
}

JHGPixels_scene JHGPixels_SceneMerge( JHGPixels_scene scene1, JHGPixels_scene scene2 ) {
    
    int size1 = (scene1->x * scene1->y) ;
    
    int size2 = (scene2->x * scene2->y) ;
    
    JHGPixels_scene merged = NULL ;
    
    if ( size1 == size2 ) {
        
        JHGPixels_FullCopy(scene1, scene2) ;
        
        merged = scene1 ;
        
    } else if (size1 > size2) {
        
        JHGPixels_BlockCopy(scene1, scene2, 0, 0) ;
        
        merged = scene1 ;
        
    } else if (size2 > size1) {
        
        JHGPixels_BlockCopy(scene2, scene1, 0, 0) ;
        
        merged = scene2 ;
    }
    
    return merged ;
}

JHGPixels_scene JHGPixels_BlockMerge( JHGPixels_scene scene1, JHGPixels_scene scene2, int pos_x, int pos_y ) {
    
    int size1 = (scene1->x * scene1->y) ;
    
    int size2 = (scene2->x * scene2->y) ;
    
    JHGPixels_scene merged = NULL ;
    
    if ( size1 == size2 ) {
        
        JHGPixels_BlockCopy(scene1, scene2, pos_x, pos_y) ;
        
        merged = scene1 ;
        
    } else if (size1 > size2) {
        
        JHGPixels_BlockCopy(scene1, scene2, pos_x, pos_y) ;
        
        merged = scene1 ;
        
    } else if (size2 > size1) {
        
        JHGPixels_BlockCopy(scene2, scene1, pos_x, pos_y) ;
        
        merged = scene2 ;
    }
    
    return merged ;
}

void JHGPixels_FullCopy( JHGPixels_scene dest, JHGPixels_scene src ) {
    
    memcpy(dest->pixelarray, src->pixelarray, (dest->x * dest->y) * sizeof(JHGsubpixel)) ;
}

void JHGPixels_BlockCopy( JHGPixels_scene scene, JHGPixels_scene block, int pos_x, int pos_y ) {
    
    int i = 0 ;
    
    int j = 0 ;
    
    JHGsubpixel red, blue, green ;
    
    while (i < block->x) {
        
        j = 0 ;
        
        while (j < block->y) {
            
            JHGPixels_GetPixel(block, i, j, &red, &blue, &green) ;
            
            if ( ((i+pos_x) >= 0) && ((i+pos_x) < scene->x) && ((j+pos_y) >= 0) && ((j+pos_y) < scene->y) )
            
            JHGPixels_SetPixel(scene, (i+pos_x), (j+pos_y), red, blue, green) ;
            
            j++ ;
        }
        
        i++ ;
    }

}

void JHGPixels_SetPixel( JHGPixels_scene scene, int x, int y, JHGsubpixel red, JHGsubpixel blue, JHGsubpixel green ) {
    
    int rk = ( x * scene->f_size ) + ( y * scene->x * scene->f_size ) ;
    
    scene->format(scene->pixelarray,rk,red,blue,green) ;
}

void JHGPixels_GetPixel( JHGPixels_scene scene, int x, int y, JHGsubpixel* red, JHGsubpixel* blue, JHGsubpixel* green ) {
    
    int rk = ( x * scene->f_size ) + ( y * scene->x * scene->f_size ) ;
    
    scene->get(scene->pixelarray,rk,red,blue,green) ;
}

void JHGPixels_scenefree( JHGPixels_scene scene )  {
    
    free(scene->pixelarray) ;
    
    free(scene) ;
}

void* JHG_DrawPixels(JHGPixels_scene pixelframe, int *x, int *y) {
    
    *x = pixelframe->x ;
    
    *y = pixelframe->y ;
    
    return pixelframe->pixelarray ;
    
}