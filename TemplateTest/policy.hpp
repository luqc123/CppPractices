#ifndef POLICY_H
#define POLICY_H

class Widget;

template <class T>
struct OpNewCreator {
	static T* Create() {
		return new T;
	}
};

template <class T>
struct MallocCreator {
	static T* Create() {
		void* buf = malloc(sizeof(T));
		if (!buf) return 0;
		return new(buf) T;
	}
};

template <class T>
struct PrototypeCreator {
	PrototypeCreator(T* pObj=nullptr):pPrototype_(pObj) {}
	T* Create() {
		return pPrototype_ ? pPrototype_->Clone() : 0;
	}
	T* GetPrototype() {
		return pPrototype_;
	}
	void SetPrototype(T* pObj) {
		pPrototype_ = pObj;
	}
private:
	T* pPrototype_;
};

template<class CreationPolicy>
class WidgetManager1 : public CreationPolicy {};

template<template<class Created> class CreationPolicy>
class WidgetManager2 : public CreationPolicy<Widget> {
public:
	void SwitchPrototype(Widget* pNewPrototype) {
		CreationPolicy<Widget>& myPolicy = *this;
		delete myPolicy.GetPrototype();
		myPolicy.SetPrototype(pNewPrototype);
	}
};

template<template<class Created> class CreationPolicy=OpNewCreator>
class WidgetManager3 : public CreationPolicy<Widget> {
};

template<class T>
class DefaultSmartPtrStorage {
public:
	typedef T* PointerType;
	typedef T& ReferenceType;
protected:
	PointerType GetPointerTpye() {
		return point_;
	}
	void SetPointerType(PointerType ptr) {
		point_ = ptr;
	}
private:
	PointerType point_;
};

template<
	class T,
	template<class> class Storage = DefaultSmartPtrStorage
>
class SmartPtr;

#endif