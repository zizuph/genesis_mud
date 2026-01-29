/*
 * /d/Gondor/pelargir/street/nroad4.c
 *
 * Modification history:
 *	4 Feb 99, Gnadnar:	clean up, add some items, hint
 *				at new building to north
 */

#pragma strict_types

inherit "/d/Gondor/std/room";
inherit "/d/Gondor/pelargir/city_items";

#include <stdproperties.h>
#include "/d/Gondor/defs.h"

public void	create_gondor();
public void	init();
public int	listen(string arg);
public int	enter(string arg);
public int	knock(string arg);


/*
 * Function name:	create_gondor
 * Description	:	set up the room
 */
public void
create_gondor()
{
    set_short("on an east-west road");
    set_long(BSN(
	"A cobbled road runs east and west, past stone buildings " +
	"to the north and the Sirith River to the south. A bit " +
	"further east, the paved road ends and a spur of rock " +
	"leads out towards a lighthouse."));

    add_item( ({ "peninsula", "spur", "spur of rock", "rock" }),
	BSN(
	"A narrow stretch of rock juts out into the Anduin river."));
    add_item( ({ "buildings", "building", "stone buildings",
	"stone building", }),
	BSN(
	"A two-storey stone building is to the northwest, and "+
	"a smaller building, also of stone, rises directly north. Both " +
	"appear solidly built, but show little imagination or " +
	"elegance in their construction. " +
	"The sounds of hammers and saws can be heard behind the " +
	"door of the smaller building."));
    add_item( ({ "two-storey building", "northwest building", 
	"large building", "larger building", "official building", }),
	BSN("Bland and solid in appearance, it appears " +
	    "to be some kind of official building."));
    add_item( ({ "small building", "smaller building", "north building", }),
	BSN("The rather small building to the north is built of " +
	    "stone, grey and unadorned.  The sounds of hammers and saws "+
	    "can be heard behind its door."));
    add_item( ({ "door", "north door", "building door",
	"small building door", "smaller building door" }),
	BSN("The door has been stained dark brown.\nIt is closed."));
    add_item( ({ "sirith river", "river", "sirith", "river sirith",
	"water", "waters" }),
	BSN("The road runs along the north edge of the Sirith River, "+
	    "whose waters flow swiftly east."));
	
    add_cmd_item( ({ "door", "north door", "building door",
	"small building door", "smaller building door" }),
	"open", 
	"The door is locked.\n");
    add_cmd_item( ({ "door", "north door", "building door",
	"small building door", "smaller building door" }),
	"close", 
	"The door is already closed.\n");
    add_cmd_item( ({ "door", "north door", "building door",
	"small building door", "smaller building door" }),
	({ "lock", "unlock",  }),
	"No keyhole is visible on this side of the door.\n");

    add_cmd_item( ({ "in sirith river", "in river", "in sirith", 
   	 "in river sirith", "in water", "in waters" }),
	({ "swim", "dive" }),
	"The waters are too swift for swimming.\n");

    add_admiral("south");
    add_lighthouse("north");
    add_northside();
    add_cobble();

    add_exit((PELAR_DIR + "street/nroad5"), "east");
    add_exit((PELAR_DIR + "street/nroad3"), "west");
} /* create_gondor */


/*
 * Function name:	init
 * Description	:	add verbs
 */
public void
init()
{
    ::init();
    add_action(listen, "listen");
    add_action(enter, "north");
    add_action(enter, "enter");
    add_action(knock, "knock");
} /* init */


/*
 * Function name:	listen
 * Description	:	let 'em listen to the construction noises
 * Arguments	:	string arg -- whatever the player typed
 * Returns	:	1 if no or good arg, 0 if bad arg
 */
public int
listen(string arg)
{
    if (!strlen(arg) ||
	parse_command(LOW(arg), ({}),
	    "[to] [the] [sound] [sounds] [of] 'hammering' / 'hammer' / "+
	    "'sawing' / 'saw' / 'hammers' / 'saws' "+
	    "/ 'sound' / 'sounds' / 'noise' / 'noises'"))
    {
	WRITE("Judging by the sounds, some kind of construction " +
	    "work is taking place inside the north building.");
	return 1;
    }
    return 0;
} /* listen */

/*
 * Function name:	enter
 * Description	:	handle attempts to enter buildings
 * Arguments	:	string arg -- whatever the player typed
 * Returns	:	1 if we recognize the arg, 0 if not
 */
public int
enter(string arg)
{
    if (QVB == "north")
    {
	arg = "smaller building";
    }
    if (!strlen(arg))
    {
	NF0("Enter what?\n");
    }

    arg = LOW(arg);
    if (parse_command(arg, ({}),
    	"[the] [small] [smaller] [north] 'building' / 'door'"))
    {
	write("The door is closed.\n");
	return 1;
    }
    if (parse_command(arg, ({}),
	"[the] [two-storey] [northwest] [large] [larger] "+
	 "[official] 'building'"))
    {
	write("No entrance to that building is visible from here.\n");
	return 1;
    }
    NF0("Enter what?\n");
} /* enter */


/*
 * Function name:	knock
 * Description	:	respond to knocking on the door
 * Arguments	:	string arg -- whatever the player typed
 * Returns	:	1 if we understand the arg, 0 if not
 */
public int
knock(string arg)
{
    if (strlen(arg) &&
	parse_command(LOW(arg), ({}),
	   "[on] [the] [north] [small] [smaller] [building] 'door'"))
    {
	/* XXX temporary ... just see what enterprising mortal is first
	 * to try it
	 */
	if (!TP->query_wiz_level())
	{
	    log_file("bathhouse", ctime(time()) + ": " +
		TP->query_name() + " knocked.\n");
	}
	write("You knock on the door.\n");
	SAY(" knocks on the door.");
	tell_room(TO,
	    "A female dwarf voice shouts: We're not open yet!\n"+
	    "A female dwarf voice shouts: Come back later!\n");
	return 1;
    }
    return 0;
} /* knock */
