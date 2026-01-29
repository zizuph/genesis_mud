/*
*  by Amelia, for use in the Light Forest
*/
inherit "/std/room";
#include <stdproperties.h>
#include <macros.h>
#include "defs.h"

create_room() {

	object door;
	set_short("Granny's parlor");
	set_long("Granny often comes here to sit and look out at "+
		"her garden.  The room contains a rocking chair, a small "+
		"table, and pictures of Granny's grandchildren on the "+
		"wall.\n");
	add_exit((FPATH+"cottage1"), "west", 0,0);
	door = clone_object(FPATH+"garden_door");
   door->move(this_object());

}

