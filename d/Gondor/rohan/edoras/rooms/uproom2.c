inherit "/d/Gondor/common/room";
#include "/sys/stdproperties.h"
#include "/sys/macros.h"
#include "/d/Gondor/defs.h"

 
create_room() {
   set_short("The bath room");
   set_long(BSN("This is the bath room . " +
   "On theese walls, like no other walls of the " +
   "house, are hanging no family portraits. " +
   "A mirror is all you can see on them."));
  
   add_item(({ "mirror" }),
   BSN("In the mirror you look uglier than ever!"));
 
  
   add_exit(EDORAS_DIR + "rooms/uphall","east", 0, 1);
  
   add_prop(ROOM_I_INSIDE,1);  /* This is a real room */
}

