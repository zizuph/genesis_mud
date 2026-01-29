#include "/sys/macros.h"
#include "/sys/stdproperties.h"
inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
/* modified by Antharanos */
create_room()
{
   ::create_room();
   set_short("Road to Trading Square");
   set_long("You are on a road to Trading Square. To the north you see "
      +"@@people_square@@" + "On Trading Square "
      +"there are lots of interesting stores, restaurants and "
      +"other trading companies. To the south is the road leading to "
      +"Cliffside Road, the southern border of Kabal.\n");
   add_exit(TRADE(ts1),"south");
   add_exit(TRADE(tsquare/t1),"north");
   add_item(({"square","trading square"}),"The Trading Square is "
      +"@@busy_square@@" + "right now.\n");
   set_time_desc("There are many people walking through and "
      +"from Trading Square.\n","The streets are deserted "
      +"right now.\n");
   
   hear_bell = 2;
}

string
busy_square()
{
   if (DAY) 
      return "quite crowded ";
   return "very quiet ";
}

string
people_square()
{
   if (DAY)
      return "lots of people walking on Trading Square. ";
   return "a deserted Trading Square. ";
}

