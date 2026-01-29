
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
	set_short("Further from shore...");
	set_long("You are standing waist deep in the sea, further from "+
		"shore.  The blue-green sea is all around "+
		"you, and feels warm and refreshing.  There are seabirds "+
		"fishing here. "+"@@extra_desc");

	add_item((({"sea", "blue-green sea", "water"})),
		("The water is clear and a perfect temperature. "+
		"You can look down all the way to the bottom.\n"));
	add_item((({"seabirds", "pelicans", "pelican", "sea gulls"})),
		("There are pelicans and sea gulls flying around, "+
		"apparently hunting for fish.\n"));
		
	add_prop(ROOM_I_LIGHT,1);
	add_prop(ROOM_I_INSIDE, 0);
	add_prop(ROOM_I_IS, 1);
	add_prop(ROOM_I_TYPE, ROOM_IN_WATER);


	set_tell_time(110);
	add_tell("Pelicans soar gracefully overhead.\n");
	add_tell("Suddenly a pelican dives in, catching a fish.\n");
	add_tell("A large wave splashes over your head.\n");
	add_tell("Far out to sea the sailboat tacks to the north.\n");
	add_tell("Far away the sailboat tacks to the northwest.\n");
	
}

void
init()
{
	::init();
	add_action("dive", "swim");
}
int
dive(string where)
{
	if((where=="west")||(where=="w")||(where==""))
	{
	write("A large wave throws you back to your "+
		"previous location. That area is not open for "+
		"swimming yet.\n");
	return 1;
	}
	notify_fail("Swim where?\n");
	return 0;
}

string
extra_desc()
{
	return
	"The sea extends west all the way to where it "+
	"merges with the horizon. Far away in the northwest you can see "+
	"a ship that heads away from the busy dock of Gelan. "+
	"In the south the landscape is dominated by Mt. Kyrus. "+
	"From here you can wade north, east, or northeast.\n";
}
