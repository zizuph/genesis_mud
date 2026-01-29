/* room coded by Elizabeth Cook/Mouse, September 1996 */

inherit "std/room";
#include <stdproperties.h>
#include <ss_types.h>
#include "../../mouse.h"

   void create_room() {
     add_prop(ROOM_I_LIGHT,1);
     add_prop(ROOM_I_INSIDE, 1);
     set_short("In the tunnel");
     set_long("   You are inside a water-filled tunnel which inclines "+
          "further into the heart of the beaver lodge. The walls are "+
          "rough in spots where the beavers were required to crudely "+
          "gnaw through the branches and roots jutting from the mud. "+
          "Light barely shines in from beneath you at the entrance, "+
          "and from above you in the heart of the lodge itself. Your "+
          "lungs are beginning to ache from holding your breath for "+
          "so long, hopefully the light above will lead you to air.\n");
     add_item("walls", "The walls are not much to look at, just mud "+
          "with the nubs of roots and branches sticking out.\n");
     add_item("branches","All you can see is chewed off nubs.\n"); 
     add_item("roots", "All you can see is chewed off nubs.\n");
     add_item("mud", "Slimy, brown, wet dirt.\n");
     add_item("entrance", "The opening of the tunnel at the base of "+
          "the mound. You can leave the lodge through the opening by "+
          "swimming down.\n");
     add_exit(ROOT+"pond/rooms/beaver_room2","swim","@@swim_func",5,1);
     add_exit(ROOT+"pond/rooms/beaver_room4","swim","@@swim_func2",5,1);  
}

int swim_func() {
   if(query_dircmd()=="down")
     return 0;
   return 2;
}
int swim_func2() {
   if((query_dircmd()!="up")&&(query_dircmd()!="down"))
   {
      write("It is impossible to swim that direction.\n");
      return 1;
   }
   return 0;
}
