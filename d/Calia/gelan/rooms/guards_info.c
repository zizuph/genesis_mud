/* 	this is a room of the town Gelan

    coder(s):   Merlin

    history:	Date:		What done?			Who did?
                31/5/96    call_outs taken out                  Maniac
                26/7/95    resetting of guard now handled by   
                           reset of all guards at gate          Maniac
		17.01.95	reset-function updated		Deinonychus
                14.09.94        new poster added                Deinonychus
		11.09.94	reset-function updated          Deinonychus
                  7.9.94	Map cloning bug removed         Maniac	
    		16.12.93	block-function		    	Deinonychus
    		26. 2.93	posters added		    	Deinonychus
		16. 2.93	path system                     Merlin
                17. 1.93	new guard system                Merlin
                 9. 1.93	townrooms.h -> room.h           Merlin
                 6.11.92	installed helps system          Merlin
                 3.11.92	created                         Merlin

    purpose:    player can get info here
    exits:      west to castle road, east to offices, north to headquarter
                south to square

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

string *posters = ({  /* stores id for path object */
  "gelan.poster",
  "palace.poster",
  "dinosauria.poster",
});


/*
 * Function name: reset_room
 * Description:   resets the room
 * Arguments:     none
 */

void
reset_room()
{
    int i;
    object box;
    object map;

    if(!(box = present("box", TO))) {
    	box = clone_object(GELAN_OBJECTS + "map_box");
        box->move(TO);
    }

    if(!(map = present("map", box))){
    	map = clone_object(GELAN_OBJECTS + "map");
        map->move(box);
    }

    map->set_heap_size(50);
}


public void
create_gelan_room()
{
    object poster;
    int i;

    /* descriptions */

    set_short("guards info office");
    set_long("You're in the guards info office.\n" +
	BS("There are several posters hanging on the wall.  In an edge " +
	"you find a cardboard box.  This seems to be the place where " +
	"the sightseeing tours in Gelan start.\n"));

    i = sizeof(posters);
    while(i > 0){
      i--;
      poster = clone_object(GELAN_OBJECTS + "poster");
      poster->read_long(GELAN_TEXTS + posters[i]);
      poster->move(TO);
      poster->set_no_show_composite(1);
    }

	/* properties */

    add_prop(ROOM_I_INSIDE, 1);	 /* this room is inside */

    /* exits */

    add_exit(GELAN_ROOMS + "guards_headquarter","north", "@@block");
    add_exit(GELAN_ROOMS + "square_northend_e","south", 0);
    add_exit(GELAN_ROOMS + "castle_road_e1","west", 0);
    add_exit(GELAN_ROOMS + "guards_offices","east", "@@block");

    /* items in the room */

    add_item(({"%", "%"}), BS("%\n"));

    set_alarm(1.0, 0.0, reset_room);
    enable_reset(150);

} /* create_room */



/*
 * Function name: block
 * Description:   blocks a player
 * Arguments:     none
 * Returns:       1
 */
int block()
{
  write("You have no access to this section of the head quarter.\n");
  return 1;
}

/*
 * Function name: none
 * Description:   none
 * Arguments:     none
 * Returns:       none
 */
