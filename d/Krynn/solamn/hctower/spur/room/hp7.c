// hp7
// room with locked door opening into Level 1 hall
// grace apr 1995
// gold and rose banners (courtesy of Teth) added 2/23/96

#include "../local.h"
inherit SPURRM;

object ban4, ban5;

void
reset_spur_room()
{                                                                       
/*
    if (!ban4)
      (ban4 = clone_object(SOBJ + "goldbnr"))->move(TO);
    if (!ban5)
      (ban5 = clone_object(SOBJ + "rosebnr"))->move(TO);
*/
}  

void
create_spur_room()
{

   SHORT("Hidden hallway");
   LONG("This end of the hallway appears to be of more recent "+
        "construction than the western section, but it is quite "+
        "old nonetheless.\n");

   clone_object(SOBJ + "l1d4b")->move(TO);

   AE(ROOM + "hp6", "west", 0);

   AI(({"floor","stone floor"}),
      "It is so shiny you can see your reflection in it.\n");
   AI(({"reflection", "my reflection"}), "Yes, sure enough, that "+
      "is a distorted image of your face. At least, you hope it "+
      "is distorted. You've seen draconians prettier than that!\n");
   AI(({"stair", "stairwell"}), "It is circular and winds upward.\n");
   AI(({"torch", "torches"}), "They are just like all the others "+
      "you have seen here in the Knights' Spur.\n");

   reset_spur_room();
}

