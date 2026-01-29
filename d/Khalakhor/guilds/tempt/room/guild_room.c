/**********************************************************************
 * - guild_room.c                                                   - *
 * - Guild base room for Temptresses club                           - *
 * - Temple of Oenghus -> Celtic god of love                        - *
 * - Created by Damaris@Genesis 03/2006                             - *
 **********************************************************************/

#pragma no_clone
#pragma save_binary
#pragma strict_types
#include "../guild.h"
inherit "/d/Khalakhor/std/room";

#include <filter_funs.h>
#include <macros.h>
#include <stdproperties.h>

/*********************************************************************
 * - Variables to hold our descrip lines to choose from (randomly).- *
 *********************************************************************/
private static string *shorts = ({
	"a %s in the temple of Oenghus", });

private static string *desc1 = ({
	"\n   A %s in the temple of Oenghus.",
	"\n   A %s in the temptress temple of Oenghus.",
	"\n   A %s in the fabled temple of Oenghus.",
	"\n   A %s in the temple of Oenghus in the Otherworld.",
	"\n   A %s in the temptress temple of Oenghus in the "+
	"Otherworld.",});

private static string *desc2 = ({
	"Vine covered rock pillars shoot upward holding a roof "+
	"made of grape vines. Ripe grape vines make up the "+
	"fortifications.",
	"Trailing creeper plants encompass massive rock pillars that "+
	"spiral upward bracing a covering made of grape vines. "+
	"Intricate ripe grape vines make up the "+
	"fortifications.",
	"Creeper plants cover substantial rock pillars that "+
	"twist upward bracing a roof made of grape vines. Mature grape "+
	"vines make up the fortifications.",
	"Creeper plants envelop sizeable rock pillars that coil "+
	"upward holding a roof made of grape vines. Thorny full-grown "+
	"grape vines make up the fortifications.",
	"Bright green vines trail along sturdy rock pillars "+
	"that hold a grape vine roof. Full-grown grape vines are "+
	"intricately woven to form the fortifications.",
	"Supple green vines trail upward along rock pillars that hold "+
	"a ripe grape vine roof. Well developed grape vines are "+
	"intricately woven to form the fortifications.", });

private static string *desc3 = ({
	"Smooth granite stones mark a path throughout the area. The air "+
	"is light and refreshing with a hint of sweet berries and "+
	"succulent grapes.",
	"Smooth granite stones mark a pathway throughout the area. The "+
	"air is light and refreshing with a hint of sweet berries and "+
	"succulent grapes.",
	"Smooth granite stones indicate a pathway throughout the area. "+
	"The air is light and refreshing with a hint of sweet berries "+
	"and succulent grapes.", });

private static string *extra_long, section = "middle";

/*********************************************************************
 * - This will get added to the end of the compiled long desc.     - *
 *********************************************************************/
public void
set_xlong(mixed arg)
{
	if (stringp(arg))
	arg = ({ arg });
	extra_long = arg;
}

public string *
query_xlong()
{
	return
	extra_long;
}

/*********************************************************************
 * - Compile the associated items to go with a room description.   - *
 *********************************************************************/
static varargs void
config_items(int x, int y, int z)
{
	set_add_item(0);
	add_item(({"oenghus temple", "temple", "section", "here", "area"}), query_long);
	add_item(({"pillar", "pillars", "sturdy pillars", "large pillars", "massive pillars", "sizable pillars", "substantial pillars", "rock pillars"}),
	"The rock pillars are grand in size and are intricately covered "+
	"in grapevines. Each pillar provides support for the grape "+
	"vines that stretch over making a roof of sorts.\n");
	add_item(({"roof", "covering", "vine roof", "up"}),
	"Grape vines have intricately grown together spreading "+
	"overhead making a roof of sorts.\n");
	add_item(({"grass", "green grass", "vibrant green grass", "ground", "down"}),
	"Vibrant green grass covers this area and looks soft enough "+
	"to lay upon.\n");
	add_item(({"plants", "plant", "creeper plants"}),
	"There are various types of plants scattered alongside the "+
	"path in no set pattern.\n");
	add_item(({"bush", "bushes"}),
	"The bushes are vibrant green with red berries flourishing "+
	"all over them.\n");
	add_item(({"berry", "berries"}),
	"The berries are vibrant red and look edible.\n");
	add_item(({"grapes"}),
	"There are red and white grapes growing every where.\n");
	add_item(({"red grapes"}),
	"These sumptous red grapes are ready to be picked and eaten.\n");
	add_item(({"white grapes"}),
	"These sumptous white grapes are ready to be picked and eaten.\n");
	add_item(({"fortification", "fortificatiobs", "wall", "walls"}),
	"Grape vines that are intricately woven form the "+
	"fortifications.\n");
	add_item(({"grape leaves", "leaves"}),
	"There are many soft grape leaves here and those along the "+
	"ground look soft enough to lay upon.\n");
	add_item(({"grape vines", "vines", "vine", "lush grape vines"}),
	"There are lush grape vines everywhere.\n");
	add_item(({"smooth granite stones", "smooth stones", "stones", "large stones", "big stones", "flat stones", "stone", "big stone", "flat stone", "large stone", "granite stones", "granite stone"}),
	"There are many smooth granite stones that make up a path.\n");
	add_item(({"path", "pathway"}),
	"There is a pathway made from large flat stones that grace "+
	"this area.\n");
	
}

/*************************************************************************
 * - Compile the associated room tells to go with the room description.- *
 *************************************************************************/
static varargs void
config_tells(int x, int y, int z)
{
	clear_tells();
	set_tell_time(65 + random(50));
	add_tell("From the distance, you hear the soft sounds of nymphs "+
	"giggling.");
	add_tell("A butterfly flickers along the path of some grape "+
	"vines.");
	add_tell("You can hear a song bird chirping.");
	add_tell("A nice warm breeze brings the scent of grapes.");
}

/*********************************************************************
 * - Compile a random room description with associated items.      - *
 *********************************************************************/
static varargs void
config_room(string str, string extra = "")
{
	mixed *arr = allocate(3);
	if (strlen(str))
	section = str;
	
	arr[0] = random(sizeof(desc1));
	arr[1] = random(sizeof(desc2));
	arr[2] = random(sizeof(desc3));
	
	config_items(arr[0], arr[1], arr[2]);
	config_tells(arr[0], arr[1], arr[2]);
	
	arr[0] = desc1[arr[0]];
	arr[1] = desc2[arr[1]];
	arr[2] = desc3[arr[2]];
	
	set_short(sprintf(one_of_list(shorts), section));
	set_long(sprintf("%s %s %s %s %s\n",
	sprintf(arr[0], section), arr[1], arr[2],
	(pointerp(extra_long) ? one_of_list(extra_long) : one_of_list(({
		"The sacred temple of Oenghus encompasses all." }))), extra));

}


/*********************************************************************
 * - Basic room stuff.                                             - *
 *********************************************************************/
static void
create_khalakhor_room()
{
	set_name("temple");
}

