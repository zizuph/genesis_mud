/* 
 * A hobbit dwelling in Waymeet
 * This smial is oriented westward.
 * A low-income hobbit hole
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

//	if I do the paper materials quest, this would be a great place to put some linnen.

void
create_hobbit_room()
{
	set_short("The Bedroom");
	
	set_long("Unlike the rest of the house, the study is quite cluttered. "
		+ "There are many chairs here, but each of them is piled high "
		+ "with half-finished quilts, or old clothes, or books. It doesn't "
		+ "look like there's anywhere at all to sit! The rug on the floor "
		+ "has claw-marks on it, making you think the woman who lives "
		+ "here has at least one cat. There might be a desk against the "
		+ "wall, but it's hard to tell with all the fabric piled on it.\n");
	
	add_item("window", "This small round window would provide views to the "
		+ "outdoors if there weren't thick black curtains pulled over it.\n");
	add_item( ({"curtain", "curtains"}), "The curtains are thick and black, "
		+ "letting in no light and, more importantly, no prying eyes. They "
		+ "have been sewn together, so there is no chance of opening them "
		+ "up.\n");
		
	add_item( ({"chair", "chairs"}), "The chairs would probably be comfortable "
		+ "places to sit if there weren't so much stuff on them.\n");
		
	add_item( ({"quilt", "quilts"}), "None of the quilts is finished, and yet "
		+ "all of them have been started. It seems the woman who lives here "
		+ "is taking old clothes and turning them into quilts.\n");
	add_item( ({"clothes", "fabric"}), "As you look at the clothes, you "
		+ "realize that they're halfway between being clothes and being fabric. "
		+ "The old hobbit woman is ripping out the seams and stacking "
		+ "the pieces of clothes together in like sizes, at which point she "
		+ "treats them like fabric for her quilts.\n");
	add_item( ({"book", "books"}), "There are books here, but they have clothes "
		+ "piled on top of them so that you can't even read the titles on the "
		+ "spines.\n");
	add_item( "desk", "You think this is a desk, judging by the size and shape, "
		+ "but it's hard to be sure. There's so much stuff on it that it could "
		+ "just as easily be a table, or a pile of stuff that's not sitting "
		+ "on anything at all, and you wouldn't know the difference. But it's "
		+ "about the right size and shape to be a desk.\n");
	add_item( ({"mark", "marks", "claw mark", "claw marks"}),
		"The marks look to be about the right size for a house cat or seven "
		+ "to leave when they sharpen their claws on the rug. If you were "
		+ "going to be honest, you'd say there are more holes than there is "
		+ "rug right now.\n");
	
	add_floor_poor("claw-marked");

	add_exit(WAYM_HOUSE_DIR + "h_5_2", "south");
	

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

