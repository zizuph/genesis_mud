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
   set_short("Crowded street in the town of Flotsam");
   set_long("@@long_descr");
   
   add_item(({"crowded street","street"}),"A crowded, cobblestone " +
      "street \n");
   add_item(({"brazier","tall iron brazier","iron brazier"}),"A " +
      "tall iron brazier, its light casting dark shadows on " +
      "the walls of the surroundings buildings. \n");
   add_item("house","A tall deserted merchant's house stands to your " +
      "west. You think you see a light in one of its windows. \n");
   add_item("window","Hmm... you thought you saw a light " +
      "in this window. Must have been your imagination. \n");
   add_item(({"guild","adventurers guild"}),"The adventurers " +
      "guild of Flotsam, recently constructed for travellers as " +
      "well as the dragonarmy soldiers. \n");
   
   add_exit(FROOM + "street25","north",0);
   add_exit(FROOM + "f_board","east","@@enter",0);
   add_exit(FROOM + "street33","south",0);
   
   reset_flotsam_room();
}

string
long_descr()
{
   return tod_descr1() + tod_descr2() + "You stand in the " +
   "eastern parts of Flotsam. The street runs north and south " +
   "while to your west stands a tall house that may have been " +
   "the home of a rich merchant, but is now in disrepair and " +
   "seems deserted. To your east stands a recently constructed " +
   "adventurers guild. A tall iron brazier stands on a sidewalk, " +
   "relieving little of Flotsam's gloomy atmosphere. " +
   season_descr() + "\n";
}

int
enter()
{
   write("You enter the Adventurers guild... \n");
   return 0;
}
