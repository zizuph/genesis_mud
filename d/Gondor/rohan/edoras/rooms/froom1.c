inherit "/d/Gondor/common/room";
#include "/sys/stdproperties.h"
#include "/sys/macros.h"
#include "/d/Gondor/defs.h"

object table;
 
void add_stuff;
void reset_room();
 
create_room() {
   set_short("The lounge.");
   set_long(BSN("This is the lounge of the house. " +
   "Strange enough, there are no chairs though. " +
   "There is actually no place to sit on at all. " +
   "The room is still smelling from smoked cigars."));
  
   add_stuff();
     reset_room();
 
   add_exit(EDORAS_DIR + "rooms/funohedhome", "west", 0, 1);
  
  
   add_prop(ROOM_I_INSIDE,1);  /* This is a real room */
}

add_stuff() {
   if (!present("table",TO))
  table = clone_object(EDORAS_DIR + "obj/table");
  table->move(TO);
}
 
reset_room()
{
add_stuff();
}
