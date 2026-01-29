 /*****************************************************************************
*  /d/Kalad/common/guilds/fishing/fish/rfish.c
*
*  Fish File: Rare Fish
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
*  Pompano Definitions
 *****************************************************************************/

#define COLOR_PO ({"grey", "dark-green", "moss-green", "olive", "jade"})
#define PHYS_PO ({"fat", "sleek", "scaly", "scarred", "lean", "spotted", \
"yellow-bellied"})

 /*****************************************************************************
*  Sheepshead Definitions
 *****************************************************************************/

#define COLOR_SH ({"brown", "tan", "light brown", "sandy", "chestnut", \
"russet"})
#define PHYS_SH ({"fat", "sleek", "scaly", "scarred", "lean", "striped"})

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

	color = one_of_list(COLOR_PO);
	phys = one_of_list(PHYS_PO);

	set_name("pompano");
	add_name("fish");

	set_adj(color);
	add_adj(phys);

	set_short("" + color + " " + phys + " pompano");
	set_long("This is a " + color + " " + phys
	+ " pompano with a deep, compressed body and small "
	+ "mouth. The forehead slopes gently back to the "
	+ "dorsal fin on top which is symmetrical with the "
	+ "one on bottom. Its belly is a yellowish tint that "
	+ "bleeds into the fins and throat. This is a rare catch!\n");

	add_prop(OBJ_I_WEIGHT, random(4200)+ 1400);
	add_prop(OBJ_I_VOLUME, random(2000)+ 2000);
    add_prop(OBJ_M_NO_SELL, "You can't sell fish here.\n");
	break;

case 2:

	color = one_of_list(COLOR_SH);
	phys = one_of_list(PHYS_SH);

	set_name("sheepshead");
	add_name("fish");

	set_adj(color);
	add_adj(phys);

	set_short("" + color + " " + phys + " sheepshead");
	set_long("This is a " + color + " " + phys
	+ " sheepshead, also known as the convict fish. It has "
	+ "prominent teeth which include incisors, molars and "
	+ "rounded grinders. Vertical black bars run down its "
	+ "sides to the tail. Above those, the dorsal fin is "
	+ "made up of strong, sharp spines, and there is a "
	+ "smaller version of them on the bottom side.\n");

	add_prop(OBJ_I_WEIGHT, random(4200)+ 1400);
	add_prop(OBJ_I_VOLUME, random(2000)+ 2000);
	add_prop(OBJ_I_VALUE, 17280);
	break;

default:

	color = one_of_list(COLOR_SH);
	phys = one_of_list(PHYS_SH);

	set_name("sheepshead");
	add_name("fish");

	set_adj(color);
	add_adj(phys);

	set_short("" + color + " " + phys + " sheepshead");
	set_long("This is a " + color + " " + phys
	+ " sheepshead also known as the convict fish. It has "
	+ "prominent teeth which include incisors, molars and "
	+ "rounded grinders. Vertical black bars run down its "
	+ "sides to the tail. Above those, the dorsal fin is "
	+ "made up of strong, sharp spines and a smaller version "
	+ "of them on the bottom side. This is a rare catch!\n");

	add_prop(OBJ_I_WEIGHT, random(4200)+ 1400);
	add_prop(OBJ_I_VOLUME, random(2000)+ 2000);
	add_prop(OBJ_I_VALUE, 17280);
	}
}