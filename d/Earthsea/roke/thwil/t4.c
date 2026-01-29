#include "defs.h"
inherit THWIL_BASE_ROOM;

void create_thwil_room()
{
   set_short("Street");
   set_long("You are in the southern part of Thwil, bordered on "+
      "the sides by solid log houses and on one side by the "+
      "wall of a great building. "+
      "The air is cold and damp. There's a feeling of "+ 
      "magic surrounding you. You can see the local bank to the west " +
      "and a newly constructed building to the south. " +
      "The street slopes upwards to the east and down to the north.\n");
   
   add_exit(THWIL + "t5" , "north" , 0, 1);
   add_exit(THWIL + "t3" , "east" , 0, 1);
   add_exit(THWIL + "notary", "south", 0, 1);
   add_exit(THWIL + "bank" , "west" , 0, 1);
   
   STREET;
}







