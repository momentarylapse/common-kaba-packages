#include "../base/base.h"
#include "BigInt.h"
#include "../kabaexport/KabaExporter.h"

class KabaBigInt : public BigInt {
public:
	void assign_string(const string& s) {
		*(BigInt*)this = s;
	}
	void assign_int(int i) {
		*(BigInt*)this = i;
	}
};

void export_package_algebra(kaba::Exporter* e) {
	e->package_info("algebra", "0.2");

	e->declare_class_size("BigInt", sizeof(BigInt));
	e->link_class_func("BigInt.__init__:BigInt", &kaba::generic_init<BigInt>);
	e->link_class_func("BigInt.__init__:BigInt:i32", &kaba::generic_init_ext<BigInt, int>);
	e->link_class_func("BigInt.__init__:BigInt:string", &kaba::generic_init_ext<BigInt, const string&>);
	e->link_class_func("BigInt.__delete__", &kaba::generic_delete<BigInt>);
	e->link_class_func("BigInt.__assign__:BigInt:BigInt", &kaba::generic_assign<BigInt>);
	e->link_class_func("BigInt.__assign__:BigInt:string", &KabaBigInt::assign_string);
	e->link_class_func("BigInt.__assign__:BigInt:i32", &KabaBigInt::assign_int);
	e->link_class_func("BigInt.__str__", &BigInt::to_string);
	e->link_class_func("BigInt.compare", &BigInt::compare);
	e->link_class_func("BigInt.idiv", &BigInt::idiv);
	e->link_class_func("BigInt.div", &BigInt::_div);
	e->link_class_func("BigInt.count_bits", &BigInt::count_bits);
	e->link_class_func("BigInt.__eq__", &BigInt::operator==);
	e->link_class_func("BigInt.__neq__", &BigInt::operator!=);
	e->link_class_func("BigInt.__lt__", &BigInt::operator<);
	e->link_class_func("BigInt.__gt__", &BigInt::operator>);
	e->link_class_func("BigInt.__le__", &BigInt::operator<=);
	e->link_class_func("BigInt.__ge__", &BigInt::operator>=);
	e->link_class_func("BigInt.__add__", &BigInt::operator+);
	e->link_class_func("BigInt.__sub__", &BigInt::operator-);
	e->link_class_func("BigInt.__mul__", &BigInt::operator*);
	e->link_class_func("BigInt.__iadd__", &BigInt::operator+=);
	e->link_class_func("BigInt.__isub__", &BigInt::operator-=);
	e->link_class_func("BigInt.__imul__", &BigInt::operator*=);
	e->link_func("BigInt.pow", &BigInt::pow);
	e->link_func("BigInt.pow_mod", &BigInt::pow_mod);
	e->link_func("BigInt.gcd", &BigInt::gcd);
	e->link_func("BigInt.rand", &BigInt::rand);
	e->link_func("BigInt.find_coprime", &BigInt::find_coprime);
	e->link_func("BigInt.find_mod_inverse", &BigInt::find_mod_inverse);
	e->link_func("BigInt.miller_rabin_prime", &BigInt::miller_rabin_prime);
}

