#include "/d/Ansalon/goodlund/nethosak/city/local.h" 
#include "/d/Ansalon/goodlund/bloodsea/local.h"
#include "/d/Ansalon/common/defs.h"
#include <stdproperties.h>

inherit MITHAS_IN;
 

void 
reset_mithas_room()
{
   return;
}


void
create_mithas_room()
{
   set_short("inside the ruins of Winston's Tower");
   set_long("@@long_descr"); 

   add_item(({"ruins","abandoned ruins","tower","winston's tower","great tower",
         "lighthouse","beacon","holy beacon","ruins"}),
     "Once a holy beacon for travellers, Winston's Tower is now abandoned, " +
     "home only to the darkness.\n");
   add_item(({"darkness","ominous darkness"}),
     "Darkness hovers around you in Winston's Tower, seemingly sucking up the " +
     "light around you.\n");
   add_item(({"staircase","stone staircase"}),
     "A stone staircase rises up the side of the walls of this great tower into " +
     "ominous darkness. It also leads down to the ground floor of the tower.\n");

   add_prop(ROOM_S_DARK_LONG,                   
     "A staircase in a dark tower. It is impossible "+
     "to see anything in the ominous darkness.\n");

   DARK;

   add_exit(BISLAND + "tower03", "up", "@@up_tower", 1);
   add_exit(BISLAND + "tower01", "down", 0, 1);

   reset_mithas_room();
}

int
up_tower()
{
   write("You continue far up the staircase, eventually coming out of the oppressive " +
      "darkness and on to the roof of the tower.\n");
   return 0;
}

string
long_descr()
{ 
   return "You are standing within the abandoned ruins of " +
      "Winston's Tower on the isle of Karthay. This great tower " +
      "was once a lighthouse that served as a holy beacon for travellers " +
      "across the lands of Istar, one of the ancient wonders of the world. " +
      "Now only the brave or foolish travel here, as the tower is rumoured " +
      "to be cursed, haunted by fell creatures better left undisturbed. A " +
      "stone staircase circles up and down the walls of the tower.\n";
}