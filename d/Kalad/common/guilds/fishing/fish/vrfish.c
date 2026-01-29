 /*****************************************************************************
*  /d/Kalad/common/guilds/fishing/fish/vrfish.c
*
*  Fish File: Very Rare Fish
*
*  Created June 2019, Greneth        
*
 *****************************************************************************/

 /*****************************************************************************
*  Includes
 *****************************************************************************/
#include "/d/Kalad/common/guilds/fishing/defs.h"

 /*****************************************************************************
*  Inherits
 *****************************************************************************/
inherit "/std/object";

 /*****************************************************************************
*  Grouper Definitions
 *****************************************************************************/

#define COLOR_GR ({"brownish-red", "redwood", "maroon", "sandy", "vermillion", \
"russet"})
#define PHYS_GR ({"fat", "sleek", "scaly", "scarred", "lean", "white-spotted"})

 /*****************************************************************************
*  Snapper Definitions
 *****************************************************************************/

#define COLOR_SN ({"coral", "rose", "rosewood", "ruby"})
#define PHYS_SN ({"fat", "sleek", "scaly", "scarred", "lean", "white-bellied"})

 /*****************************************************************************
*  Function name: create_object
*  Description  : Constructor for the item, modify this to change.
 *****************************************************************************/
void create_object()
{

	string color, phys;
	int roll;
	roll = random(2) + 1;

switch (roll)
{
case 1:

	color = one_of_list(COLOR_GR);
	phys = one_of_list(PHYS_GR);

	set_name("grouper");
	add_name("fish");

	set_adj(color);
	add_adj(phys);

	set_short("" + color + " " + phys + " grouper");
	set_long("This is a " + color + " " + phys
	+ " grouper with various black dots that can be found "
	+ "on its snout. The mouth is lined in a scarlet orange "
	+ "color and small white blotches run along its side. "
	+ "It has a single dorsal fin that looks like two side "
	+ "by side, with the first spined, and the second half long "
	+ "and wavy. This is a very rare catch!\n");

	add_prop(OBJ_I_WEIGHT, random(13500)+ 4500);
	add_prop(OBJ_I_VOLUME, random(4000)+ 4000);
    add_prop(OBJ_M_NO_SELL, "You can't sell fish here.\n");
	break;

case 2:

	color = one_of_list(COLOR_SN);
	phys = one_of_list(PHYS_SN);

	set_name("snapper");
	add_name("fish");

	set_adj(color);
	add_adj(phys);

	set_short("" + color + " " + phys + " snapper");
	set_long("This is a " + color + " " + phys
	+ " snapper thats entire body, including its eyes, has a "
	+ "reddish hue. The snout is long and triangular, much "
	+ "like all of its fins. The first half of the dorsal fin "
	+ "contains pronounced spines, and then fades into a "
	+ "point where they are less prominent. This is a very "
	+ "rare catch!\n");

	add_prop(OBJ_I_WEIGHT, random(13500)+ 4500);
	add_prop(OBJ_I_VOLUME, random(4000)+ 4000);
	add_prop(OBJ_I_VALUE, 17280);
	break;

default:

	color = one_of_list(COLOR_SN);
	phys = one_of_list(PHYS_SN);

	set_name("snapper");
	add_name("fish");

	set_adj(color);
	add_adj(phys);

	set_short("" + color + " " + phys + " snapper");
	set_long("This is a " + color + " " + phys
	+ " snapper thats entire body including its eyes has a "
	+ "reddish hue. The snout is long and triangular much "
	+ "all of its fins. The first half of the dorsal fin "
	+ "contains pronounced spines and then fades into a "
	+ "point where they are less prominent. This is a very "
	+ "rare catch!\n");

	add_prop(OBJ_I_WEIGHT, random(13500)+ 4500);
	add_prop(OBJ_I_VOLUME, random(4000)+ 4000);
	add_prop(OBJ_I_VALUE, 17280);
	}
}