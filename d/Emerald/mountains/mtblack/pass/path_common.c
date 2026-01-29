/* path_common.c, the baseroom for the path the the cliffs */
/* Geraden 22 January 1997 */

#include "/d/Emerald/defs.h"

inherit "/std/room";

void create_path();
void create_room()
{
	
	set_long("   You are walking along a faint trail on Mt. Black. The mist "+
		"is very dense here, making it hard to see very far. The mist "+
		"soaks through your clothing and chills you to the bone causing "+
		"you to shiver. It also soaks the moss covered ground making "+
		"the footing unsure. You had best watch your step lest you fall "+
		"to the jagged rocks below. ");
	
	add_item(({"trail", "path"}), "This is more like a game trail than "+
		"a proper path. Not much more than a faint disturbance in "+
		"the moss covered ground.\n");
	add_item(({"Mt. Black", "mountain", "mt black"}), "The black mountain rises high "+
		"above you seeming to touch the very heavens.\n");
	add_item(({"mist", "fog"}), "The mist seems clings to everything. "+
		"It seems to be alive in the way it twists and swirls "+
		"around alternately concealing and revealing the path "+
		"ahead as well as the other featurs of the landscape.\n");
	add_item(({"moss", "ground"}), "The ground is covered with moss, "+
		"which glistens from the moisture left upon it by the ever "+
		"present mist.\n");
	add_item(({"rocks", "jagged rocks", "below"}), "It is a long drop "+
		"to the broken, jagged rocks below the path.  To fall upon "+
		"them would most likely mean your death.\n");
	add_item(({"clothing", "my clothes"}), "Your clothing is completely "+
		"soaked from the mist that clings to everything here in "+
		"this desolate place.\n");

	create_path();
}

create_path()
{
}

