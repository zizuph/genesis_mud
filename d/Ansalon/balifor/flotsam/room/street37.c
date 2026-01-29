#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/balifor/flotsam/local.h"

inherit FLOTSAM_OUT;

void
reset_flotsam_room()
{
   return;
}

create_flotsam_room()
{
   set_short("Gates of Flotsam");
   set_long("@@long_descr");
   
   add_item(({"iron gates","gates","gate","grim iron gates"}),
      "Double iron " +
      "gates rise before you, opening outwards into the lands of " +
      "Goodlund.\n");
   add_item("guardrooms","Two stone guardrooms stand to your " +
      "east and west, where soldiers of the Dragonarmies ordered " +
      "to guard the main gates rest. \n");
   add_item(({"centre","town","flotsam"}),"To the north " +
      "is the wretched town of Flotsam, currently occupied by the " +
      "dragonarmies of the Dark Queen.\n");
   
   add_exit(FROOM + "street36","north",0);
   add_exit(FROOM + "guard04","east","@@guard",0);
   add_exit("/d/Ansalon/balifor/flotsam_forest/room/roada","south","@@pass");
   add_exit(FROOM + "guard03","west","@@guard",0);
   
   reset_flotsam_room();
}

string
long_descr()
{
   return tod_descr1() + tod_descr2() + "You stand at the grim " +
   "iron gates of Flotsam. To your east and west are guardrooms, " +
   "while to your north lies the centre of town. To your south are " +
   "the gates, which are at present standing open. " +season_descr() +
   "\n";
}

int
guard()
{
   write("You enter the guardroom... \n");
   return 0;
}

int
pass()
{
   write("You pass through the gates of Flotsam...\n");
   return 0;
}

int
no_exit()
{
   write("The gates are closed by orders of the Blue Lady! \n");
   return 1;
}
