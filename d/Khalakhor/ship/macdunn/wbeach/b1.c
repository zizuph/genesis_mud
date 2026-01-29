inherit "/d/Khalakhor/ship/macdunn/wbeach/bbase";
#include "local.h"
#include "/d/Khalakhor/sys/defs.h"
object base_rm = (BEACH_DIR+"bbase")->query_pointer();
void create_khalakhor_room()
{
   create_beach_room();
    set_long(
       "   You are at the east end of a rocky beach which is the narrow "+
       "shore of Cala Fasgadh near Port MacDunn. The choppy surf laps at "+
       "the low rocks just below you to the south, snapping at your "+
       "feet. High cliffs rise just to the north, sharp rocks "+
       "scarring their face with danger, leaving only a narrow "+
       "strip of sand between it and the rocks below. Far to the east, "+
       "you see the piers, though the rocks prevent you from walking "+
       "there.\n");
   add_item(({"rocks","rocks below"}),
       "The sharp rocks of the cliffs bar you from going anywhere "+
       "but west along the narrow shore, though the rocks below "+
       "seem safe enough to climb down into the sea.\n");
 
   add_cmd_item(({"rocks","down rocks","down","into sea","into water",
      "into the water","into the sea","into harbor","into the harbor"}),
      "climb","@@climb_down");
 
   add_exit("b2","west");
}
 
string climb_down() {
   write("You carefully climb the sharp rocks of the shore into the "+
         "choppy waters of the harbor.\n");
   set_dircmd("down");
   TP->move_living("climbs down the rocks into the water",
                   MACDUNN_DIR+"shore0",0,0);
   return "";
}
 
public void enter_inv(object ob, object from) {
   ::enter_inv(ob, from);
   if ((from!=TO)&&(interactive(ob)))
      base_rm->start_pound_surf();
}
