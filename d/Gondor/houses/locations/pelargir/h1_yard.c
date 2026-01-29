/*
 * PEL + h1_yard.c
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
inherit "/d/Gondor/common/lib/time";
inherit "/d/Shire/std/room/cmd_parse";
inherit "/d/Gondor/common/lib/herbsearch";
inherit "/d/Gondor/open/room_chairs/room_chairs";
inherit "/d/Gondor/common/lib/drink_water.c";

#define CITY            "the city of Pelargir"
#define STREET          ("/d/Shire/bree/rooms/road/shedge01")
#define BENCH_NAME  	"small stone bench"
#define BENCH_CAPACITY 	2

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
	set_items_yard();

	set_short("Yard");

	set_long("This is a small yard belonging to a wealthy " +
		"townhouse in " + CITY + ". Everything here appears "  +
		"to have been very carefully maintained, with " +
		"several small gardens dotting the manicured " +
		"green grass of the lawn. A small garden path of " +
		"packed dirt winds around the yard carefully, " +
		"trailing away from the townhouse and towards " +
		"the tall hedge that curves around the western " +
		"edge. A small stone bench sits in the middle of " +
		"the yard beside a stone well, offering a quiet " +
		"place for peaceful contemplation.\n");

	add_item( ({"large house", "townhouse", "large townhouse",
			"house"}),
		"You are currently standing in the living room of a " +
		"large townhouse " + CITY + ". Somewhat larger than the " +
		"other houses you have seen in Bree, you surmise that " +
		"the owner must be quite wealthy.\n");
	add_item( ({"door", "narrow door", "wooden door",
			"narrow wooden door"}),
		"This is a narrow wooden door, you could open it to go " +
		"inside the house.\n");
	add_item( ({"hedge", "green hedge", "bree hedge", "wall"}),
		"A thick hedge curves around the western edge of the " +
		"yard like a great green wall. Tall and densely packed, "+
		"the hedge serves as a boundary on the edge of Bree. " +
		"You notice the garden path ending into a small " +
		"recess in the hedge.\n");
	add_item( ({"path", "garden path", "dirt path"}),
		"The small garden path winds all around the yard, " +
		"leading from the large house beside you to a narrow " +
		"alcove recessed into the hedge.\n");
	add_item( ({"alcove", "recess"}),
		"This alcove has clearly been carved into the hedge " +
		"here, creating a thin opening that would allow you " +
		"to see through if you examined it. In fact, you " +
		"think that you could probably enter the opening " +
		"if you wanted to slip out of Bree unnoticed.\n");
	add_item( ({"gardens", "garden", "small garden", 
			"small gardens"}),
		"The yard is filled with several small gardens, each " +
		"well maintained and carefully tucked around the " +
		"garden path. Each of the gardens is surrounded by " +
		"a low bush and is filled with a variety of flowers " +
		"and other plants.\n");
	add_item( ({"here", "yard"}),
		"This is a yard belonging to a wealthy townhouse " +
		CITY + ". Several small gardens have been planted " +
		"in the yard, with a well maintained path winding " +
		"through them.\n");
	add_item( ({"well", "stone well"}),
		"This sturdy looking well has been built from " +
		"a collection of fieldstones mortared together. " +
		"You notice a wooden bucket attached to the well, " +
		"allowing you to get some water if you desired.\n");
	add_item( ({"bucket", "wooden bucket"}),
		"There is a wooden bucket that can be used to " +
		"pull up fresh water from the well. You could " +
		"probably get yourself a drink of water this " +
		"way.\n");
	add_item( ({"plant", "plants", "wildflower", "wildflowers", 
			"flower", "flowers"}),
		"There are a wide variety of colourful wildflowers " +
		"mixed with other plants, each carefully placed to " +
		"provide a relaxing sense of beauty to these " +
		"gardens. You suspect there might be some useful " +
		"herbs hidden here that you could harvest.\n");
	add_item( ({"bush", "low bush", "bushes", "low bushes"}),
		"Several low bushes frame the perimeter of every " +
		"small garden here.\n");
	add_item( ({"grass", "ground", "lawn", "green grass"}),
		"The grass on the ground here is a bright green " +
		"and has been will maintained. Someone has expertly" +
		"trimmed it short to better frame each of the small " +
		"gardens.\n");
	add_item( ({"herb", "herbs", "useful herbs"}),
		"There might be some useful herbs here that could be " +
		"harvested, the only way you could know for sure " +
		"would be if you searched.\n");
	add_item( ({"village", "town", "bree"}),
		"The village of Bree is located near the crossroads " +
		"of the Greenway (which leads south towards Edoras " +
		"and Gondor) and the Great East Road, which leads " +
		"west towards the Shire proper and east towards fabled " +
		"Rivendell.\n");
	add_item( ({ "opening", "thin opening"}), "@@exa_opening|" + 
		"You peek through the opening in the " +
		"hedge.\n|" + STREET + "@@");
	add_item( ({"bench", "stone bench", "small stone bench"}),
		&look_at(BENCH_NAME) );

	set_no_exit_msg( ({"southwest", "northwest", "south", "north"}),
		"The hedge surrounding the yard prevents you from going " +
		"in that direction.\n");
	set_no_exit_msg( ({"southeast", "northeast"}),
		"If you want to go into the house, you will have to " +
		"use the door.\n");

	add_chair(BENCH_NAME,
		"[down] [on] [in] [the] [small] [stone] 'bench' / 'chair'",
		BENCH_CAPACITY, "on");

	set_up_herbs( ({ HERB_DIR + "lothore", HERB_DIR + "redweed", 
                    HERB_DIR + "tuo", HERB_DIR + "alfirin",
                    HERB_DIR + "attanar", HERB_DIR + "basil",
                    HERB_DIR + "blackberry", HERB_DIR + "blueberry",
                    HERB_DIR + "mint", HERB_DIR + "lissuin",
                    HERB_DIR + "tyelka", HERB_DIR + "ungolestel",
                     }),
                ({"ground","field"}), 5);

	add_prop(ROOM_I_INSIDE, 0);

	add_exit(BREE + "h1_kit", "east", "@@kit@@", 0, 0);
	add_exit(BREE + "h1_kit", "open door", "@@kit@@", 0, 1);
	add_exit(STREET, "west", "@@hedge@@", 1, 1);
	add_exit(STREET, "enter", "@@hedge@@", 1, 1);

	set_drink_from(({"well", "stone well", "bucket",
		"wooden bucket"}));

}

/*
 * Function name: init
 * Description  : initialize time
 */

public void
init()
{   
    ::init();
    init_room_chairs();
    init_drink();
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
    if (arg == BENCH_NAME)
    {
    	return "There is a small stone bench in the yard here " +
    	"that is just big enough for two people to share. It " +
    	"looks like a perfect place to relax and enjoy a " +
    	"breath of fresh air.\n" + 
    		sitting_on_chair(BENCH_NAME, this_player(), 0);
    }
}


int
kit()
{
	write("You open the door and slip into the townhouse.\n");
	return 0;
}

int
hedge()
{
	write("As you crawl through the hidden opening in " +
		"the hedge the branches snap back into place and " +
		"you realize to get back into the house you will " +
		"have to use the front door.\n");
	return 0;
}

public string
exa_opening(string desc, string room_file)
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

    tell_room(ENV(TP), QCTNAME(TP) + " peeks through the hedge.\n", TP);

    return "";
}

/*
 * Function name:        drink_message
 * Description  :        Provides a description for drinking from the river
 */

public void
drink_message(string from)
{
    write("Drawing up the bucket from the well, you take a nice " +
    	"long drink of fresh, cool water.\n");
    say(QCTNAME(TP) + " wanders over to the stone well and " +
    	"takes a drink of fresh water from the bucket.\n");
}
/* drink_message */