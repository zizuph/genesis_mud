/* 
 * A hobbit dwelling in Waymeet
 *
 * --Raymundo, Jan 2020
 */
 
inherit "/d/Shire/std/room";

#include "/d/Shire/sys/defs.h"
#include "../defs.h"
#include <stdproperties.h>
#include <macros.h>
#include <cmdparse.h>
#include <composite.h>
#include <ss_types.h>

inherit WAYM_LIB_DIR + "base_hobbit_hole.c";

void reset_shire_room();
//Keeping track of the rug.
int rug = 0;

//Gives people a message that they might want to light the lamps.
int
lamp_message()
{
	write("\n\nAs you walk north, you enter a dark room and begin to feel around "
		+ "for a lamp or a sconce to light.\n");
	return 0;
}

void
create_shire_room()
{
	set_short("In the North Hallway");
	
	set_long("You find yourself completely under the hill now, and while it "
		+ "should be dark, lamps on the wall keep the quite bright. To the "
		+ "east you can just make out a formal dining room, while to the "
		+ "west is the master bedroom. The room to the north is quite "
		+ "dark, and you have trouble making out what's there. "
		+ "@@long_rug@@" + "\n");
		
	set_room_tell_time(200);
	
	add_item( ({"lamp", "lamps"}), "The lamps are nailed into the wall. They "
		+ "provide light for the hallway.\n");
	add_item( ({"rug", "rugs"}), "@@exa_rug@@");
		
	add_cmd_item( ({"lamp", "lamps"}), "light", "The lamps are already "
		+ "lit.\n");
	add_cmd_item( ({"lamp", "lamps"}), "extinguish", "You don't see an easy "
		+ "way to extinguish the lamps, and so you leave them lit.\n");
	add_walls();
	remove_item("floor");
	add_item("floor", "@@exa_floor@@");
	add_item(
		({"patch", "patches", "discolored patch", "discolored patches", "discolored", "portion", "discolored portion"}),
		"@@exa_patch@@");
	add_item( ({"scratch", "scratches"}), "@@exa_scratches@@");
	add_item( ({"floorboard", "floor board", "floorboards", "floor boards"}),
		"@@exa_floorboards@@");
	add_item( ({"edge", "edges", "fray", "frayed", "frayed edges", "frayed edge"}),
		"The edges of the rug are frayed, as if someone has been moving the rug "
		+ "often.\n");
	add_cmd_item("rug", "move", "@@move_rug@@");
	add_cmd_item( ({"board", "floorboard", "floor board", "up board", "up floorboard", "up floor board", "board up", "floorboard up", "floor board up"}), 
		"lift", "@@lift_board@@");
		
	
	add_room_tell("Lamplight flickers against the walls.");
	add_room_tell("A lamp flickers, and shadows dance on the walls.");
	
	add_prop(ROOM_I_INSIDE, 1);
	
	add_exit(WAYM_HOUSE_DIR + "h_1_2", "south");
	add_exit(WAYM_HOUSE_DIR + "h_1_6", "east");
	add_exit(WAYM_HOUSE_DIR + "h_1_7", "west");
	add_exit(WAYM_HOUSE_DIR + "h_1_8", "north", lamp_message, 0, 0);
		
}

void
reset_shire_room()
{
	rug = 0;
}

void
init()
{
	::init();
	
}

//How the rug looks in the long description.
string
long_rug()
{
	if(rug == 0)
	{
		return("Beneath your feet is another rug.");
	}
	else
	{
		return("A rug is pushed up against the wall, revealing "
			+ "a discolored portion of the floor.");
	}
}

//how the rug looks in the add_item
string
exa_rug()
{
	if(rug == 0)
	{
		return("The rug is red and black, exactly the same as the "
			+ "rug to the south, except you notice the edges "
			+ "are frayed.\n");
	}
	else
	{
		return("The rug is red and black, exactly the same as the "
			+ "rug to the south. This rug is bunched up and pushed "
			+ "against one of the walls, revealing a discolored patch "
			+ "on the floor.\n");
	}
}

//The way the floor looks
string
exa_floor()
{
	if(rug == 0)
	{
		return("The floor is wooden and especially clean. There is a large "
			+ "rug in the center of it.\n");
	}
	else
	{
		return("The floor is wooden and would look especially clean, except "
			+ "that the rug has been pushed up against the wall, revealing a "
			+ "discolored patch on the floor.\n");
	}
}

//The discolored patch
string
exa_patch()
{
	if(rug==0)
	{
		return("You find no patch. You do, however, find a very nice "
			+ "rug in the middle of an exceptionally clean floor.\n");
	}
	else
	{
		return("On closer inspection, you realize that this patch of flooring "
			+ "isn't discolored. On the contrary, the rest of the flooring "
			+ "has faded over the years as it has been exposed to light. "
			+ "This patch, protected by the rug, retained the original "
			+ "color of the floor. You notice some scratches on some of the "
			+ "floorboards.\n");
	}
}

//the scratches between the floorboards.
string
exa_scratches()
{
	if(rug==0)
	{
		return("You see no scratches.\n");
	}
	else
	{
		return("The scratches look like the boards have been rubbing "
			+ "together... almost as if someone has been lifting the "
			+ "boards up... Curious.\n");
	}
}
//floorboards description
string
exa_floorboards()
{
	if(rug == 0)
	{
		return("The floorboards look nice and clean, much like the floor "
			+ "itself does.\n");
	}
	else
	{
		return("The scratches look like the boards have been rubbing "
			+ "together... almost as if someone has been lifting the "
			+ "boards up... Curious.\n");
	}
}

//move the rug on the floor back and forth, changing
// descriptions.
int
move_rug()
{
	if(rug == 0)
	{
		write("You move the rug against the wall, dragging it along "
			+ "the floor. So this is how the edges of the rug got so "
			+ "frayed! Looking back, you notice a discolored patch on "
			+ "the floor where the rug used to be.\n");
		say(QCTNAME(TP) + " pushes the rug up against the wall, revealing "
			+ "a discolored patch on the floor.\n");
		rug = 1;
		return 1;
	}
	else
	{
		write("You drag the rug back into place, concealing the discolored "
			+ "patch on the floor once more.\n");
		say(QCTNAME(TP) + " drags the rug back into place, concealing the "
			+ "discolored patch on the floor again.\n");
		rug = 0;
		return 1;
	}
}

//Lift the floor board, only to find... a red herring.
int
lift_board()
{
	if(rug == 0)
	{
		write("You reach down and try to pull up one of the floor boards, "
		+ "but it is firmly in place. Clearly, the floor has been installed "
		+ "very well!\n");
		say(QCTNAME(TP) + " tries to lift up a floor board, but isn't "
			+ "able to do so.\n");
		return 1;
	}
	else
	{
		write("You lift up the boards and reach your hand down into "
		+ "the gap. You feel nothing but hard-packed earth. Other than that, "
		+ "the entire hole is empty.\n");
		say(QCTNAME(TP) + " lifts up a floor board from the discolored "
			+ "patch on the floor. " + CAP(HE_SHE(TP)) + " finds nothing "
			+ "inside the hole, however.\n");
		return 1;
	}
}