#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/balifor/flotsam/local.h"

inherit FLOTSAM_IN;

void
reset_flotsam_room()
{
   return;
}

create_flotsam_room()
{
   set_short("Top of stairs");
   set_long("@@long_descr");
   
   add_exit(FROOM + "upper_inn03","west","@@enter",0);
   add_exit(FROOM + "inn02","down","@@down",0);
   
   reset_flotsam_room();
}

string
long_descr()
{
   return "You stand at the top of the stairway. To your west " +
   "is an open door that leads into the inn's most luxurious " +
   "room. The stairway leads back down to the bottom floor " +
   "of the inn.\n";
}

int
enter()
{
   write("You enter the luxurious room...\n");
   return 0;
}

int
down()
{
   write("You climb down the staircase...\n");
   return 0;
}
