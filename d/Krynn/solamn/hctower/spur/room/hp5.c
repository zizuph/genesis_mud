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
      "falling.\n   There is a doorway at the foot of the stairs.\n");

   INSIDE;
   LIGHT;

   AE(ROOM + "hp4", "up", 0);
   AE(ROOM + "hp6", "down", 0);
   

   AI(({"floor","stone floor"}),
      "It is so shiny you can see your reflection in it.\n");
   AI(({"reflection", "my reflection"}), "Yes, sure enough, that "+
      "is a distorted image of your face. At least, you hope it "+
      "is distorted. You've seen draconians prettier than that!\n");
   AI(({"stair", "stairwell"}), "It is circular and winds upwawrd.\n");
   AI(({"torch", "torches"}), "They are just like all the others "+
      "you have seen here in the Knights' Spur.\n");
   AI(({"door", "doorway"}), "Bright light shines into the darkened "+
	"stairwell from the doorway below.\n");

}








