 /*****************************************************************************
*  /d/Kalad/common/guilds/fishing/fish/ufish.c
*
*  Fish File: Unique Fish
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
*  Goliath Bichir Definitions
 *****************************************************************************/

#define COLOR_GB ({"brown", "tan", "light brown", "sandy", "chestnut", \
"russet", "grey", "dark-grey", "light-grey", "ebony", "onyx", "sable"})
#define PHYS_GB ({"fat", "sleek", "scaly", "scarred", "lean", \
"yellow-spotted"})

 /*****************************************************************************
*  Goliath Bichir Fins
 *****************************************************************************/

#define FIN_GB ({"seven", "eight", "nine", "ten", "eleven", "twelve", \
"thirteen", "fourteen", "fifteen", "sixteen", "seventeen", "eighteen"})

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

	string color, phys, finn;
	int roll;
	roll = random(2) + 1;

switch (roll)
{
case 1:

	color = one_of_list(COLOR_GB);
	phys = one_of_list(PHYS_GB);
	finn = one_of_list(FIN_GB);

	set_name("bichir");
	add_name("fish");
	add_name("goliath bichir");

	set_adj(color);
	add_adj(phys);

	set_short("" + color + " " + phys + " goliath bichir");
	set_long("This is a " + color + " " + phys
	+ " goliath bichir with " + finn + " bifid dorsal fins. "
	+ "Each is connected via a thick bristle like spine. "
	+ "Bulky scales that are bonelike and rhombic shaped cover "
	+ "its entire elongated body. Strong, circular pectoral "
	+ "fins can be found on the underside. And with two sharp, "
	+ "curved horns resting on its head, it looks like a very "
	+ "dangerous and ancient fish. This is a unique catch!\n");

	add_prop(OBJ_I_WEIGHT, random(22500)+ 22500);
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
	+ " snapper thats entire body including its eyes has a "
	+ "reddish hue. The snout is long and triangular much "
	+ "all of its fins. The first half of the dorsal fin "
	+ "contains pronounced spines and then fades into a "
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