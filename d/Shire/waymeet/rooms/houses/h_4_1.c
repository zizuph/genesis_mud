/* 
 * A hobbit dwelling in Waymeet
 * This smial is oriented westward.
 * A medium-income hobbit hole
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
#include "/d/Gondor/open/room_chairs/room_chairs.h"

inherit WAYM_LIB_DIR + "base_hobbit_hole.c";
inherit "/d/Gondor/open/room_chairs/room_chairs";
#define BENCH_NAME "scuffed wooden bench"

public void	init();
public void	leave_inv(object ob, object dest);
public string look_at(string arg);	/* VBFC for chairs */
void reset_shire_room();

void
create_hobbit_room()
{
	set_short("In the Foyer");
	
	set_long("You are in the foyer of a warm and cosy (if well-worn) hobbit "
		+ "smial. The coat hooks are a bit bent and scratched, and the bench "
		+ "hobbits sit on to remove their boots or put the boots back on is "
		+ "scuffed. Nevertheless, the pictures on the wall make you feel "
		+ "like this smial is a welcoming smial.\n" 
		+ "@@is_in_chair@@");
	
	add_item( ({ "bench", "scuffed bench", "scuffed wooden bench"}), 
		&look_at(BENCH_NAME) );
	add_item( ({"coat hook", "hook", "coathook", "coat hooks", "hooks", "coathooks"}),
		"The coat hooks are made of brass. They are bent downward, slightly, as "
		+ "if they have held some heavy cloaks for quite a long time, or as if "
		+ "people have pulled down on the cloaks before lifting them off the "
		+ "hooks. Additionally, the hooks are scratched and look worn.\n");
	add_item( ({"picture", "pictures", "painting", "paintings"}), "The "
		+ "paintings on the wall each depict an individual hobbit. Each and "
		+ "every hobbit is smiling and happy (except the hobbit in the painting "
		+ "labeled Uncle Morty; he's frowning and nearly angry-looking!). "
		+ "Beneath each painting on the frame you see a plaque, which labels "
		+ "the subject. The labels read things like 'Grandmother', 'Father', "
		+ "'Aunt Betty', and 'Great Grandfather Grimgrass.' Clearly, "
		+ "the hobbit's family is on display.\n");
	add_item( ({"plaque", "plaques", "frame", "frames"}), 
		"The plaques are on the frames. They label the paintings so you know "
		+ "who's who.\n");
	add_walls();
	
	add_chair(BENCH_NAME, 
		"[down] [on] / [in] [the] [small] [wooden] 'bench' ", 12);

	add_exit(WAYM_HOUSE_DIR + "h_4_2", "west");
	add_exit(WAYM_STREET_DIR + "street_1", "out");

}

void
reset_shire_room()
{
	
}

void
init()
{
	::init();
	init_room_chairs();
}

public void
leave_inv(object ob, object dest)
{
    ::leave_inv(ob, dest);
    leave_inv_room_chairs(ob, dest);
}


public string
look_at(string arg)
{
    switch ( arg )
    {
    case BENCH_NAME:
	return "This is a short little bench. While it seems comfortable, "
		+ "you notice it's very scuffed, as if people have been banging "
		+ "their boots (or Valar forbid swords and shields!) against it "
		+ "while preparing to leave the smial and venture into the Shire "
		+ "at large.\n"+
	    sitting_on_chair(BENCH_NAME, this_player(), 0);
    }
}


/* This returns who is in the chair to the long or short description.
 * IF you add + "@@is_in_chair@@" somewhere in your long description.
 */
 
string
is_in_chair()
{
	return("\n" + sitting_on_chair(BENCH_NAME, this_player(), 0));
}
