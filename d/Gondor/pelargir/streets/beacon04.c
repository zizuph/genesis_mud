/*
 * /d/Gondor/pelargir/rooms/beacon04.c
 *
 *
 * Copyright (C) 1999 by Cooper Sherry (Gorboth) and
 *	Nancy L. Mintz (Gnadnar)
 * 
 */

#pragma strict_types

inherit "/d/Gondor/pelargir/pelargir_room";

#include "/d/Gondor/defs.h"
#include "/d/Gondor/pelargir/pelargir_room.h"

#define	BATH_ENTRY	(PELAR_DIR + "misc/bathhouse/entry")

public void	create_pelargir_room();
public void	init();
public int	enter(string arg);
public int	knock(string arg);


/*
 * Function name:	create_pelargir_room
 * Description	:	set up the room
 */
public void
create_pelargir_room()
{
    set_part(PART_NORTH);
    set_street_name(STREET_BEACON);
    set_room_type(TYPE_STREET);

    set_extra_desc("The street runs past a stone building " +
        "to the north and the Sirith River to the south. A bit " +
        "further east, the paved road ends and a spur of rock " +
        "leads out towards a lighthouse.");

    add_item( ({ "peninsula", "spur", "spur of rock", "rock" }),
        BSN(
        "A narrow stretch of rock juts out into the Anduin river."));
    add_item( ({ "sirith river", "river", "sirith", "river sirith",
        "water", "waters" }),
        BSN("The road runs along the north edge of the Sirith River, "+
            "whose waters flow swiftly east."));

    add_item( ({ "buildings", "building", "stone buildings",
        "stone building", "small building", "smaller building",
	"north building", }),
        BSN(
        "A small building of stone construction rises directly to"
      + " the north. It appears to be solidly built, although not vastly"
      + " elegant. A small plaque is affixed to its door."));
    add_item( ({ "dark brown door", "dark door", "brown door",
	"door", "north door", "building door",
        "small building door", "smaller building door" }),
        BSN("The dark brown door has no lock or handle on this side, " +
	    "but a small brass plaque is affixed to its center."));
    add_item( ({ "small brass plaque", "small plaque", "brass plaque",
	"plaque", "door plaque" }),
	"\n"+
	"                        Pelargir Baths\n" +
	"\n" +
	"                 Please knock for admittance.\n\n");
    add_cmd_item( ({ "small brass plaque", "small plaque", "brass plaque",
	"plaque", "door plaque" }),
	"read",
	"\n"+
	"                        Pelargir Baths\n" +
	"\n" +
	"                 Please knock for admittance.\n\n");
        

    add_cmd_item( ({ "in sirith river", "in river", "in sirith", 
   	 "in river sirith", "in water", "in waters" }),
        ({ "swim", "dive" }),
        "The waters are too swift for swimming.\n");

    add_exit((PELAR_DIR + "streets/beacon05"), "east");
    add_exit((PELAR_DIR + "streets/beacon03"), "west");
    // BATH_ENTRY->wake_up_plixxx();
} /* create_gondor */


/*
 * Function name:	init
 * Description	:	add verbs
 */
public void
init()
{
    ::init();
    add_action(enter, "open");
    add_action(enter, "close");
    add_action(enter, "lock");
    add_action(enter, "unlock");
    add_action(enter, "push");
    add_action(enter, "pull");
    add_action(enter, "north");
    add_action(enter, "enter");
    add_action(knock, "knock");
} /* init */

/*
 * Function name:	enter
 * Description	:	handle attempts to enter buildings
 * Arguments	:	string arg -- whatever the player typed
 * Returns	:	1 if we recognize the arg, 0 if not
 */
public int
enter(string arg)
{
    string	junk,
    		vb = QVB;

    if (vb != "north" &&
        (!strlen(arg) ||
         !parse_command((arg = LOW(arg)), ({}),
    		        "[on] [the] [dark] [brown] [small] [smaller] "+
		        "[north] %s 'building' / 'door'", junk)))
    {
        NF0(CAP(vb) + " what?\n");
    }

    switch(vb)
    {
	case "enter":
	case "north":
            write("The door is closed.\n");
	    SAY(" tries to walk through the wooden door.");
	    break;
	case "open":
	case "push":
	case "pull":
	    write("No doorknob is visible on this side of the door, and " +
	        "you can't seem to budge it.\n");
	    SAY(" fumbles at the door.");
	    break;
	case "close":
	    write("The door is already closed.\n");
	    SAY(" fumbles at the door.");
	    break;
	case "lock":
	case "unlock":
            write("No keyhole is visible on this side of the door.\n");
	    SAY(" fumbles at the door.");
	    break;
    }
    return 1;
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
        !parse_command(LOW(arg), ({}),
           "[on] [the] [dark] [brown] [north] [small] [smaller] "+
	   "[building] 'door'"))
    {
	NF0("Knock on what?\n");
    }
    write("You knock on the door.\n");
    SAY(" knocks on the door.");
    TP->reveal_me(1);
    BATH_ENTRY->knock_on_door(TP, TO);
    return 1;
} /* knock */
