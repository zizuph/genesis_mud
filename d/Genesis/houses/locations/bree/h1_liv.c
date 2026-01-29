/*
 * BREE_DIR + h1_liv.c
 *
 * Varian - Jan 2020
 *
 */

#pragma strict_types

#include "defs.h"
#include <macros.h>
#include <stdproperties.h>
#include <filter_funs.h>
#include <composite.h>

inherit "/w/varian/house/housebase.c";
inherit "/d/Gondor/open/room_chairs/room_chairs";
inherit "/d/Gondor/open/fireplace/fireplace";
inherit "/d/Gondor/common/lib/time";
inherit "/d/Shire/std/room/cmd_parse";

#define CITY            "the village of Bree"
#define STREET          ("/d/Shire/bree/rooms/road/broad03")
#define COUCH_NAME  	"soft brown couch"
#define COUCH_CAPACITY 	3

public void            leave_inv(object ob, object to);
public string          look_at(string arg);

/*
 * Function name:        create_house_room()
 * Description  :        Creates a house room from from the base file
 *                       "housebase.c"
 */

void 

create_house_room()

{
	object door;

	set_items_wood();
	set_items_living();

	set_short("Living room");

	set_long("You are standing in the living room of a large " +
		"house in " + CITY + ". A long table built from a " +
		"dark brown wood stands in the middle of the room with " +
		"a soft brown couch nestled behind it. A narrow " +
		"doorway in the southern wall leads into what appears " +
		"to be a cozy bedroom, while the kitchen is visible " +
		"to the north. A sturdy door beside a small window " +
		"in the eastern wall leads out into " + CITY + ".\n");

	add_item( ({"large house", "townhouse", "large townhouse",
			"house"}),
		"You are currently standing in the living room of a " +
		"large townhouse in Bree. Somewhat larger than the " +
		"other houses you have seen in Bree, you surmise that " +
		"the owner must be quite wealthy.\n");
	add_item( ({"south wall", "southern wall"}),
		"The southern wall of the living room consists of " +
		"wide wooden planks and an open doorway leading into " +
		"a bedroom beyond.\n");
	add_item( ({"doorway", "open doorway"}),
		"A thick wooden frame arches around the open doorway, " +
		"even though there appears to be no door actually " +
		"present. On the other side of the doorway, you can " +
		"see a comfortable looking bedroom.\n");
	add_item( ({"east wall", "eastern wall"}),
		"A sturdy wooden door leading out into the village " +
		"of Bree stands in the middle of the eastern wall. " +
		"There is also a small window here you can examine " +
		"to see what is going on outside.\n");
	add_item( ({"north wall", "northern wall"}),
		"A wide opening in the northern wall leads into a " +
		"tidy looking kitchen. You could walk over there " +
		"to grab something if you are hungry or thirsty.\n");
	add_item( ({"opening", "wide opening"}),
		"A wide opening stretches across most of the " +
		"northern wall, and empties out into a tidy looking " +
		"kitchen.\n");
	add_item( ({"west wall", "western wall"}),
		"The western wall here is quite plain, with nothing " +
		"decorating it, just rows of wide wooden planks.\n");
	add_item( ({"southeast wall", "southeastern wall",
			"northeast wall", "northeastern wall",
			"southwest wall", "southwestern wall",
			"northwest wall", "northwestern wall"}),
		"There is no single wall here, it is a corner.\n");
	add_item( ({"southeast corner", "southeastern corner",
			"northeast corner", "northeastern corner",
			"southwest corner", "southwestern corner",
			"northwest corner", "northwestern corner",
			"corner", "corners"}),
		"Yup, this is where two walls meet, otherwise known " +
		"as a corner. Maybe you could stand in it?\n");
	add_item( ({"room", "living room"}),
		"This is a quaint living room which is surprisingly bare "+
		"at the moment.\n");
	add_item( ({"kitchen", "north"}),
		"Taking a look through the wide opening in the " +
		"northern wall, you can see what appears to be a " +
		"well-stocked and tidy kitchen.\n");
	add_item( ({"bedroom", "south"}),
		"Peeking through the open doorway in the south wall, " +
		"you can see a rather comfortable looking bedroom.\n");
	add_item( ({"doorman", "guard"}),
		"There is a doorman discreetly standing guard outside " +
		"the door here, willing to open or close the door for " +
		"the owner of this house.\n");
	add_item( ({"village", "town", "bree"}),
		"The village of Bree is located near the crossroads " +
		"of the Greenway (which leads south towards Edoras " +
		"and Gondor) and the Great East Road, which leads " +
		"west towards the Shire proper and east towards fabled " +
		"Rivendell.\n");
	add_item( ({"couch", "brown couch", "soft couch", 
		"soft brown couch"}),
		&look_at(COUCH_NAME) );
	add_item( ({ "window", "east window"}), "@@exa_window|" + 
		"You look through the window.\n|" + STREET + "@@");

	set_no_exit_msg( ({"southwest", "southeast", "northeast",
			"northwest", "west"}),
		"It does not appear that you are able walk though the " +
		"walls of this house quite yet.\n");

	add_chair(COUCH_NAME,
		"[down] [in] [the] [soft] [brown] 'couch' / 'sofa'",
		COUCH_CAPACITY, "on");

	room_add_object(OBJ + "table1");
	room_add_object(BREEDOOR + "h1door_in");

	add_prop(ROOM_I_INSIDE,1);

	/*add_exit(STREET, "east", check_sitting, 1, 0);*/
	add_exit(BREE + "h1_kit", "north", check_sitting, 0, 0);
	add_exit(BREE + "h1_bed", "south", check_sitting, 0, 0);

}

/*
 * Function name: init
 * Description  : initialize couch & time
 */

public void
init()
{   
    ::init();
    init_room_chairs();
    add_action(check_time, "time");
    init_cmdparse();
}

/*
 * Function name: leave_inv
 * Description  : This masks parent to be sure that departing players
 *                are removed from chair/sofa occupants. If they leave 
 *                via a normal exit, they've already been made to stand
 *                by the exit efunc check_sitting(). However, if they
 *                leave by quitting, going netdead, teleporting, etc
 *                and we don't call leave_inv_room_chairs(), then they'll
 *                still look as if they're here.
 * Arguments    : object ob -- the departing object
 *                object dest -- its destination
 */

public void
leave_inv(object ob, object to)
{
    ::leave_inv(ob, to);

    leave_inv_room_chairs(ob, to);
}

/*
 * Function name: look_at
 * Description  : This lets people see who is sitting on the couch.
 */

public string
look_at(string arg)
{
    if (arg == COUCH_NAME)
    {
    	return "This soft brown couch rests in the middle of " +
    		"the room, nestled carefully behind a long wooden " +
    		"table.\n" + 
    		sitting_on_chair(COUCH_NAME, this_player(), 0);
    }
}

/*
 * Function name: exa_window
 * Description  : This lets people see the adjacent outside room.
 */

public string
exa_window(string desc, string room_file)
{
    object room = find_object(room_file),
    *in_room_p, *in_room_o;

    in_room_p = FILTER_LIVE(all_inventory(room));
    in_room_o = FILTER_DEAD(all_inventory(room));

    write((room_file)->long());

    if (sizeof(in_room_p))
        this_player()->catch_msg(capitalize(COMPOSITE_LIVE(in_room_p)) + 
        ".\n");

     if (sizeof(in_room_o))   
        this_player()->catch_msg(capitalize(COMPOSITE_DEAD(in_room_o))+ 
        ".\n");

    tell_room(ENV(TP), QCTNAME(TP) + " gazes through the window.\n", TP);

    return "";
} 