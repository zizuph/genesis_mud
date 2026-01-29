/*
 * PEL + h1_kit.c
 *
 * Varian - Aug 2021
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

#define CITY            "the city of Pelargir"
#define STREET          ("/d/Shire/bree/rooms/road/broad02")

/*
 * Function name:        create_house_room()
 * Description  :        Creates a house room from from the base file
 *                       "housebase.c"
 */

void 

create_house_room()

{
	set_items_wood();
	set_items_kitchen();

	set_short("Kitchen");

	set_long("This tidy kitchen covers the north end of a large " +
		"house in " + CITY + ". A narrow wooden counter runs " +
		"along the eastern wall of the kitchen, while a " +
		"large black cauldron rests in the fireplace located in " +
		"the southwest corner. A wide pantry stands in the " +
		"northwest corner, nestled between a small window " +
		"in the north wall and a narrow door in the west " +
		"wall. A wide opening in the south wall leads into " +
		"a sparsely decorated living room.\n");

	add_item( ({"large house", "townhouse", "large townhouse",
			"house"}),
		"You are currently standing in the kitchen of a " +
		"large townhouse in Bree. Somewhat larger than the " +
		"other houses you have seen in Bree, you surmise that " +
		"the owner must be quite wealthy.\n");
	add_item( ({"south wall", "southern wall"}),
		"The southern wall is essentially a wide opening which " +
		"leads into the living room of this house.\n");
	add_item( ({"door", "narrow door", "wooden door",
			"narrow wooden door"}),
		"This is a narrow wooden door, you could open it to go " +
		"outside and into the yard.\n");
	add_item( ({"yard", "back yard", "west"}),
		"You cannot see the yard from here, but that is where " +
		"you would end up if you went through the door here.\n");
	add_item( ({"east wall", "eastern wall"}),
		"A long, narrow counter built out of wood stretches " +
		"out across the entire length of the eastern wall.\n");
	add_item( ({"north wall", "northern wall"}),
		"There is a small window carved into the wooden planks " +
		"of the north wall, gazing out into " + CITY + ".\n");
	add_item( ({"opening", "wide opening"}),
		"A wide opening stretches across most of the " +
		"southern wall, and empties out into a sparsely " +
		"furnished living room.\n");
	add_item( ({"west wall", "western wall"}),
		"The western wall has a narrow doorway leading out " +
		"into the yard beyond, bookended by a wide pantry " +
		"and a large cauldron.\n");
	add_item( ({"southeast wall", "southeastern wall",
			"northeast wall", "northeastern wall",
			"southwest wall", "southwestern wall",
			"northwest wall", "northwestern wall"}),
		"There is no single wall here, it is a corner.\n");
	add_item( ({"southeast corner", "southeastern corner",
			"northeast corner", "northeastern corner"}),
		"Yup, this is where two walls meet, otherwise known " +
		"as a corner. The narrow counter that runs along " +
		"the eastern wall ends here.\n");
	add_item( ({"living room", "south"}),
		"To the south is a quaint living room which is " +
		"surprisingly bare at the moment.\n");
	add_item( ({"fireplace", "stone fireplace", "fire"}),
		"There is a stone fireplace burning in the southwest " +
		"corner of the kitchen, with a large iron cauldron " +
		"hanging there.\n");
	add_item( ({"kitchen", "here", "room"}),
		"This tidy kitchen covers the north end of a large " +
		"house in " + CITY + ". A narrow wooden counter runs " +
		"along the eastern wall of the kitchen, while a " +
		"large black cauldron rests in the fireplace located in " +
		"the southwest corner. A wide pantry stands in the " +
		"northwest corner, nestled between a small window " +
		"in the north wall and a narrow door in the west " +
		"wall. A wide opening in the south wall leads into " +
		"a sparsely decorated living room.\n");
	add_item( ({"village", "town", "bree"}),
		"The village of Bree is located near the crossroads " +
		"of the Greenway (which leads south towards Edoras " +
		"and Gondor) and the Great East Road, which leads " +
		"west towards the Shire proper and east towards fabled " +
		"Rivendell.\n");
	add_item( ({ "window", "north window"}), "@@exa_window|" + 
		"You look through the window.\n|" + STREET + "@@");

	set_no_exit_msg( ({"southwest", "southeast", "northeast",
			"northwest", "east", "north"}),
		"It does not appear that you are able walk though the " +
		"walls of this house quite yet.\n");

	room_add_object(OBJ + "counter1");
	room_add_object(OBJ + "cauldron1");
	room_add_object(OBJ + "pantry1");

	add_prop(ROOM_I_INSIDE, 1);

	add_exit(PEL + "h1_liv", "north", 0, 0, 0);

}

/*
 * Function name: init
 * Description  : initialize time
 */

public void
init()
{   
    ::init();
    add_action(check_time, "time");
}


int
yard()
{
	write("You open the door and slip out into the yard.\n");
	return 0;
}

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