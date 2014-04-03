#ifndef __YATL_SINGLETON_H__
#define __YATL_SINGLETON_H__
namespace yatl {

template<class T> struct SingleNewCreatorPolicy {
	typedef T* instance_ptr;
	typedef T instance_type;
	static void Create(instance_ptr *inst)
	{
		*inst = new instance_type;
	}

	static void Destory(instance_ptr *inst)
	{
		delete *inst;
		*inst = NULL;
	}
};

template<class T> struct SingleStaticCreatorPolicy {
	typedef T* instance_ptr;
	typedef T instance_type;
	static void Create(instance_ptr *inst)
	{
		static instance_type t;;
		*inst = &t;
	}

};

template<class T, template <class> class TCreatorPolicy>
class SingletonHolder {
public:
	typedef T* instance_ptr;
	static T& Instance()
	{
		if (inst_ == NULL) {
			TCreatorPolicy<T>::Create(&inst_);
		}
		return *inst_;
	}

	static void DestoryInstance()
	{
		if (inst_ != NULL) {
			TCreatorPolicy<T>::Destory(&inst_);
		}
	}

private:
	static instance_ptr inst_;

	SingletonHolder();
};

template<class T, template <class> class TCreator>
typename SingletonHolder<T, TCreator>::instance_ptr 
	SingletonHolder<T, TCreator>::inst_ = NULL;
}

#endif