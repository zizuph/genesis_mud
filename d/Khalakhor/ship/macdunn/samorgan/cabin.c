/**********************************************************************
 * - cabin.c                                                        - *
 * - Cabin for ship from MacDunn to SaMorgan                        - *
 * - Created by Damaris@Genesis 03/2001                             - *
 * - Updated by Damaris@Genesis 08/2005                             - *
 **********************************************************************/

#pragma save_binary
#pragma strict_types
 
inherit "/d/Genesis/ship/cabin";

#include <macros.h> 
#include <stdproperties.h>
#include "local.h"
#include "/d/Khalakhor/sys/terrains.h"
#include "/d/Khalakhor/sys/defs.h"
object desk;
 
int
chk(string id, string fname)
{
	if (!objectp(present(id,desk)))
	{
		(clone_object(THIS_DIR+fname))->move(desk);
		return 1;
	}
	return 0;
}
 
void
check_desk()
{
	if ((chk("map","map") + chk("globe","globe"))<0)
 	tell_room(TO,"A young elf rushes in, places something on the "+
 	"desk and rushes back out.\n");
}

void reset_cabin()
{
	check_desk();
} 
 
public void
create_cabin()
{
	set_short("the cabin of the Bella Diaz");
	set_long("   This is the captain's cabin of the Bella Diaz. "+
	"There is a large desk placed firmly in the corner of this "+
	"cabin. The cabin is small and cramped but adequate for the "+
	"captain's needs.\n");
	add_item(({"cabin","quarters","cramped quarters",}), query_long);
	add_item(({"timber","surrounding timber","wall","walls"}),
	"The walls are made of a sturdy timber, that would resist " +
	"any oceanic storm.\n");
	add_item("ceiling","The ceiling is constructed of wooden "+
	"beams.\n");
	add_item(({"beams","wooden beams"}),"The hefty beams of wood "+
	"are constructed of oak.\n");
	add_item("oak","The oak tree is a typical wood used for ship " +
	"construction.\n");
	add_item("floor","The floor is made of sturdy planks.\n");
	add_item(({"planks","sturdy planks"}),"The sturdy planks "+
	"appear to be constructed of oak.\n");
	add_item(({"walls","wooden walls","wall"}),"Each wall is "+
	"made of oak.\n");
	add_cmd_item(({"charts","navigational charts"}),({"get","take"}),
	"Taking the charts would only make sense if you were the " +
	"captain of a ship running between MacDunn and SaMorgan!\n");
	add_item("chart","Each chart appears similar. Perhaps looking "+
	"at all the charts may give you a better idea. One looks like "+
	"a map.\n");
	add_item("deck","The main deck of the ship lies outside the "+
	"cabin.\n");
	add_item(({"wax","melted wax","blob","blob of melted wax", "blob of wax"}),
	"The blob of melted wax is a combination of colours, perhaps "+
	"from a series of leaking candles.\n");
	add_item("chair","It's just a simple chair in front of the "+
	"table.\n");
	
	add_exit(THIS_DIR+"deck","deck");
	add_prop(ROOM_I_INSIDE, 1);
	add_prop(ROOM_I_LIGHT, 1);
	add_prop(ROOM_I_TERRAIN_TYPE, TERRAIN_INSHIP);
	set_cabin_sound("@@sounds");
	desk=clone_object(THIS_DIR + "desk");
	desk->move(TO);
	reset_cabin();
}
 
public string sounds()
{
	if(random(2))
	return "The ship barrels through the cold waters at top speed.\n";
	return "The ship rises slightly as it slices through a huge "+
	"wave.\n";
}
