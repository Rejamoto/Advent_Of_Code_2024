#include "Day_01/Day_01.h"
#include "Day_02/Day_02.h"
#include "Day_03/Day_03.h"
#include "Day_04/Day_04.h"

int main()
{
   const auto day_01 = new Day_01();
   const auto day_02 = new Day_02();
   const auto day_03 = new Day_03();
   const auto day_04 = new Day_04();

   //day_01->Run();
   //day_02->Run();
   //day_03->Run();
   day_04->Run();

   return 0;
}
