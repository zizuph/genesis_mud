/*
 *  /d/Emerald/blackwall/del_rimmon/obj/normal_emblem.c
 *
 *  This is the standard Insignia of Telberin and the Knights
 *  of Telan-Ri. The Keepers of Telberin have this emblem
 *  throughout the city, and therefore it was carved in various
 *  locations at their outpost at Del Rimmon. Players can try
 *  to mess with the various elements.
 *
 *  Copyright (c) November 2001, by Cooper Sherry (Gorboth)
 */
#pragma strict_types

inherit "/std/object";
#include <macros.h>
#include <stdproperties.h>
#include "/d/Emerald/blackwall/delrimmon/defs.h"


/* Global Variables */
public mixed   Emblem_Desc = 0;
public int     Stained = 0;
public int     Too_High = 0;


/* Prototypes */
public void        create_object();
public string      print_emblem();
public int         do_stuff(string arg);
public void        init();

public void    set_emblem(string s) { Emblem_Desc = s; }
public void    set_stained(int i = 1) { Stained = i; }
public void    set_too_high(int i = 1) { Too_High = i; }


/*
 * Function name:        create_object
 * Description  :        set up the object
 */
public void
create_object()
{
    set_name("emblem");
    add_name( ({ "symbol", "symbol of telberin", "standard",
                 "standard of telberin", "emblem",
                 "emblem of telberin", "kot_emblem" }) );
    add_adj( ({ "large" }) );

    set_short("emblem");
    set_long(print_emblem);

    add_item( ({ "emblem of telberin", "standard of telberin",
                 "symbol of telberin" }), print_emblem);
    add_item( ({ "star", "four-pointed star", "four pointed star",
                 "stars" }),
        "The emblem bears a four-pointed star, the traditional symbol"
      + " of the Order of Telan-Ri from the city of Telberin.\n");
    add_item( ({ "band", "circle", "circular band" }), 
        "The circular band surrounds the four-pointed star, to complete"
      + " the traditional emblem of Telberin.\n");

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
    string txt;

    if (Emblem_Desc)
    {
        if (Emblem_Desc == "You find no emblem.")
        {
            return Emblem_Desc + "\n";
        }

        txt = Emblem_Desc;
    }
    else
    {
        txt = "The doorway bears the symbol of Telberin - a four-pointed"
            + " star within a circular band.";
    }

    if (Stained)
    {
        txt +=
            "\n\n\n"
          + "\n"
          + "\n"
          + "                   ...\n"
          + "               .         .\n"
          + "             .      |      .\n"
          + "            .       |       .\n"
          + "           .       /|\\       .\n"
          + "           .  ----<-+->----  .\n"
          + "           .   * * \\|/       .\n"
          + "            . * *  *|       .\n"
          + "           * ***  * |      .\n"
          + "           ******        .\n"
          + "             ***   ...\n"
          + "\n\n\n\n";

        return txt;
    }

    txt +=
        "\n\n\n"
      + "\n"
      + "\n"
      + "                   ...\n"
      + "               .         .\n"
      + "             .      |      .\n"
      + "            .       |       .\n"
      + "           .       /|\\       .\n"
      + "           .  ----<-+->----  .\n"
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

    if (Too_High)
    {
        if (query_verb() == "touch")
        {
            write("The emblem has been carved into the wall high above"
                + " your head, and is quite out of reach.\n");
            return 1;
        }

        NFN0("The emblem has been carved into the wall high above"
           + " your head, and is quite out of reach.");
    }

    if (QVB == "pull")
    {
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
    add_action(do_stuff, "touch");
} /* init */
