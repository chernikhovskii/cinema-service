#include <iostream>
#include "src/Cinema.hh"
#include "src/Service.hh"
using namespace std;

int main()
{
    Service service;
    service.Init();
    service.Run();
    return 0;
}
