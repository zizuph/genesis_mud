/* vpath.c The path between Mt. Black and the Volcano*/
/* Geraden 22 January 1997 */

#include "/d/Emerald/defs.h"

inherit "/std/room";

void create_path();
void create_room()
{
	
   set_long("   You are on the path between Mount Black and the volcano "+
		"known as fujitsuhamilocamino. The path is very rocky and "+
		"cluttered with ash and debris from previous lava flows "+
           "from the volcano. ");
	
	add_item(({"path", "trail"}), "Looking closely at the path you notice "+
		"that the ground under it is made completely of basalt from an "+
		"ancient lava flow.\n");
	add_item(({"ash"}), "The ash covers the ground like a blanket of "+
		"grey snow, leaving everything dark and dingy.\n");
	add_item(({"debris"}), "The landscape is dotted with larger chunks "+
		"of ash and rock from the erruptions of the volcano.\n");
	add_item(({"lava", "lava flows"}), "All around the area where you "+
		"stand you can see the evidence of previous lava flows; "+
		"Black serpent-like fingers of rock running down the "+
		"volcano.\n");
	add_item(({"volcano"}), "You look toward the towering volcano. "+
		"You can see the smoke and ash billowing up from the cone "+
		"in plain evidence of the activity inside.\n");
	add_item(({"Mt. Black", "mt black", "mountain"}), "Looking to the "+
		"south you can see the towering shape of Mt. Black looming "+
		"dark and forboding.\n");
	create_path();
}

create_path()
{
}
