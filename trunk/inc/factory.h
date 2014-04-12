#ifndef __YATL_FACTORY_H__
#define __YATL_FACTORY_H__

#include "typelist.h"

namespace yatl {

template<class T> struct NewCreaterPolicy {
	static T* Create(const T &t) {
		return new T;
	}
};

template<class T> struct CloneCreaterPolicy {
	static T* Create(const T &t) {
		return new T(t);
	}
};

template<class T, template <class> class Creator> class FactoryBase;
template<class T, template <class> class Creator> class FactoryBase<TypeList<T, NullType>, Creator> {
public:
	FactoryBase() {}
	FactoryBase(const Tuple<TypeList<T, NullType>> &t) : t_(t.value_) {}

	T* Create(Type2Type<T>) {
		return Creator<T>::Create(t_);
	}

private:
	T t_;
};

template<class T, class U, template <class> class Creator>
class FactoryBase<TypeList<T, U>, Creator> : public FactoryBase<U, Creator>{
public:
	FactoryBase() {
		static_assert(IsAllUniqueTypeList<TypeList<T, U>>::Value, "Need Unique Type in the TypeList");
	}
	FactoryBase(const Tuple<TypeList<T, U>> &t) : FactoryBase<U, Creator>((Tuple<U> &)t), t_(t.value_) {
		static_assert(IsAllUniqueTypeList<TypeList<T, U>>::Value, "Need Unique Type in the TypeList");
	}

	T* Create(Type2Type<T>) {
		return Creator<T>::Create(t_);
	}

private:
	T t_;
};

template<class T, template <class> class Creator> class FactoryHolder 
: public FactoryBase<T, Creator> {
public:
	FactoryHolder() {}
	FactoryHolder(const Tuple<T> &t) : FactoryBase(t) {}

	template<class U>
	U* Create() {
		FactoryBase<typename FindTypeList<T, U>::Result, Creator> &obj = *this;
		return obj.Create(Type2Type<U>());
	}
};

}

#endif