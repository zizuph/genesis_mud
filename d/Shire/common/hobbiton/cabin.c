inherit "/d/Shire/room";

#include "/d/Shire/common/defs.h"
#include "/sys/stdproperties.h"
#include "/sys/ss_types.h"


create_room() {
   set_short("cabin");
   set_long("You are inside a small cabin. Everything in the"
			 + " cabin is neat and ordered. The books on the"
			 + " shelves gives of an aura of knowledge and wisdom"
			 + " as does the papers and utensils on the small"
			 + " desk in the middle of the room. There is also"
			 + " a wooden chair at the desk and a small cot in"
			 + " a corner.\n");

   add_item(({"book", "books"}), "The books are in a multitude of colours and"
	    + " sizes.\n");
   add_item(({"chair", "wooden chair"}), "A very normal chair made of"
	    + " pine.\n");
   add_item("cot", "It's neat and well made. It doesn't look very comfortable"
	    + " though.\n");
   add_item("desk", "It's the only thing in this cabin that is not well"
	    + " ordered. Papers lie\nin heaps and there are two books"
	    + " opened on the middle of the desk.\n");
   add_item(({"papers","paper","utensils"}),
	      "The papers and utensils on the desk seems to be news from all "
	     +"over the known world, some are named Sparkle.\n");

   add_prop(ROOM_I_INSIDE,1);

   add_exit(HOBBIT_DIR + "garden","out",0,1);

}
