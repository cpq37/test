#ifndef IMAGAGEMGR_H
#define IMAGAGEMGR_H

#include <vector>
#include <map>
#include <cassert>

#include "handle.h"
#include "handlemgr.h"

struct tagImage  {  };
typedef Handle <tagImage> HImage;

struct ImageData
{

};

class ImageMgr
{
public:

// Lifetime.

	ImageMgr( void )  {  /* ... */  }
	~ImageMgr( void );

// Texture management.

	HImage GetTexture   ( const char* name );
	void     DeleteTexture( HImage himg );
};


#endif	//IMAGAGEMGR_H
