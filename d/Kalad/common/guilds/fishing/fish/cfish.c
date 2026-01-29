 /*****************************************************************************
*  /d/Kalad/common/guilds/fishing/fish/cfish.c
*
*  Fish File: Common Fish
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
*  Croaker Definitions
 *****************************************************************************/
#define COLOR_CR ({"silver", "grey", "silvery-grey", "bronze", "copper"})
#define PHYS_CR ({"fat", "sleek", "scaly", "scarred", "lean"})

 /*****************************************************************************
*  Flounder Definitions
 *****************************************************************************/

#define COLOR_FL ({"brown", "dark brown", "light brown", "sandy", "chestnut", \
"russet"})
#define PHYS_FL ({"fat", "sleek", "scaly", "scarred", "lean", "white-bellied", \
"white-spotted"})

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

	color = one_of_list(COLOR_CR);
	phys = one_of_list(PHYS_CR);

	set_name("croaker");
	add_name("fish");

	set_adj(color);
	add_adj(phys);

	set_short("" + color + " " + phys + " croaker");
	set_long("This is a " + color + " " + phys
	+ " croaker with an iridescent head. Indistinct wavy lines run "
	+ "from head to tail that are dark in color on the upper sides. "
	+ "Its first dorsal fin is spiney and spiked, with the second combed "
	+ "down at an angle. This is a common catch!\n");

	add_prop(OBJ_I_WEIGHT, random(900)+ 900);
	add_prop(OBJ_I_VOLUME, random(1000)+ 1000);
   add_prop(OBJ_M_NO_SELL, "You can't sell fish here.\n");
	break;

case 2:

	color = one_of_list(COLOR_FL);
	phys = one_of_list(PHYS_FL);

	set_name("flounder");
	add_name("fish");

	set_adj(color);
	add_adj(phys);

	set_short("" + color + " " + phys + " flounder");
	set_long("This is a " + color + " " + phys
	+ " flounder, with a single dorsal fin that runs from "
	+ "head to tail. Numerous white spots and blotches are "
	+ "scattered amongst its body, though there are three "
	+ "distinct black spots on one side. It has a wedge "
	+ "shaped tail with the tip in the center and visible "
	+ "canine shaped teeth. This is a common catch!\n");

	add_prop(OBJ_I_WEIGHT, random(900)+ 900);
	add_prop(OBJ_I_VOLUME, random(1000)+ 1000);
	add_prop(OBJ_I_VALUE, 864);
	break;

default:

	color = one_of_list(COLOR_CR);
	phys = one_of_list(PHYS_CR);

	set_name("croaker");
	add_name("fish");

	set_adj(color);
	add_adj(phys);

	set_short("" + color + " " + phys + " croaker");
	set_long("This is a " + color + " " + phys
	+ " croaker with an iridescent head. Indistinct wavy lines run "
	+ "from head to tail that are dark in color on the upper sides. "
	+ "Its first dorsal fin is spiney and spiked with the second combed "
	+ "down at an angle. This is a common catch!\n");

	add_prop(OBJ_I_WEIGHT, random(900)+ 900);
	add_prop(OBJ_I_VOLUME, random(1000)+ 1000);
	add_prop(OBJ_I_VALUE, 864);
	}
}