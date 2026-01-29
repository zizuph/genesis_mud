#include "defs.h"

CONSTRUCT_ROOM
{
   set_short("Bedroom");
   set_long("You have entered a nice and cosy bedroom!\n" +
      "Obviously, the dwarves which lived here in the western " +
      "parts of Moria needed to rest. There are many rows of beds " +
      "standing here, though they have not been used for ages, " +
      "considering the amount of dust and web which have grown " +
      "here during centuries. There is a dark passage leading " +
      "eastwards towards a crossing of some sort.\n");
   add_item(({"passage","archway"}),
      "The passage leads towards a crossing.");
   add_item(({"beds", "bed", "rows"}),
      "They seems to have been unused for a long time.\n");
   add_cmd_item(({"into the bed","into a bed","into bed","bed"}),
      ({"climb","enter","sleep"}),"@@my_bed@@");
   EAST("cross");
}

string
my_bed()
{
   say(QCTNAME(TP)+" jumps into a bed, but decides not to say in it "+
      "for too long, since it is full of dust!\n");
   return "You jump into a bed, but decide not to stay in it, "+
   "since it is full of dust!";
}

