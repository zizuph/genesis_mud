/*
 *  /d/Emerald/blackwall/delrimmon/lakeside/cliffs/tunnel1.c
 *
 *  A tunnel connects the ledge which runs along the western
 *  cliff faces to the single path which leads into the
 *  valley. Here, the tunnel meets with a doorway leading
 *  to an overlook. Vines have overgrown the doors on the
 *  outside, and so they must be cut away before the door
 *  can be opened.
 *
 *  Copyright (c) January 2001, by Cooper Sherry (Gorboth)
 */
#pragma strict_types

inherit "/d/Emerald/blackwall/delrimmon/legacy/del_rimmon_room";
inherit "/d/Emerald/blackwall/delrimmon/del_rimmon";

#include <macros.h>      /* for QCTNAME, etc */
#include <stdproperties.h>
#include "/d/Emerald/blackwall/delrimmon/defs.h"

/* definitions */
#define OTHER_SIDE    (DELRIMMON_DIR + "lakeside/west_overlook")

/* global variables */
int     Door_Closed = 1;
int     Beam = 1; /* 0 - beam gone, 1 - on wall, 2 - barring door */

/* prototypes */
public void        create_del_rimmon();
public string      describe();
public string      exa_outside();
public void        tunnel_items();
public int         check_exit();
public int         check_obvious();
public int         mess_with_door(string arg);
public void        close_doors();
public string      exa_doors();
public void        hear_knock();
public void        init();


/*
 * Function name:        create_del_rimmon
 * Descriptionn :        set up the room with area presets
 */
public void
create_del_rimmon()
{
    set_short("before a doorway at the end of a tunnel");
    set_long(del_rimmon_long);

    set_extraline(describe);

    add_item( ({ "door", "doors", "metal door", "metal doors",
                 "two doors", "doorway", "two metal doors" }),
        exa_doors);
    add_item( ({ "outside", "east", "landing", "light" }), exa_outside);
    add_item( ({ "bracket", "brackets", "metal bracket", "metal brackets",
                 "two brackets", "two metal brackets" }),
        "The brackets look as if they may have been created to house a"
      + " crossbeam to prevent the doors from swinging open. They are"
      + " empty.\n");

    tunnel_items();

    add_prop(ROOM_I_INSIDE, 1);

    add_exit(DELRIMMON_DIR + "lakeside/cliffs/tunnel2", "west");
    add_exit(DELRIMMON_DIR + "lakeside/west_overlook", "east",
             check_exit, 1, check_obvious);

    set_no_exit_msg( ({ "northwest", "north", "northeast",
                        "southwest", "south", "southeast" }),
        "The tunnel walls block your progress in that direction.\n");

    FIX_EUID
} /* create_del_rimmon */


/*
 * Function name:        describe
 * Description  :        create the long description for the room, based
 *                       on whether or not the doors are open.
 * Returns      :        string - the long description for the room
 */
public string
describe()
{
    if (!Door_Closed)
    {
        return "Light pours into this tunnel from the east, where metal"
             + " doors have been flung wide to open onto a landing of"
             + " some kind in that direction. To the west, the tunnel"
             + " travels for some distance into the rock, disappearing"
             + " from view in that direction.";
    }

    return "Just to the east, the tunnel comes to a halt before two"
         + " metal doors which are framed by the rock walls. In the"
         + " very dim light you can see that the tunnel runs a ways"
         + " to the west, trailing off into the distance.";
} /* describe */


/*
 * Function name:        exa_outside
 * Description  :        allow the player to examine the light which
 *                       is coming in from the outside, or, if the doors
 *                       are closed, give a description of them.
 * Returns      :        string - the description 
 */
public string
exa_outside()
{
    if (Door_Closed)
    {
        return "The doors to the east are closed, blocking out all"
             + " light from the outside.\n";
    }

    return "Light from the outside is pouring into this chamber from"
         + " the east, where it appears as if the tunnel opens out onto"
         + " a landing of some kind.\n";
} /* exa_outside */


/*
 * Function name:        tunnel_items
 * Description  :        add some items common to all tunnel rooms
 */
public void
tunnel_items()
{
    add_item( ({ "tunnel", "corridor", "passage", "passageway",
                 "here", "area" }),
        "This tunnel travels through the rock of the cliffs, winding"
      + " its way in a general east-west direction.\n");
    add_item( ({ "ground", "floor", "down", "tunnel floor",
                 "floor of the tunnel" }),
        "The floor of the tunnel is very smooth, though covered with"
      + " a great deal of collected dust and debris.\n");
    add_item( ({ "dust", "debris", "collected dust", "collected debris",
                 "collected dust and debris" }),
        "It would appear that this tunnel has seen very little use"
      + " over the last hundred or so years. Dust has and debris are"
      + " scattered along the floor.\n");
    add_item( ({ "wall", "walls", "rock wall", "rock walls",
                 "walls of rock", "wall of rock", "walls of stone",
                 "wall of stone", "stone walls", "stone wall",
                 "rock", "stone", "walls of the tunnel", "tunnel walls",
                 "tunnel wall", "wall of the tunnel" }),
        "The walls of the tunnel are cleanly hewn from the rock. It"
      + " is evident that great skill made them, and yet did not care"
      + " to embellish with any sense of beauty or design. This place"
      + " has a strictly functional appearance.\n");
    add_item( ({ "ceiling", "roof", "up", "tunnel roof", 
                 "roof of the tunnel" }),
        "The roof of the tunnel is much like the walls - clean hewn from"
      + " the rock of the cliffs.\n");
    add_item( ({ "cliffs", "cliff", "rock of the cliff" }),
        "This tunnel is hewn from the cliffs, whose dense rock formation"
      + " surrounds you here.\n");
} /* tunnel_items */


/*
 * Function name:        check_exit
 * Description  :        see if the door is open
 * Returns      :        int 1 - the door is shut,
 *                           0 - the door is open
 */
public int
check_exit()
{
    if (Door_Closed)
    {
        write("The doors are shut fast.\n");
        return 1;
    }

    return 0;
} /* check_exit */


/* Function name:        check_obvious
 * Description  :        see if the exit should be obvious
 * Returns      :        1 - doors are shut, so non-obvious
 *                       0 - doors are open, obvious
 */
public int
check_obvious()
{
    if (Door_Closed)
    {
        return 1;
    }

    return 0;
} /* check_obvious */


/*
 * Function name:        mess_with_door
 * Description  :        let the player try to open the door
 * Arguments    :        string arg - what the player typed
 * Returns      :        1 - success, 0 - failure
 */
public int
mess_with_door(string arg)
{
    if (!strlen(arg))
    {
        NFN0(CAP(QVB) + " what?");
    }

    if (!parse_command(arg, ({}),
        "[on] [the] [large] [stone] 'door' / 'doors'"))
    {
        return 0;  /* player typed unusable syntax */
    }

    if (QVB == "knock")
    {
        if (!Door_Closed)
        {
            write("Knock on what? The doors are open.\n");
            return 1;
        }

        write("You knock firmly on the metal doors.\n");
        tell_room(this_object(),
            QCTNAME(this_player()) + " knocks firmly on the"
          + " metal doors.\n", this_player());

        OTHER_SIDE->hear_knock();
        return 1;
    }

    if (QVB == "open" || QVB == "pull")
    {
        write("There is no handle or knob of any kind on these"
            + " doors. How do you intend to do that?\n");
        return 1;
    }

    if (OTHER_SIDE->query_overgrown())
    {
        write("You push hard on the doors, and they give a little,"
            + " yet will not swing open. It feels as if something"
            + " is blocking them from the other side, and you notice"
            + " what sounds like the rustling of leaves from beyond"
            + " the doors.\n");

        return 1;
    }

    if (!Door_Closed)
    {
        write("Push on what? The doors are already open.\n");
        return 1;
    }

    write("You push hard on the doors, and they swing open."
        + " Light from the outside pours into the tunnel.\n");
    tell_room(this_object(), QCTNAME(this_player())
        + " pushes on the doors, which swing open allowing light"
        + " from outside to pour into the tunnel.\n",
        this_player());

    Door_Closed = 0;
    OTHER_SIDE->open_doors();
    set_alarm(10.0, 0.0, close_doors);

    return 1;
} /* mess_with_door */


/*
 * Function name:        close_doors
 * Description  :        the doors swing shut of their own
 *                       accord 5 seconds after being pushed
 *                       open
 */
public void
close_doors()
{
    tell_room(this_object(), "The doors swing slowly shut,"
      + " cutting off the light from the outside.\n");
    Door_Closed = 1;
    OTHER_SIDE->close_doors();

    return;
} /* close_doors */


/*
 * Function name:        exa_doors
 * Description  :        show a description of the door, taking
 *                       several factors into account.
 * Returns      :        string - the door description
 */
public string
exa_doors()
{
    string  txt = "Two metal doors mark the end of the tunnel"
                + " here. Each is bare of any marking or device,"
                + " aside from two large metal brackets";

    if (Door_Closed)
    {
        if (Beam == 2)
        {
            txt += " where a large beam of wood has been placed"
                 + " to bar the doors. ";
        }

        txt += ". The doors are shut.\n";
        return txt;
    }

    txt += ". The doors have been pushed open, and are"
         + " slowly swinging back closed.\n";
    return txt;
} /* exa_doors */


/*
 * Function name:        hear_knock
 * Description  :        if someone on the other side knocks on the
 *                       doors, we hear it here.
 */
public void
hear_knock()
{
    tell_room(this_object(), "A faint tapping sound comes suddenly"
      + " from the other side of the doors, as if someone there were"
      + " knocking on them.\n");

    return;
} /* hear_knock */


/*
 * Function name:        init
 * Description  :        add some actions to the player
 */
public void
init()
{
    ::init();

    add_action(mess_with_door, "open");
    add_action(mess_with_door, "pull");
    add_action(mess_with_door, "shove");
    add_action(mess_with_door, "push");
    add_action(mess_with_door, "knock");
} /* init */
