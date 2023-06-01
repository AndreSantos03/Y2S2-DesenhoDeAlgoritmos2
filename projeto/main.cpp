#include "include/Menu.h"


using namespace std;

int main() {
    try{
        Menu menu;
        menu.display();
        return 0;
    }
    catch(const std::exception& e)
    {
        std::cout << e.what();
    }
}
