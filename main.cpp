#include "Header/Utils.h"
#include <ctime>
using namespace std;

int main(int argc, char* argv[]) {
	srand(time(0));
  
	Game MyGame;
	MyGame.run();
  
	return 0;
}
