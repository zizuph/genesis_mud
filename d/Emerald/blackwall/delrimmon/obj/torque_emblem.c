/*
 *  /d/Emerald/blackwall/del_rimmon/obj/normal_emblem.c
 *
 *  This is the standard Insignia of Telberin and the Knights
 *  of Telan-Ri. The Keepers of Telberin have this emblem
 *  throughout the city, and therefore it was carved in various
 *  locations at their outpost at Del Rimmon. This particular
 *  emblem is the register for the Crystal Torque.
 *
 *  Copyright (c) August 2001, by Cooper Sherry (Gorboth)
 */
#pragma strict_types

inherit "/std/object";
#include <macros.h>
#include <stdproperties.h>
#include "/d/Emerald/blackwall/delrimmon/defs.h"


/* Prototypes */
public void        create_object();
public string      print_emblem();
public int         do_stuff(string arg);
public void        init();


/*
 * Function name:        create_object
 * Description  :        set up the object
 */
public void
create_object()
{
    set_name("emblem");
    add_name( ({ "symbol", "symbol of telberin", "standard",
                 "standard of telberin", "emblem", "mosaic",
                 "emblem of telberin", "kot_emblem",
                 "torque_quest_emblem" }) );
    add_adj( ({ "large" }) );

    set_short("emblem");
    set_long(print_emblem);

    add_item( ({ "emblem of telberin", "standard of telberin",
                 "symbol of telberin" }), print_emblem);
    add_prop(OBJ_M_NO_GET, "The emblem cannot be taken.\n");
    set_no_show_composite(1);   /* We don't want it listed in the room */
} /* create_object */


/*
 * Function name:        print_emblem
 * Description  :        show what the emblem currently looks like
 */
public string
print_emblem()
{
    string txt = "The north wall bears the symbol of Telberin - a four-"
               + "pointed star within a circular band. Unlike other"
               + " emblems you have seen, this one is fashioned as"
               + " a mosaic of beautiful gemstones.\n";


    txt +=
        "\n\n\n"
      + "\n"
      + "\n"
      + "                   ...\n"
      + "               .         .\n"
      + "             .      |      .\n"
      + "            .       |       .\n"
      + "           .       /|\\       .\n"
      + "           .  ----<-O->----  .\n"
      + "           .       \\|/       .\n"
      + "            .       |       .\n"
      + "             .      |      .\n"
      + "               .         .\n"
      + "                   ...\n"
      + "\n\n\n\n";


    return txt;
} /* print_emblem */


/*
 * function name:        do_stuff
 * description  :        handle attempts to push/press/pull/turn emblem
 * arguments    :        string arg -- whatever the player typed
 * returns      :        1 on success, 0 on failure
 */
public int
do_stuff(string arg)
{
    string *names = ({
        "mosaic",
        "socket",
        "gem",
        "gems",
        "gemstone",
        "gemstones",
        "emblem",
        "band",
        "circle",
        "circular band",
        "four pointed star",
        "four-pointed star",
        "symbol",
        "standard",
        "star",
        "stars",
        "wall",
        "door",
        "portal",
                    }); /* we want to be syntax friendly */

    if (!strlen(arg))
    {
        notify_fail(CAP(QVB) + " what?\n");
        return 0;
    }
    arg = LOW(arg);

    if (!parse_command(arg, ({}),
        "[the] %p", names))
    {
        return 0;      /* bad arg */
    }

    if (!CAN_SEE_IN_ROOM(TP))
    {
        NFN0("You cannot see well enough to try that.");
    }

    if (QVB == "pull")
    {
        if (names[0] == "gems" || names[0] == "gemstones")
        {
            WRITE("You attempt to pull the "+names[0]+" but they do"
                + " not yield to any obvious finger holds.");
            return 1;
        }

        WRITE("You attempt to pull the "+names[0]+", but it does not"
            + " yield any obvious finger holds.");
        return 1;
    }

    if (QVB == "turn")
    {
        WRITE("There does not seem to be any way to turn the "
            + names[0] + ".");
        return 1;
    }

    if (QVB == "push" || QVB == "press")
    {
        if (names[0] == "gems" || names[0] == "gemstones")
        {
            WRITE("You push hard on the "+names[0]+", but they"
                + " do not budge.");
            return 1;
        }

        write("You push hard on the " + names[0] + ", but it"
          + " does not budge.\n");
        return 1;
    }

    return 0; /* shouldn't ever happen */
} /* do_stuff */


/*
 * Function name:        init
 * Description  :        add some actions to the player
 */
public void
init()
{
    ::init();

    add_action(do_stuff, "push");
    add_action(do_stuff, "pull");
    add_action(do_stuff, "turn");
    add_action(do_stuff, "press");
} /* init */
