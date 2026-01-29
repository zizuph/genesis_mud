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
#define BENCH_NAME "simple wooden bench"

public void	init();
public void	leave_inv(object ob, object dest);
public string look_at(string arg);	/* VBFC for chairs */
void reset_shire_room();

//returns sun or moon as an indication of what type of light comes in the room
string
sun_moon()
{
	if(CLOCK->query_night())
	{
		return("moon");
	}
	else
	{
		return("sun");
	}
}
void
create_hobbit_room()
{
	set_short("In the Foyer");
	
	set_long("You stand in the foyer of a tidy hobbit hole. You cannot see "
		+ "a speck of dirt anywhere, much of which is likely because people "
		+ "sit on the bench and remove their boots before entering the smial. "
		+ "to the east, you see the hallway and beyond that the rest of the "
		+ "home." + "@@is_in_chair@@" + "\n");
	
	add_item( ({ "bench", "small bench", "wooden bench", "small wooden bench"}), 
		&look_at(BENCH_NAME) );
	add_item( ({"door"}), "The door is round. It's large enough for a dwarf "
		+ "or even (heaven forfend!) a goblin to enter normally, but humans "
		+ "would need to stoop and ogres... well, ogres would probably have "
		+ "to crawl on their bellies like snakes. The door is painted a "
		+ "bright canary yellow and there is a small window in it.\n");
	add_item("window", "The window in the door allows the master or mistress "
		+ "of this tidy smial to peek outside and see who's there, but "
		+ "equally important, it allows in some " + "@@sun_moon@@"
		+ "-light into the smial.\n");
	
	add_walls();
	add_chair(BENCH_NAME, 
		"[down] [on] / [in] [the] [small] [wooden] 'bench' ", 3);
	add_exit(WAYM_HOUSE_DIR + "h_3_2", "east"); //Hallway
	add_exit(WAYM_STREET_DIR + "street_5", "out");
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
	add_action("under_bench", "look");
	add_action("under_bench", "l");
	
	
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
    case BENCH_NAME:
	return "This small wooden bench is an ideal place for you to sit while "
		+ "removing your boots (you wouldn't track mud into this pefectly "
		+ "clean hobbit hole, would you?). It looks pretty comfortable "
		+ "for a bench.\n"+
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

int
under_bench(string str)
{
	if(!strlen(str))
	{
		return 0;
	}
	if (parse_command(str, TO, " 'under' [the] [simple] [wooden] 'bench' ") )
	{
		write("You look under the " + BENCH_NAME + " and see a few hobbit boots "
			+ "neatly stacked against the wall.\n");
		return 1;
	}
	else
	{
		return 0;
	}
}