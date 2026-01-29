// hp4
// stairs to training area from 3rd level
// grace feb 1995

#include "../local.h"
inherit SPURRM;

create_spur_room()
{

   SHORT("Hidden staircase");
   LONG("Torches placed every few steps along the walls of this "+
      "circular stairwell make it possible to negotiate without "+
      "falling.\n");

   INSIDE;
   LIGHT;

   AE(ROOM + "hp3", "up", 0);
   AE(ROOM + "hp5", "down", 0);
   

   AI(({"floor","stone floor"}),
      "It is so shiny you can see your reflection in it.\n");
   AI(({"reflection", "my reflection"}), "Yes, sure enough, that "+
      "is a distorted image of your face. At least, you hope it "+
      "is distorted. You've seen draconians prettier than that!\n");
   AI(({"stair", "stairwell"}), "It is circular and winds downward.\n");
   AI(({"torch", "torches"}), "They are just like all the others "+
      "you have seen here in the Knights' Spur.\n");
}

