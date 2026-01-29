inherit "/d/Shire/room";

#include "/d/Shire/common/defs.h"
#include "/sys/stdproperties.h"

#define RANGER_SPELLS "/d/Gondor/common/guild/spells/obj/"
 
create_room() {
    set_short("Dark room in the downs");
    set_long(break_string(
	  "You find yourself in a dark room, probably a barrow. A weird "
	+ "green light is glowing softly here. Your fear seems to be a part "
	+ "of the atmosphere in this room. Better get out quickly.\n",70));

    add_item(({"light","green light"}), break_string(
	  "The green light seems to be emanating from yourself and reveals "
	+ "little in the room.\n",70));

    add_exit(DOWNS_DIR + "stone2_2", "west");

    add_prop(ROOM_I_LIGHT,0);
    add_prop(ROOM_I_INSIDE,1);
    reset_room();	
}

reset_room() {
 object wight;
	if (!present ("wight"))
 {
	wight = clone_object(DOWNS_DIR + "npc/wight");
 wight -> move(this_object());
/*
 clone_object(RANGER_SPELLS + "nightv_scroll")->move(wight);
*/
 }
}
