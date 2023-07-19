#include"tetris.hpp"

int main() {
	std::srand(std::time(0));
	auto tetris = std::make_shared<Tetris>();
	tetris->run();
	return 0;
}