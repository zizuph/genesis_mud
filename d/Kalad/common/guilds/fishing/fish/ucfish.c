 /*****************************************************************************
*  /d/Kalad/common/guilds/fishing/fish/ucfish.c
*
*  Fish File: Uncommon Fish
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
*  Mackerel Definitions
 *****************************************************************************/

#define COLOR_MK ({"bluish-green", "viridian", "teal", "dark-turqoise"})
#define PHYS_MK ({"fat", "sleek", "scaly", "scarred", "lean", "white-bellied", \
"yellow-spotted"})

 /*****************************************************************************
*  Hogfish Definitions
 *****************************************************************************/

#define COLOR_HG ({"white", "pearl-white", "mottled-brown", "sandy", \
"reddish-orange"})
#define PHYS_HG ({"fat", "sleek", "scaly", "scarred", "lean", "spotted"})

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

	color = one_of_list(COLOR_MK);
	phys = one_of_list(PHYS_MK);

	set_name("mackerel");
	add_name("fish");

	set_adj(color);
	add_adj(phys);

	set_short("" + color + " " + phys + " mackerel");
	set_long("This is a " + color + " " + phys
	+ " mackerel, which has a single lateral line that "
	+ "slopes from just behind the gill to the tail. Irregular "
	+ "golden-yellow spots can be found on both sides, with a "
	+ "bluish-black blotch on the first dorsal fin. Small spikes "
	+ "run on both the top and bottom side after the second "
	+ "dorsal fin all the way down to the boomerang shaped tail. "
	+ "This is an uncommon catch!\n");

	add_prop(OBJ_I_WEIGHT, random(6600)+ 2200);
	add_prop(OBJ_I_VOLUME, random(2000)+ 2000);
	add_prop(OBJ_I_VALUE, 5184);
	break;

case 2:

	color = one_of_list(COLOR_HG);
	phys = one_of_list(PHYS_HG);

	set_name("hogfish");
	add_name("fish");

	set_adj(color);
	add_adj(phys);

	set_short("" + color + " " + phys + " hogfish");
	set_long("This is a " + color + " " + phys
	+ " hogfish, which, as the name implies, looks similar to "
	+ "both a hog and of course a fish. Its mouth is "
	+ "elongated and shaped like a snout. The first dorsal "
	+ "fin is spiked and the first three are vastly longer "
	+ "than the others, which are quite small. Both the top "
	+ "and bottom part of the tail are lobed and stretched "
	+ "out. This is an uncommon catch!\n");

	add_prop(OBJ_I_WEIGHT, random(6600)+ 2200);
	add_prop(OBJ_I_VOLUME, random(2000)+ 2000);
	add_prop(OBJ_I_VALUE, 5184);
	break;

default:

	color = one_of_list(COLOR_HG);
	phys = one_of_list(PHYS_HG);

	set_name("hogfish");
	add_name("fish");

	set_adj(color);
	add_adj(phys);

	set_short("" + color + " " + phys + " hogfish");
	set_long("This is a " + color + " " + phys
	+ " hogfish which as the name implies looks similar to "
	+ "both a hog and of course a fish. Its mouth is "
	+ "elongated and shaped like a snout. The first dorsal "
	+ "fin is spiked and the first three are vastly longer "
	+ "than the others which are quite small. Both the top "
	+ "and bottom part of the tail are lobed and stretched "
	+ "out. This is an uncommon catch!\n");

	add_prop(OBJ_I_WEIGHT, random(6600)+ 2200);
	add_prop(OBJ_I_VOLUME, random(2000)+ 2000);
    add_prop(OBJ_M_NO_SELL, "You can't sell fish here.\n");
	}
}