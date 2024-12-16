#include "Day_01/Day_01.h"
#include "Day_02/Day_02.h"
#include "Day_03/Day_03.h"
#include "Day_04/Day_04.h"
#include "Day_05/Day_05.h"
#include "Day_06/Day_06.h"

int main()
{
   const auto day_01 = new Day_01();
   const auto day_02 = new Day_02();
   const auto day_03 = new Day_03();
   const auto day_04 = new Day_04();
   const auto day_05 = new Day_05();
   const auto day_06 = new Day_06();

   //day_01->Run();
   //day_02->Run();
   //day_03->Run();
   //day_04->Run();
   //day_05->Run();
   day_06->Run();

   return 0;
}
