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
#define BENCH_NAME "long dining room bench"

public void	init();
public void	leave_inv(object ob, object dest);
public string look_at(string arg);	/* VBFC for chairs */
void reset_shire_room();

void
create_hobbit_room()
{
	set_short("In the Dining Room");
	
	set_long("This is a real hobbit's dining room, all table and not much "
		+ "else. This is the type of place where an entire hobbit family, along "
		+ "with their friends and friends' friends could meet up for a "
		+ "meal. There is a long bench next to the table, ensuring that many "
		+ "people could find a seat.\n" 
		+ "@@is_in_chair@@");
	
	add_item( ({ "bench", "long bench", "dining room bench", "long dining room bench"}), 
		&look_at(BENCH_NAME) );
	add_item( ({"table", "dining room table"}), "The table takes up most of the "
		+ "room. It's a huge table, big enough for many hobbits to sit around.\n");
	add_walls();
	add_window("bright yellow");
	add_chair(BENCH_NAME, 
		"[down] [on] / [in] [the] [small] [wooden] 'bench' ", 12);

	add_exit(WAYM_HOUSE_DIR + "h_3_2", "south");

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
	return "This large kitchen bench looks like just the kind of place for "
		+ "you and a dozen or so of your friends to belly up to the table "
		+ "and eat a meal or three.\n"+
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
