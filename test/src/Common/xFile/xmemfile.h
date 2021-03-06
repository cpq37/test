#if !defined(__xmemfile_h)
#define __xmemfile_h

#include "xfile.h"

//////////////////////////////////////////////////////////
class  CxMemFile : public CxFile
{
public:
	CxMemFile(unsigned char* pBuffer = NULL, unsigned long size = 0);
	~CxMemFile();

	bool Open();
	unsigned char*  GetBuffer(bool bDetachBuffer = true);

	virtual bool	Close();
	virtual size_t	Read(void *buffer, size_t size, size_t count);
	virtual size_t	Write(const void *buffer, size_t size, size_t count);
	virtual bool	Seek(long offset, int origin);
	virtual long	Tell();
	virtual long	Size();
	virtual bool	Flush();
	virtual bool	Eof();
	virtual long	Error();
	virtual bool	PutC(unsigned char c);
	virtual long	GetC();

protected:
	void	Alloc(unsigned long nBytes);
	void	Free();

	unsigned char*	m_pBuffer;
	unsigned long	m_Size;
	bool			m_bFreeOnClose;
	long			m_Position;	//current position
	long			m_Edge;		//buffer size
};

#endif
