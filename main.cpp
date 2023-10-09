#include "userinterface.hpp"
#include <locale>

int main() {
    setlocale(LC_ALL, "Spanish");
    new UserInterface();
}
