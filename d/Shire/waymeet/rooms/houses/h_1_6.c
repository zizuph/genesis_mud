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
	set_short("In the Dining Room");
	
	set_long("The Dining Room is larger than it appeared from the hall, "
		+ "with room for a dozen guests or so around the large table that "
		+ "dominates not just the center of the room, but the room in its "
		+ "entirety. There is room to move about, but just barely, and "
		+ "perhaps it would feel like even less than barely if some of the "
		+ "guests were big people, or even very fat hobbits, especially "
		+ "against the east wall, where the curve of the ceiling could make "
		+ "headroom a bit tight. Nevertheless, this could be a nice place "
		+ "for a birthday, or a holiday, or a spot of tea after a "
		+ "fireworks show." + "@@is_in_chair@@" + "\n");
		
	add_item( ({"room", "dining room"}), "Yes, that's where you are, the "
		+ "dining room, the place where formal meals are eaten.\n");
	add_item( "table", "This is a big, big table, at least for a hobbit. "
		+ "You could easily fit a dozen hobbits around the table, and "
		+ "maybe as many dwarves. Now humans, perhaps only four or so, "
		+ "since the east wall slopes rather abruptly, cutting off "
		+ "some headroom. All in all, this is a nice table for "
		+ "entertaining guests.\n");
	add_item( ({"guest", "guests"}), "Aren't you a guest? You were invited "
		+ "into the house, right? You didn't just barge in here, did you?\n");
	add_item( ({"tea", "spot of tea"}), "No one is drinking tea here at the "
		+ "moment.\n");
	add_item("east wall", "The east wall slopes quite agressively. If you "
		+ "were a child, or perhaps if you were very short, it would be fine. "
		+ "But for full size adults, it's best to sit elsewhere.\n");
	add_item("headroom", "There's ample headroom here. But if you go to the "
		+ "east side of the table, that would be a bit tight.\n");
	add_item( ({ "kitchen chair", "chair", "chairs", "kitchen chairs"}), 
		&look_at(SOFA_NAME) );
	add_cmd_item("about", "move", "You move about the room. It's really "
		+ "quite easy, despite the large table.\n");
		
	set_room_tell_time(200);
	add_walls();
	

	
	add_prop(ROOM_I_INSIDE, 1);
	add_chair(SOFA_NAME, "[down] [on] / [in] [one] [of] [the] [kitchen] 'chair' / 'chairs' ", 6);

	add_exit(WAYM_HOUSE_DIR + "h_1_5", "west", check_sitting, 1);

		
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
	return "The kitchen chairs are hobbit-sized, which is to say pretty small "
		+ "for humans or elves. Nevertheless, you could see yourself sitting "
		+ "in one of these chairs, eating some cakes, and maybe drinking "
		+ "(quite) a few pints of beer.\n"+
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