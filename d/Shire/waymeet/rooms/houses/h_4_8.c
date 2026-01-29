/* 
 * A hobbit dwelling in Waymeet
 *
 * --Raymundo, Jan 2020
 */
 
inherit "/d/Shire/std/room";
inherit "/d/Gondor/open/room_chairs/room_chairs";


#include "/d/Shire/sys/defs.h"
#include "../defs.h"
#include <stdproperties.h>
#include <macros.h>
#include <cmdparse.h>
#include <composite.h>
#include <ss_types.h>
#include "/d/Gondor/open/room_chairs/room_chairs.h"

inherit WAYM_LIB_DIR + "base_hobbit_hole.c";

#define SOFA_NAME "one of the kitchen chairs"

void reset_shire_room();
public void	init();
public void	leave_inv(object ob, object dest);
public string	look_at(string arg);	/* VBFC for chairs */

void
create_shire_room()
{
	set_short("The Dining Room");
	
	set_long("The Dining Room is very, very small. In fact, you don't think "
		+ "you could get more than three or four people in here at a time. "
		+ "It's like whoever built this wasn't planning to have guests over--"
		+ "how odd! The dining room itself is quite small, leaving room for "
		+ "little more than a table and four chairs." + "@@is_in_chair@@" );
		
	add_item( ({"room", "dining room"}), "Yes, that's where you are, the "
		+ "dining room, the place where formal meals are eaten. This one "
		+ "pretty small, though.\n");
	add_item( "table", "The table is small, basically the size you'd use "
		+ "to serve breakfast to a couple of kids.\n");
	add_item( ({"guest", "guests"}), "Aren't you a guest? You were invited "
		+ "into the house, right? You didn't just barge in here, did you?\n");
	add_item( ({"tea", "spot of tea"}), "No one is drinking tea here at the "
		+ "moment.\n");
	
	add_item( ({ "kitchen chair", "chair", "chairs", "kitchen chairs"}), 
		&look_at(SOFA_NAME) );

		
	set_room_tell_time(200);
	add_walls();
	

	
	add_prop(ROOM_I_INSIDE, 1);
	add_chair(SOFA_NAME, "[down] [on] / [in] [one] [of] [the] [kitchen] 'chair' / 'chairs' ", 6);

	add_exit(WAYM_HOUSE_DIR + "h_4_4", "west", check_sitting, 1);

		
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
    /* ok, the descs are a little lame, but you get the idea ... */
    switch ( arg )
    {
    case SOFA_NAME:
	return "The chairs are an average size for hobbits. They're made of "
		+ "wood and alltogether completely normal. They've been painted "
		+ "yellow.\n"+
	    sitting_on_chair(SOFA_NAME, this_player(), 0);
    }
}

/* This returns who is in the chair to the long or short description.
 * IF you add + "@@is_in_chair@@" somewhere in your long description.
 */
 
string
is_in_chair()
{
	return("\n" + sitting_on_chair(SOFA_NAME, this_player(), 0));
}