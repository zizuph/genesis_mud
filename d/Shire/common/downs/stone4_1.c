inherit "/d/Shire/room";

#include "/d/Shire/common/defs.h"
#include "/sys/stdproperties.h"
#include <macros.h>

create_room() {
    set_short("Dark room in the downs");
    set_long(
	  "You are inside the Barrow downs.\n"
	+ "There is a slight draft along the floor.\n"
	+ "It smells like a three month old open grave.\n");

    add_item(({"",}), break_string(
	  "Yes, it smells BAD.",70));
	
	add_exit(DOWNS_DIR + "stone2_3", "up");
	add_exit(DOWNS_DIR + "stone4_2", "east");
    add_prop(ROOM_I_LIGHT,0);
    add_prop(ROOM_I_INSIDE,1);
    reset_room();       
}


reset_room() {
		int i;
 		object ghast;    
		if (!present ("ghast")){
		 for (i=1; i<=3; i++ ) {
    ghast=clone_object(DOWNS_DIR+"npc/r_ghast")->move(TO);
    tell_room(TO,"A horrifying ghast brings the chill of death with it.\n");
		};
	};
}
    	
