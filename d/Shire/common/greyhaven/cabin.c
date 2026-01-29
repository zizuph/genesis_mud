inherit "/std/room";

#include "defs.h"
#include "/sys/stdproperties.h"
#include "/sys/ss_types.h"


object ob;
create_room() {
   set_short("cabin");
   set_long(BS("You are inside a small cabin. Everything in the"
			 + " cabin is neat and ordered. The books on the"
			 + " shelves give off an aura of knowledge and wisdom"
			 + " as do the papers and utensils on the small"
			 + " desk in the middle of the room. There is also"
			 + " a wooden chair at the desk and a small cot in"
			 + " a corner.\n"));

   add_item(({"book", "books"}), "The books are in a multitude of colours and"
	    + " sizes.\n");
   add_item(({"chair", "wooden chair"}), "A very normal chair made of"
	    + " pine.\n");
   add_item("cot", "It is neat and well made. It doesn't look very comfortable"
	    + " though.\n");
   add_item("desk", "It is the only thing in this cabin that is not well"
	    + " ordered. Papers lie\nin heaps and there are two books"
	    + " opened on the middle of the desk.\n");

   add_prop(ROOM_I_INSIDE,1);

   add_exit(STAND_DIR + "garden","out",0,1);

   reset_room();
}

reset_room() {
  if(!ob) {
    ob = clone_object(STAND_MONSTER + "wise_man");
    ob->move(this_object());
  }
}
