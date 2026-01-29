/*
*  by Amelia, for use in Light Forest
*/
inherit "/std/room";
#include "room_tell.c"
#include "/sys/stdproperties.h"
#include <ss_types.h>
#include "/sys/macros.h"
#include "defs.h"


object shadow;

void
	
reset_room()
	{
	}
create_room() {

	set_short("A large shallow pond");
	set_long("You find yourself sinking deep into mud. "+
		"It feels like quicksand! You better get out fast.\n");
		

	add_item((({"pond"})),
		("As you look at the pond, you can sense it "+
		"is filled with life.  It is a large shallow pond, "+
		"and extends some distance to the other side.\n"));
	add_item((({"water lilies", "water lily", "lily", "lilies",
		"flowers"})),
		("The water lilies are large pink and white blossoms that "+
		"grow on the surface of the pond.  Their leaves are "+
		"large green pads.\n"));
	add_item((({"pad", "pads", "lily pad", "lily pads", "leaves"})),
		("The pads are leaves of the water lilies, and nearly "+
		"cover the pond...\n"));
	set_tell_time(80);
	add_tell("Ribbit!  Ribbit! \n");
	add_tell("Chug-a-rumph, chug-a-rumph, chug-a-rumph!\n");
	add_tell("Neek-neek-neek!\n");
	add_tell("A dragonfly hovers over a water lily.\n");
	add_tell("Croak! Croak! Croak!\n");
	add_tell("Splash!\n");
	reset_room();
}

/*
 * Function name:
 * Description  :
 */

void
init()
{

	::init();
	
}
enter_inv(object obj, object from)
	{
	::enter_inv(obj,from);
	if (interactive(obj))
		start_room_tells();
	}
