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
   set_short("Gloomy street outside a run-down Inn");
   set_long("@@long_descr");
   
   add_item(({"cobblestone street","street"}),"A filthy, well-used " +
      "cobblestone street. \n");
   add_item("inn","An ugly and poorly build Inn. its fieldstone base seems " +
      "to be the only sturdy part of the whole building, and you are " +
      "surprised that the rest of the wooden structure hasn't been " +
      "blown away in one of Flotsams many storms. A sign board " +
      "swings with the wind above the door, and you manage to " +
      "make out the name of the place, 'the Jetties'. \n");
   add_item(({"alley","alleyway"}),"An uninviting alley opens " +
      "up to the south. \n");
   
   add_exit(FROOM + "street15","north",0);
   add_exit(FROOM + "street26","east",0);
   add_exit(FROOM + "inn01","west","@@enter_inn",0);
   add_invis_exit(FROOM + "street28","south","@@enter_alley",0);
   
   reset_flotsam_room();
}

string
long_descr()
{
   return tod_descr1() + tod_descr2() + "You stand on a " +
   "gloomy cobblestone street in the town of Flotsam. The " +
   "street continues to the north and east, while to the " +
   "west stands, only barely, a fairly run-down Inn. To the " +
   "south you can make out the entrance to an uninviting " +
   "alleyway. " + season_descr() + "\n";
}

int
enter_inn()
{
   write("You open the door, and step into the Inn. \n");
   return 0;
}

int
enter_alley()
{
   write("You step into the darkness of the alley... \n");
   return 0;
}
