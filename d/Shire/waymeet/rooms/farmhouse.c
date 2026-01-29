/* 
 *Farmhouse for Waymeet
 *
 * --Raymundo, Mar 2020
 */
 
inherit "/d/Shire/std/room";


#include "/d/Shire/sys/defs.h"
#include "../defs.h"
#include <stdproperties.h>
#include <macros.h>
#include <cmdparse.h>
#include <composite.h>
#include <ss_types.h>

void reset_shire_room();
static object innkeeper;
int lit = 1;

void
create_shire_room()
{
	set_long("The farmhouse appears to be one big room. Along the east "
		+ "wall is a bed. On the south wall is a stove, table and sink, "
		+ "making the kitchen area, and against the west wall is a "
		+ "shelf with various kinds of wolf traps on it. Otherwise, "
		+ "this is a pretty average looking home.\n");
	set_short("Inside the Farmhouse");
	add_item("floor", "The floor is just hard-packed dirt. There are "
		+ "some rugs here and there, but mostly it's dirt.\n");
	add_item( ({"rug", "rugs"}), "The rugs are basically a dirty brown "
		+ "color and have obviously not been shaken or cleaned in quite "
		+ "some time.\n");
	add_item( ({"bed"}), "There is just a single bed here, big enough for "
		+ "one, and just one, hobbit. But that's no surprise. Given the "
		+ "state of the farmhouse, you'd be hard pressed to imagine a "
		+ "Mrs. Farmer living here.\n");
	add_item( ({"shelf", "shelves", "wolf trap", "wolf traps"}), "The shelf "
		+ "is a rough wooden board nailed into the wall, more function than "
		+ "beauty. On it sit many wolf traps of various designs. It seems "
		+ "this farmer has put some thought into catching wolves.\n");
	add_item(({"table", "chair"}),
		"The table is big enough for one person to sit at.\n");
	add_item( ({"sink", "dishes", "dirty dishes"}), "The sink is a large "
		+ "stone washbasin. It's nearly full with dirty dishes.\n");
	add_item("stove", "@@exa_stove@@");
	add_item( ({"wall", "walls"}), "The walls are thin, made of hand-hewn "
		+ "boards with small gaps between them. You can feel a bit of a breeze "
		+ "coming through them.\n");
	add_item("ceiling", "The ceiling keeps the rain out, but that's about all "
		+ "you can say for it. It's pretty unremarkable.\n");
	add_item( ({"gap", "gaps", "gaps in the walls"}), "The gaps are big enough "
		+ "to let the wind blow through. Brrrr.\n");
	add_item("home", "This is a farmhouse.\n");
		
	add_room_tell("You smell the fire from the stove.");
	add_room_tell("Wind blows through the gaps in the walls, chilling "
		+ "you.");
	add_room_tell("Wolves howl from the direction of the fields.");
	add_room_tell("A log pops in the fire, sending sparks out of the "
		+ "chimney.");
	
	add_prop(ROOM_I_INSIDE, 1);
	set_room_tell_time(200);
	add_npc(WAYM_NPC_DIR + "boso");
	add_exit(WAYM_ROOM_DIR + "path_5", "out");
	
		
}

void
reset_shire_room()
{

}

void
init()
{
	::init();
	
}

string
exa_stove()
{
	if(lit == 1)
	{
		return("The stove is lit. A fire crackles inside it, warming the house.\n");
	}
}