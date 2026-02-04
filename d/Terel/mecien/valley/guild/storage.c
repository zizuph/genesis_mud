/* Creative rights reserved to Mecien(Jeff Babcock) and team. */
inherit "/std/room";

#include <stdproperties.h>
#define PATH "/d/Terel/mecien/valley/guild/"

create_room() 
{
   object cab, vial;
   set_short("Storeroom");
   set_long("This small chamber is the storage chamber for the shrine\n"
      + "and its many inhabitants. The walls are lined with many shelves,\n"
      + "racks and pegs.\n");
   
   add_exit(PATH + "sacristy", "west", 0);
   
   add_item("pegs", "They are oak pegs that protrude from the walls.\n");
   add_item("racks", "Oak racks, used for storage.\n");
   add_prop(ROOM_I_INSIDE, 1);  /* This is an inside room */
   
   seteuid(getuid(this_object()));
   cab=clone_object(PATH + "cabinet");
   cab->move(this_object());
  cab->remove_prop(CONT_M_NO_INS);
   vial=clone_object(PATH + "obj/vial");
   vial->move(cab);
   cab->add_prop(CONT_M_NO_INS, "You cannot put things into the cabinet.\n");
   
}
