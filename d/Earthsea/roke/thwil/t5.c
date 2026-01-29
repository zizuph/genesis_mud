#include "defs.h"
inherit THWIL_BASE_ROOM;

void create_thwil_room()
{
   set_short("Street");
   set_long("This is an ordinary street in Thwil. "+
      "The air is cold and damp. To the north you spot "+
      "a large administrative building, judging "+
      "from the busy people walking in and out. "+
      "Northeast a hill towers over you while the city "+ 
      "continues down to the south. The town continues " +
      "to the west.\n");
   
   add_item(({"building","house"}),"The height of the building has"+
      " clearly the purpose to dwarf you. \n");
   
   add_exit(THWIL + "t8" , "northeast" , 0, 2);
   add_exit(THWIL + "board" , "north" ,0);
   add_exit(THWIL + "t4" , "south" , 0);
   add_exit(THWIL + "tb", "west", 0);
   
   STREET;
}
