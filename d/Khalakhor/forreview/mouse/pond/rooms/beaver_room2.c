/* room coded by Elizabeth Cook/Mouse, September 1996 */

inherit "std/room";
#include <stdproperties.h>
#include <ss_types.h>
#include "../../mouse.h"

   void create_room() {
     add_prop(ROOM_I_LIGHT,1);
     add_prop(ROOM_I_INSIDE, 1);
     set_short("Entrance to the beaver lodge");
     set_long("   As you maneuver through the tangle of branches, you "+
          "are better able to examine the hulking mass that lies "+
          "ahead of you. It is the underwater portion of the beaver "+
          "lodge; a conglomeration of mud, branches, tree trunks, "+
          "stumps, and other debris. Near the base of the mound, "+
          "you see what appears to be a hole.\n");
     add_item("lodge", "It looks like a heap of mud with branches, "+
          "roots, and other debris sticking out of it.\n");
     add_item("branches","The branches have been in the water so "+
          "long, it is virtually impossible to determine the types "+
          "of trees from which they came. They are cemented into "+         
          "the mound by mud.\n");
     add_item("mud", "Slimy, brown, wet dirt.\n");
     add_item("stumps", "You can tell these are tree stumps from "+
          "the roots sticking out of them.\n");
     add_item("trunks","You believe these are tree trunks, judging by "+
          "their diameters.\n");
     add_item("debris", "Various man-made objects such as an old boot "+
          "and a broken wagon wheel, as well as rocks and pebbles.\n");
     add_item("hole", "There is definitely a hole, partially hidden "+
          "by the branches. The hole might be large enough for you to "+
          "enter.\n");    

     add_exit(ROOT+"pond/rooms/beaver_room1","swim","@@swim_func",5,1);
     add_exit(ROOT+"pond/rooms/beaver_room3","swim","@@swim_func2",5,1);  
}

int swim_func() {
   if(query_dircmd()=="south")
     return 0;
   return 2;
}
int swim_func2() {
   if((query_dircmd()!="up")&&(query_dircmd()!="south"))
   {
      write("It is impossible to swim that direction.\n");
      return 1;
   }
   return 0;
}
