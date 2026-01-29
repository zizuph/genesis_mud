// hp7
// room with locked door opening into Level 1 hall
// grace apr 1995
// silver and sword banners (courtesy of Teth) added 2/23/96

#include "../local.h"
inherit SPURRM;

object ban6, ban7;

void
reset_spur_room()
{                                                                       
/*
    if (!ban6)
      (ban6 = clone_object(SOBJ + "slvrbnr"))->move(TO);
    if (!ban7)
      (ban7 = clone_object(SOBJ + "swrdbnr"))->move(TO);
*/
}  

void 
create_spur_room()
{

   SHORT("Hidden hallway");
   LONG("This end of the hallway appears to be of ancient "+
        "construction, much older than the eastern section.  "+
        "These stones were cut and laid long ago, yet there "+
        "are no visible signs of decay.  There is an archway "+
        "leading south.\n");

   AE(ROOM + "hp6", "east", 0);
   AE(ROOM + "train3", "south", 0);

   AI(({"floor","stone floor"}),
      "It is so shiny you can see your reflection in it.\n");
   AI(({"reflection", "my reflection"}), "Yes, sure enough, that "+
      "is a distorted image of your face. At least, you hope it "+
      "is distorted. You've seen draconians prettier than that!\n");
   AI(({"stair", "stairwell"}), "It is circular and winds upward.\n");
   AI(({"torch", "torches"}), "They are just like all the others "+
      "you have seen here in the Knights' Spur.\n");
   AI(({"arch", "archway"}),
     "Through it can be seen a brightly lighted room.\n");

   reset_spur_room();
}

