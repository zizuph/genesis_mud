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


void
create_shire_room()
{
	set_short("In the Kitchen");
	
	set_long("The kitchen is the heart of the home, and that seems true here. "
		+ "A pot with dinner in it sits on top of the stove, filling the "
		+ "room with delicious smells. You can see the countertops have been "
		+ "recently cleaned, and all the cupboard doors are shut. A tea "
		+ "kettle sits on one counter, and the pantry door is shut tight.\n");
	
	add_item( ({"counter", "counter top", "counters", "counter tops"}),
		"The counter tops are made of river stone. They look like they were "
		+ "just cleaned. A tea pot sits on one of them.\n");
	add_item( "tea pot", "The tea pot has some scratches and dents. It "
		+ "has seen a lot of use.\n");
	add_item( ({"cupboard", "cupboards", "cupboard doors", "cupboard door"}),
		"The cupboard doors are made of oak. Like everything else in the "
		+ "kitchen, they look clean and well taken care of. They are "
		+ "closed.\n");
	add_item("pantry", "The pantry looks like a great place to store food "
		+ "items like dried beans, rice, potatoes, tea leaves, salt and "
		+ "spices. This being a hobbit's home, the pantry is likely well-"
		+ "stocked.\n");
	add_item("pantry door", "The pantry door is closed.\n");
	add_item("kitchen", "This is the part of the house where meals "
		+ "are cooked.\n");
	add_item("sink", "Next the the counter, you notice a sink. It seems large "
		+ "enough to wash some dishes in, if there were any dirty dishes "
		+ "about.\n");
		
		
	add_cmd_item( ({"cupboard", "cupboards", "cupboard doors", "cupboard door"}),
		"open",
		"You reach up to open the cupboard and then feel guilty. It's not "
		+ "your house, so you probably shouldn't open them.\n");
	add_cmd_item("tea pot", "get", "You touch the tea pot and burn your "
		+ "fingers. Maybe this isn't the best time to take the tea pot.\n");
	add_cmd_item("tea pot", "take", "You touch the tea pot and burn your "
		+ "fingers. Maybe this isn't the best time to take the tea pot.\n");
	add_cmd_item("pantry door", "open", 
		"You try to open the pantry door, but it's "
		+ "stuck.\n");
	add_cmd_item( ({"dishes", "dirty dishes"}), "wash", "But there aren't "
		+ "any dirty dishes here!\n");
	add_cmd_item( ({"sink"}), "fill", "You'd need a bucket of water to fill "
		+ "the sink.\n");
	add_cmd_item("sink", "drain", "The sink is empty already!\n");
	
	add_walls();
	add_stove("black");
	
	add_object(WAYM_OBJ_DIR + "table.c", 1);
	add_prop(ROOM_I_INSIDE, 1);
	
	add_exit(WAYM_HOUSE_DIR + "h_1_2", "west");
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
