/* 	this is a room of the town Gelan

    coder(s):   Merlin

    history:    12/4/97    school connected                Maniac
                31/5/96    call_outs taken out             Maniac     
                    8.94   typos corrected                 Maniac
                20. 2.93   path system                     Merlin
                2.02.93    descriptions		           Deinonychus
		3.11.92    created                         Merlin
                6.11.92    installed help system           Merlin

    purpose:    square
    exits:      east to school, north to citizen, nw-w-se-s to square

    objects:    none
    npcs:       none

    quests:     none
    special:    none

    to do:      none
    bug:        none known
*/


#pragma save_binary

#include "defs.h"
#include "room.h"
#include <stdproperties.h>
#include <macros.h>
#include GUARD_INCLUDE

inherit GELAN_BASE_ROOM;

public void
create_gelan_room()
{
    /* descriptions */

    set_short("Square eastend north");
    set_long("You're at the northern eastend of the town square. To your " +
	"north you see a citizen's house. Looking to the east you find " +
	"the school of Gelan. There are other buildings all around the " +
        "square.\n");

	/* properties */

    add_prop(ROOM_I_INSIDE, 0);		/* this room is outside */

    /* exits */

    add_exit(GELAN_ROOMS + "citizen","north", "@@block_house");
    add_exit(GELAN_ROOMS + "square_eastend","south",0);
    add_exit(GELAN_ROOMS + "square_en","west",0);
    add_exit(GELAN_ROOMS + "school","east");
    add_exit(GELAN_ROOMS + "square_corner_ne","northwest",0);
    add_exit(GELAN_ROOMS + "square_e","southwest",0);

    /* items in the room */

    add_item(({"citizen's house", "house"}), DESC("citizen_house"));
    add_cmd_item("inscription on mat", "read", DESC("citizen_inscription"));
    add_item("school", DESC("school_house"));
    add_cmd_item("inscription on school", "read", DESC("school_inscription"));
    add_item(({"floor", "ground", "bottom", "square"}), DESC("floor"));
    add_item(({"building", "buildings"}), DESC("buildings"));
    add_item(({"%", "%"}), BS("%\n"));

} /* create_room */

int block_house()
{
  write("Oops, looks like the citizen is on holiday and everything's " +
        "locked up for now.\n");
  return 1;
}

