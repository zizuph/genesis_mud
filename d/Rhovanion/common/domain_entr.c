inherit "/std/room";
#include <stdproperties.h>

create_room()
{
   set_short("Rhovanion's entrance");
   set_long(break_string("This is the wizard's entrance to "
         + "the Rhovanion domain. To the east is the domain "
         + "tower. You see the Rhovanion meeting room just to "
         + "the south. \n",70));
   add_exit("/d/Rhovanion/workroom","south");
   add_exit("/d/Genesis/wiz/dom_b1","east");
}
