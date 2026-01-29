inherit "/d/Gondor/common/room";
#include "/sys/stdproperties.h"
#include "/sys/macros.h"
#include "/d/Gondor/defs.h"

 
create_room() {
   set_short("The upper hall");
   set_long(BSN("This is the upper hall . " +
   "On theese walls, like on most other walls of the " +
   "house, are hanging old family portraits."));
  
   add_item(({ "paintings","portraits" }),
   BSN("The paintings are, like all paintings " +
   "in this house, from the residents heir and family."));
 
  
   add_exit(EDORAS_DIR + "rooms/uproom1","east", 0, 1);
   add_exit(EDORAS_DIR + "rooms/uproom2","west", 0, 1);
   add_exit(EDORAS_DIR + "rooms/funohedhome","down", 0, 1);
  
   add_prop(ROOM_I_INSIDE,1);  /* This is a real room */
}

