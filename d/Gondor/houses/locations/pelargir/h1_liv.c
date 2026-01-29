/*
 * PEL + h1_liv.c
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
#define STREET          ("/d/Gondor/pelargir/streets/belfalas04")
#define COUCH_NAME  	"red cushioned sofa"
#define COUCH_CAPACITY 	3

public void            leave_inv(object ob, object to);
public string          look_at(string arg);
public string		   room_desc(string arg);

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

	set_long(room_desc);

	add_cmd_item( ({"sign", "small sign"}), "read", "@@sign_desc@@");

	add_item( ({"sign", "small sign"}),
		"@@sign_desc@@");
	add_item( ({"large house", "house", "wealthy house", "manor"}),
		"This is a large, wealthy house that sits on Belfalas Way in " +
		"the northern end of " + CITY + ".\n");
	add_item( ({"south wall", "southern wall"}),
		"Four marble columns stand tall and proud along the southern " +
		"wall here, the middle two flanking a wide opening which leads " +
		"into the kitchen. On either side of the opening, delicately " +
		"coloured glass mosaics depict landscapes of the surrounding " +
		"area.\n");
	add_item( ({"doorway", "open doorway"}),
		"This open doorway grants entrance into a spacious and luxurious " +
		"bedroom.\n");
	add_item( ({"east wall", "eastern wall"}),
		"A massive wooden bookcase, divided into several sections, runs " +
		"across the entire eastern wall. The collection appears to be " +
		"even larger than some libraries you have seen!\n");
	add_item( ({"north wall", "northern wall"}),
		"Four marble columns are spaced out along the northern wall. Two " +
		"large mosaics of coloured glass flank an open doorway that " +
		"leads into a bedroom.\n");
	add_item( ({"opening", "wide opening"}),
		"This wide opening leads into a large, well-organized kitchen.\n");
	add_item( ({"west wall", "western wall"}),
		"Several marble columns line the western wall, with colourful " +
		"glass mosaics depicting the local landscape decorating the " +
		"plastered walls in between. In the middle of the wall, a large " +
		"window beside an ornate wooden door looks out into " + CITY  +
		" beyond.\n");
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
	add_item( ({"room", "living room", "here"}),
		room_desc);
	add_item( ({"kitchen", "large kitchen", "south"}),
		"There is a large, well-organized kitchen at the southern end " +
		"of this manor. The smells drifting in from there are mouth-" +
		"watering! Perhaps you should visit and see what is on the " +
		"menu?\n");
	add_item( ({"bedroom", "north"}),
		"A spacious and luxurious bedroom can be seen through the open " +
		"doorway in the northern wall.\n");
	add_item( ({"doorman", "guard"}),
		"There is a doorman discreetly standing guard outside " +
		"the door here, ensuring no unwelcome visitors enter the " +
		"manor.\n");
	add_item( ({"city", "town", "pelargir"}),
		"The bustling city of Pelargir stands along the banks of the " +
		"great river Anduin. It is the largest port in the nation of " +
		"Gondor, with many large ships sailing in from the sea.\n");
	add_item( ({"couch", "sofa", "wood sofa", "wooden sofa", 
		"red sofa", "cushioned sofa", "red cushioned sofa"}),
		&look_at(COUCH_NAME) );
	add_item( ({"window", "west window"}), "@@exa_window|" + 
		"You look out through the window.\n|" + STREET + "@@");
	add_item( ({"marble", "column", "marble column", "marbles", "columns",
			"marble columns", "fluted column", "fluted columns",
			"white marble", "white marble columns"}),
		"These tall columns appear to be mostly decorative, their fluted " +
		"bodies reaching up from the floor to gracefully touch the " +
		"ceiling. Carved from large blocks of white marble, their fluted " +
		"lengths bring a touch of class and elegance to this manor.\n");
	add_item( ({"mosaic", "mosaics", "glass", "colourful glass",
			"glass mosaic", "glass mosaics", "colourful glass mosaics",
			"colourful glass mosaic", "landscape", "landscapes",
			"colourful landscape", "colourful landscapes"}),
		"Thousands of small bits of coloured glass have been set into the " +
		"plastered walls here, depicting beautiful scenes of local " +
		"landscapes from southern Gondor.\n");
	add_item( ({"plaster", "plaster wall", "plaster walls", "plastered wall",
			"plastered walls"}),
		"The walls here have been plastered, but between the marble " +
		"columns, glass mosaics and the wooden bookcase it doesn't seem "+
		"like you ever really notice the plaster unless you look for it!\n");
	add_item( ({"ground", "floor", "polished stone", "polished stone floor",
			"stone floor", "stone"}),
		"The floor here has been crafted from large slabs of polished " +
		"stone. Swirls of grey and black stretch and curl in all " +
		"directions as the natural beauty and luxury is readily " +
		"apparent.\n");
	add_item( ({"ceiling", "up", "arch", "arches", "dome"}),
		"The ceiling above arches ever so slightly into a dome, with " +
		"clear glass panels which allow light in to reflect off the " +
		"glass mosaics, making them shimmer with the passage of time.\n");
	add_item( ({"panel", "panels", "glass panel", "glass panel",
			"clear panel", "clear panels", "clear glass panel",
			"clear glass panels"}),
		"Several panels of clear glass have been placed around the " +
		"perimeter of the ceiling, allowing light to shine in and " +
		"illuminate the glass mosaics along the walls.\n");
	add_item( ({"bookcase", "case", "bookshelf", "bookshelves",
			"book case", "large bookcase", "large book case", 
			"wooden book case", "large wooden bookcase", "wooden bookcase",
			"large wooden book case"}),
		"There is a large wooden bookcase that covers the entire eastern " +
		"wall here! The thick slabs of wood have been polished and " +
		"ornately carved to enhance the beauty of the structure. The " +
		"luxury is staggering, you do not believe you have seen so many " +
		"stacks of books anywhere other than a library - and perhaps not " +
		"even then!\n");
	add_item( ({"book", "books", "stack", "stacks", "stack of books",
			"stacks of books"}),
		"There are hundreds of books in this collection here, the owner " +
		"of the manor doubtlessly relaxes by reading them in their spare " +
		"time.\n");

	set_no_exit_msg( ({"southwest", "southeast", "northeast",
			"northwest"}),
		"It does not appear that you are able walk though the " +
		"walls of this house quite yet.\n");

	add_chair(COUCH_NAME,
		"[down] [in] [the] [red] [wood] [wooden] " +
		"[cushioned] 'couch' / 'sofa'",
		COUCH_CAPACITY, "on");

	room_add_object(OBJ + "table2");
	room_add_object(PELDOOR + "h1door_in");

	add_prop(ROOM_I_INSIDE,1);

	/*add_exit(STREET, "west", check_sitting, 1, 0);*/
	add_exit(PEL + "h1_bed", "north", check_sitting, 0, 0);
	add_exit(PEL + "h1_kit", "south", check_sitting, 0, 0);
}

string
sign_desc()
{
   	return
   		"House Commands - For the owner only!\n" +
        "If you would like to invite, or uninvite other people " +
        "into your home, you must go see the doorman on the " +
        "other side of this door. There you will have the following " +
        "commands:\n\n" +
        "hinvite <name> - The doorman will allow this person inside.\n" +
        "huninvite <name> - The doorman stops allowing this person " +
        "inside.\n" +
        "hinvited - The doorman will remind you who is currently allowed " +
        "inside.\n\n" +
        "But remember! The door must be unlocked first!\n";
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
    	return "The wooden frame of this sofa is covered with elegant " +
    		"red cushions. This fine piece of furniture is not only " +
    		"beautiful, but it also looks very comfortable.\n" + 
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

public string
room_desc(string arg)
{
	return
		("This is the living room of a large and wealthy home in " + CITY + 
		". Fluted columns of white marble line the walls, stretching up " +
		"to clutch at the edges of the ceiling here. In between most " +
		"of the columns, glass mosaics have been embedded in the walls " +
		"to depict stunning landscape scenes. A large wooden bookcase " +
		"reaches across much of the eastern wall, with an open doorway " +
		"leading north into a luxurious bedroom and a wide opening " +
		"spilling out into the kitchen. An ornate wooden door in the " +
		"western wall leads back out into " + CITY + ", with a large " +
		"window beside it that you can look through. A comfortable " +
		"looking sofa with a wooden table in front of it sit in the " +
		"middle of the room.\nA small sign is visible beside the door.\n");
}