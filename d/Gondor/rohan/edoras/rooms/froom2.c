inherit "/d/Gondor/common/room";
#include "/sys/stdproperties.h"
#include "/sys/macros.h"
#include "/d/Gondor/defs.h"

object door2;
 
create_room() {
   set_short("The dining room");
   set_long(BSN("This is the dining room of the house. " +
   "There is a dining table in this room, " +
   "surrounded by six chairs. " +
   "On the walls are hanging old family paintings."));
  
   add_item(({ "table" , "dining table" }),
   BSN("The table is old, yes almost antique, " +
   "but with your trained eyes, you can see " +
   "that its worth a lot of money."));
   add_item(({ "chair" , "chairs" }),
   "The chairs are looking as old as the table.\n");
   add_item(({ "paintings" , "family paintings" }),
   BSN("The paintings are, like all paintings " +
   "in this house, from the residents heir and family."));
 
  
   add_exit(EDORAS_DIR + "rooms/funohedhome","east", 0, 1);
  
   add_prop(ROOM_I_INSIDE,1);  /* This is a real room */
}

