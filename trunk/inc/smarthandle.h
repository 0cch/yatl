#ifndef __SMART_HANDLE_H__
#define __SMART_HANDLE_H__

namespace yatl {

#include <windows.h>
#include <Wininet.h>

template<class H> struct FileClosePolicy;
template<> struct FileClosePolicy<HANDLE> {
	static void Close(HANDLE h)
	{
		if (h != NULL && h != INVALID_HANDLE_VALUE) {
			CloseHandle(h);
		}
	}
};

template<> struct FileClosePolicy<FILE *> {
	static void Close(FILE * h)
	{
		if (h != NULL) {
			fclose(h);
		}
	}
};

template<class H> struct RegClosePolicy;
template<> struct RegClosePolicy<HKEY> {
	static void Close(HKEY h)
	{
		if (h != NULL) {
			RegCloseKey(h);
		}
	}
};

template<class H> struct FindClosePolicy;
template<> struct FindClosePolicy<HANDLE> {
	static void Close(HANDLE h)
	{
		if (h != NULL) {
			FindClose(h);
		}
	}
};

template<class H> struct IntenetClosePolicy;
template<> struct IntenetClosePolicy<HINTERNET> {
	static void Close(HINTERNET h)
	{
		if (h != NULL) {
			InternetCloseHandle(h);
		}
	}
};


template<class H> struct NoTransferPolicy {
};

template<class H> struct CopyPolicy {
	static void Copy(H& dst, const H& src) {
		dst = src;
	}
};

template<class H> struct DestoryCopyPolicy {
	static void Copy(H& dst, const H& src) {
		dst = src;
		const_cast<H&>(src) = NULL;
	}
};

template<class H> struct MovePolicy {
	static void Move(H& dst, H& src) {
		dst = src;
		src = NULL;
	}
};

template
	<
		class H,
			template <class> class ClosePolicy,
			template <class> class TransferPolicy
	>
class SmartHandle {
public:
	SmartHandle() : h_(H()) {}
	SmartHandle(H h) : h_(h) {}
	SmartHandle(const SmartHandle &h)
	{
		TransferPolicy<H>::Copy(h_, h.h_);
	}
	SmartHandle(SmartHandle &&h)
	{
		TransferPolicy<H>::Move(h_, h.h_);
	}
	~SmartHandle()
	{
		ClosePolicy<H>::Close(h_);
		h_ = H();
	}
	SmartHandle& operator = (const SmartHandle& h)
	{
		TransferPolicy<H>::Copy(h_, h.h_);
		return *this;
	}
	SmartHandle& operator = (SmartHandle&& h)
	{
		TransferPolicy<H>::Move(h_, h.h_);
		return *this;
	}

	operator H () const
	{
		return h_;
	}

	H Attach(H h) {
		H tmp = h_;
		h_ = h;
		return tmp;
	}

	H Detach() {
		H tmp = h_;
		h_ = H();
		return tmp;
	}

	H Get() const
	{
		return h_;
	}

	friend class ClosePolicy;
	friend class TransferPolicy;

private:
	H h_;
};

typedef SmartHandle<HANDLE, FileClosePolicy, MovePolicy> SmartFileHandle;
}

#endif