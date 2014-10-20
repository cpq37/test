#ifndef FUI_IMAGESFACTORY_H
#define FUI_IMAGESFACTORY_H

#include "imagemgr.h"

class FUI_ImagesFactory : public ImageMgr
{
public:
    FUI_ImagesFactory();
    ~FUI_ImagesFactory();

    bool		SaveImagesToFile(const char* file=NULL);
    bool		ReadImagePacket(const char* file=NULL);

    static FUI_ImagesFactory* GetInstance();
private:
    static FUI_ImagesFactory *m_singelton;
};

#endif // FUI_IMAGESFACTORY_H
