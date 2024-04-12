/*
Напишите функцию, которая инвертирует только выбранные биты в участке памяти, 
заданном указателем и длиной в байтах. Способ выбора битов для инвертирования 
на ваше усмотрение.
*/

#include <cstdint>
#include <iostream>
#include <bitset>
#include <cassert>

using namespace std::literals;

template <typename Pointer, typename Mask>
void Invert(Pointer ptr, size_t length, Mask mask) {
	for (size_t i = 0; i < length; ++i) {
		ptr[i] ^= mask;
	}
}

void Test() {
	//uint16_t test 
	{
		uint16_t a = 0b1111111111111111;
		Invert(&a, sizeof(a), 0b10101010);
		assert(a == 0b1111111101010101);
		Invert(&a, sizeof(a), 0b10101010);
		assert(a == 0b1111111111111111);
	}
	//uint32_t test 
	{
		uint32_t a = 0b11111111111111111111111111111111;
		Invert(&a, sizeof(a), 0b11111111111111111111111111111111);
		assert(a == 0b00000000000000000000000000000000);
		Invert(&a, sizeof(a), 0b11111111111111111111111111111111);
		assert(a == 0b11111111111111111111111111111111);
	}

}

int main() {
	Test();

	uint8_t a = 0b11111111;
	const size_t size = sizeof(a);
	uint8_t* p = &a;
	uint8_t mask = 0b00000001;

	std::cout << "basic bits    "s << std::bitset<size*8>(a) << std::endl;

	Invert(p, size, mask);
	std::cout << "inverter bits "s << std::bitset<size*8>(a) << std::endl;

	Invert(p, size, mask);
	std::cout << "inverter back "s << std::bitset<size*8>(a) << std::endl;
}