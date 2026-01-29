/*   forest_E_7a.c
*    by Amelia, for use in the Light Forest
*/
inherit "/std/room";

#include <macros.h>
#include <stdproperties.h>
#include "defs.h"

create_room()
	{
		
	set_short("The light forest");
	set_long("You go around the tree, and find yourself in a thicket "+
		"on the other side.\n");

	add_exit((FPATH+"forest_E_4a"), "northwest", 0, 0);

	add_prop(ROOM_I_LIGHT, 1);
	add_prop(ROOM_I_IS, 1);
	add_prop(ROOM_I_INSIDE, 0);

}
