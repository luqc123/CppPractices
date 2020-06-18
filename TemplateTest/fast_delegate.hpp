#pragma once

//Helper templates 

namespace fast_delegate {
	namespace detail {
		template <class OutputClass, class InputClass>
		OutputClass implicit_cast(InputClass input) {
			return input;
		}

		template <class OutputClass, class InputClass>
		union horrible_union {
			OutputClass out;
			InputClass in;
		};

		//compile time check
		template <class OutputClass, class InputClass>
		inline OutputClass horrible_cast(const InputClass input) {
			horrible_union<OutputClass, InputClass> u;
			typedef int ERROR_CanUseHorrible_cast[sizeof(InputClass) == sizeof(u) && sizeof(OutputClass) == sizeof(InputClass) ? 1 : -1];
			u.in = input;
			return u.out;
		}

#define FASTDELEGATEDECLARE(CLASSNAME) class CLASSNAME;

		typedef void DefaultVoid;

		template<class T>
		struct DefaultVoidToVoid{
			typedef T type
		};

		template<>
		struct DefaultVoidToVoid<DefaultVoid> { typedef void type; };

		template<class T>
		struct VoidToDefaultVoid { typedef DefaultVoid type; };

		template<>
		struct VoidToDefaultVoid<void> { typedef DefaultVoid type; };
	}
}
