#include "userinterface.hpp"
#include <locale>

using namespace std;

int main() {
    setlocale(LC_ALL, "Spanish");
    new UserInterface();
}
