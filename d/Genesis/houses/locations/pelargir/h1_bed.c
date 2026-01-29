/*
 * PEL + h1_bed.c
 *
 * Varian - Aug 2021
 *
 */

#pragma strict_types

#include "defs.h"
#include <macros.h>
#include <stdproperties.h>

inherit "/w/varian/house/housebase.c";
inherit "/d/Gondor/open/room_chairs/room_chairs";
inherit "/d/Gondor/open/fireplace/fireplace";
inherit "/d/Gondor/common/lib/time";
inherit "/d/Shire/std/room/cmd_parse";

#define CITY            "the city of Pelargir"
#define BED_NAME 		"wide luxurious bed"
#define BED_CAPACITY 	2

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
	set_items_wood();
	set_items_bedroom();

	set_short("Bedroom");

	set_long("This is a spacious bedroom, spread out across " +
		"the southern end of a large house in " + CITY +
		". A magnificently ornate wardrobe, tall enough to " +
		"reach the ceiling stands against the western wall " +
		"while a wide, luxurious bed stretches out from the " +
		"southern wall in a welcoming manner. The rest of the " +
		"bedroom is currently rather sparse, lacking any " +
		"formal decoration at the moment. An open doorway in " +
		"the northern wall leads back to the living room.\n");

	add_item( ({"large house", "townhouse", "large townhouse",
			"house"}),
		"You are currently standing in the bedroom of a " +
		"large townhouse in Bree. Somewhat larger than the " +
		"other houses you have seen in Bree, you surmise that " +
		"the owner must be quite wealthy.\n");
	add_item( ({"south wall", "southern wall"}),
		"Aside from the bed resting against it, the southern " +
		"wall is quite plain, with nothing decorating it, " +
		"just rows of wide wooden planks.\n");
	add_item( ({"doorway", "open doorway"}),
		"A thick wooden frame arches around the open doorway, " +
		"even though there appears to be no door actually " +
		"present. On the other side of the doorway, you can " +
		"see a sparsely furnished living room\n");
	add_item( ({"east wall", "eastern wall"}),
		"The eastern wall here is quite plain, with nothing " +
		"decorating it, just rows of wide wooden planks.\n");
	add_item( ({"north wall", "northern wall"}),
		"The northern wall is unadorned, with only an open " +
		"doorway which allows you to go back to the living " +
		"room.\n");
	add_item( ({"west wall", "western wall"}),
		"A tall, ornate wardrobe rests against the western " +
		"wall here, clearly a place for the owner of this " +
		"house to store some person items.\n");
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
	add_item( ({"living room", "north"}),
		"The living room, and entrance, to the house " +
		"is visible on the other side of the open doorway " +
		"which breaks through the northern wall.\n");
	add_item( ({"bedroom", "room"}),
		"Aside from a beautiful wardrobe and a luxurious " +
		"looking bed, the rest of this room appears to be " +
		"currently unadorned.\n");
	add_item( ({"village", "town", "bree"}),
		"The village of Bree is located near the crossroads " +
		"of the Greenway (which leads south towards Edoras " +
		"and Gondor) and the Great East Road, which leads " +
		"west towards the Shire proper and east towards fabled " +
		"Rivendell.\n");
	add_item( ({"bed", "luxurious bed", "wide bed", 
		"wide luxurious bed"}),
		&look_at(BED_NAME) );

	set_no_exit_msg( ({"southwest", "southeast", "northeast",
			"northwest", "west", "east", "south"}),
		"It does not appear that you are able walk though the " +
		"walls of this house quite yet.\n");

	add_chair(BED_NAME,
		"[lay] [down] [in] [the] [soft] [luxurious] [wide] " +
		"'bed' ",
		BED_CAPACITY, "on");

	room_add_object(OBJ + "wardrobe1");

	add_prop(ROOM_I_INSIDE,1);

	add_exit(BREE + "h1_liv", "north", check_sitting, 0, 0);

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
    add_action("do_sleep","sleep");
    add_action("do_sleep","nap");
    add_action("do_sleep","lay");
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
 * Description  : This lets people see who is sitting on the bed.
 */

public string
look_at(string arg)
{
    if (arg == BED_NAME)
    {
    	return "This luxurious bed looks quite wide and " +
    		"very soft, a bed fit for a king and queen!\n" + 
    		sitting_on_chair(BED_NAME, this_player(), 0);
    }
}

/*
 * Function name:        do_sleep
 * Description  :        Provides an emote to sleep in the bed
 * Returns      :        int 0 - Prompt for proper syntax
 *                       int 1 - Returns the emote
 */
int
do_sleep(string str)
{
    if(!str)
    {
        notify_fail("What are you trying to sleep on? The bed?\n");
        return 0;
    }

    if((str != "in the bed")  && (str != "in the wide bed") 
    	&& (str != "on the bed") && (str != "on the wide bed") 
    	&& (str != "on the luxurious bed") && (str != "bed")
        && (str != "in the luxurious bed") && (str != "wide bed")
        && (str != "on the wide luxurious bed")
        && (str != "in the wide luxurious bed")
        && (str != "in bed") && (str != "luxurious bed")
        && (str != "in wide bed") && (str != "in luxurious bed")
        && (str != "on bed") && (str != "on luxurious bed")
        && (str != "on wide bed"))
    { 
        ("What are you trying to sleep on? The bed?\n");
        return 1;
    }
    write("You climb into the wide, luxurious bed and discover " +
    	"that it is even more comfortable than it looks! " +
    	"Closing your eyes, you enjoy a nice little nap.\n");
    SAYBB(" closes their eyes and takes a short nap on the " +
    	"wide luxurious bed.\n");
    return 1;
}