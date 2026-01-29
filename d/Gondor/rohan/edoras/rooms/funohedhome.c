inherit "/d/Gondor/common/room";
#include "/sys/stdproperties.h"
#include "/sys/macros.h"
#include "/d/Gondor/defs.h"

object door;
create_room() {
   set_short("The hall of a wealthy Rohirrim");
   set_long(BSN("This hall shows all signs of wealth. " +
   "The stairs are in splendid shape, and doors and chairs " +
   "all look like they came straight from the carpenter."));
  
   add_item("rug", "The rug is beautiful and red.\n");
   add_item(({ "chair" , "chairs" }),
   "The chairs are made of redwood.\n");
   add_item(({ "stair" , "stairs" }),
   "The stairs are in splendid shape.\n");
 
/*
   add_exit(EDORAS_DIR + "rooms/uphall","up",0,1);
   add_exit(EDORAS_DIR + "rooms/froom1","east",0,1);
   add_exit(EDORAS_DIR + "rooms/froom2","west",0,1);
*/
  
  door = clone_object(EDORAS_DIR + "rooms/fhomedoor");
  door->move(this_object());
 
   add_prop(ROOM_I_INSIDE,1);  /* This is a real room */
}

