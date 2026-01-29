inherit "/d/Gondor/common/room";

#include <stdproperties.h>

create_room() {
   set_short("West guardroom");
   set_long("This is the western guardroom. Here the troops, which aren't on duty, eat\n"+
   "and relax. On the west side of the room there is a table filled with \n"+
      "empty kitchen attributes and such things. But you do not want to mess with\n"+
      "their things so you look around and spot some beds along the south wall, but\n"+
     "again those aren't of your business. In the northwest corner there is a \n"+
     "staircase leading upwards, and the gates are to the east.\n");
   add_exit("/d/Gondor/rohan/edoras/gat_stairs","up",0);
   add_exit("/d/Gondor/rohan/edoras/gate","east",0);
   add_prop(ROOM_I_INSIDE,1);
   add_item(({"bed","beds"}),"These are regular beds, not so different from your own.\n");
   add_item("table","This is an oaktable filled with jugs and cups and plates.\n");
}

