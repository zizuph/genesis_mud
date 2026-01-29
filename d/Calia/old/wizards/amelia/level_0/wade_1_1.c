
/*
*	coder(s):	Amelia
*	history:		coded 22/4/95
*/

inherit "/std/room";
inherit "/d/Calia/sea/level0/wade_base";

#include <stdproperties.h>
#include <macros.h>

void
create_room()
{
	::create_level0();
	set_short("A few feet from shore");
	set_long("You are standing knee-deep in the sea not far from shore.  "+
		"The water is very clear, and as you "+
		"look down you see many small colorful fish "+
		"darting around.  The bottom is white and sandy.  "+
		"Now and then a wave hits you and nearly "+
		"knocks you off your feet.  You can "+
		"continue to wade north, east, or west here, but to the "+
		"west it seems to get deeper...\n");

	add_item((({"wave", "waves", "sea"})),
		("Every now and then you are hit by a wave, although "+
		"the sea is relatively calm. The water is a clear "+
		"blue-green and feels just the right temperature.\n"));
	add_item("west", "Looking to the west, you see "+
		"the color of the water is darker, and it is "+
		"no doubt much deeper.\n");
	add_item((({"sand", "bottom", "sandy bottom"})),
		("The water is so clear that you can "+
		"see the white sandy bottom.  The sand feels pleasant "+
		"between your toes.\n"));
	add_item((({"fish", "small fish",})),
		("Small fish of all colors abound here and seem to attract "+
		"large numbers of sea birds.\n"));
	add_item((({"birds", "sea birds", "gulls", "pelicans"})),
		("Sea birds cry and swoop overhead, occasionally "+
		"diving into the waves after a fish.  You can identify "+
		"seagulls, cormorants and pelicans.\n"));
	add_prop(ROOM_I_LIGHT,1);
	add_prop(ROOM_I_INSIDE, 0);
	add_prop(ROOM_I_IS, 1);
	add_prop(ROOM_I_TYPE, ROOM_IN_WATER);


	set_tell_time(45);
	add_tell("You are nearly knocked down by a large wave!\n");
	add_tell("Fresh salt breezes ruffle your hair.\n");
	add_tell("Small fish nibble at your feet and legs.\n");
	add_tell("The wet sand gooshes between your toes.\n");
	add_tell("A pelican soars gracefully overhead.\n");
}
