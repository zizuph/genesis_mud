/*
 *  /d/Emerald/blackwall/delrimmon/lakeside/west_outlook.c
 *
 *  The entrance to the Valley of Del Rimmon was fortified
 *  so that none could pass through without leave. Here,
 *  an overlook is placed above the western base of the
 *  path leading to the lake. A doorway leads to some
 *  tunnels which connect this overlook with the ledge
 *  above the cliffs, but it can only be opened from
 *  the other side. Over the centuries, leafy vines have
 *  overgrown this entire structure.
 *
 *  Copyright (c) January 2001, by Cooper Sherry (Gorboth)
 */
#pragma strict_types

inherit "/d/Emerald/blackwall/delrimmon/lakeside/cliffs/ledge_master";
inherit "/d/Emerald/blackwall/delrimmon/del_rimmon";

#include <macros.h>      /* for QCTNAME, etc */
#include <stdproperties.h>
#include "/d/Emerald/blackwall/delrimmon/defs.h"

/* definitions */
#define OTHER_SIDE    (DELRIMMON_DIR + "lakeside/cliffs/tunnel1")

/* global variables */
int     Door_Closed = 1;  /* true if the door is closed */
int     Overgrown   = 1;  /* true if the vines block the door */

/* prototypes */
public void        create_del_rimmon();
public string      exa_tunnel();
public int         climb_stairs(string arg);
public int         get_rock(string arg);
public string      search_vines();
public string      exa_metal();
public string      exa_vines();
public int         check_exit();
public int         check_obvious();
public string      exa_doors();
public int         mess_with_things(string arg);
public void        init();
public void        reset_room();
public void        remove_vines();
public void        hear_knock();

public int         query_overgrown() { return Overgrown; }


/*
 * Function name:       create_del_rimmon
 * Description :        set up the room with area presets
 */
public void
create_del_rimmon()
{
    set_cliff_base(DELRIMMON_DIR + "lakeside/pathway2");
    set_short("on a landing, overlooking a path below");
    set_long(del_rimmon_long);

    set_extraline("Hugging the western walls of rock, a wide landing"
      + " serves as an overlook to a pathway far below. At one time,"
      + " it appears as if this was some kind of fortification by"
      + " which a watch was placed on the pass."
      + " A wall runs along the edge of the landing,"
      + " broken only by a small opening which joins a stairway"
      + " leading down to the pathway. Great tangled vines"
      + " have grown to cover much of the stonework here, especially"
      + " to the west, where the thick foliage completely obscures the"
      + " walls of rock.");

    add_item( ({ "tunnel" }), exa_tunnel);
    add_item( ({ "vine", "vines", "leaf", "leaves", "leafy vine",
                 "leafy vines", "foliage", "thick foliage",
                 "leafy foliage", "tangled vine", "tangled vines",
                 "great tangled vines" }), exa_vines);
    add_item( ({ "opening", "opening in the wall" }),
        "At the northern end of the wall, an opening leads on to a"
      + " stairway that descends below the ledge.\n");
    add_item( ({ "pass" }),
        "The pathway below this ledge appears to be the only way in"
      + " or out of the valley to the north.\n");
    add_item( ({ "valley", "valley to the north" }),
        "To the north, a valley stretches out, cradling the lake of"
      + " Del Rimmon in its deeps.\n");
    add_item( ({ "wall of rock", "walls of rock", "western wall",
                 "western wall of rock", "ridge", "great ridge",
                 "ridge of rock", "great ridge of rock" }),
        "Rising high above to the west, walls of rock form a great"
      + " ridge which travels a great distance to the west, turning"
      + " eventually northward to ring the lake of Del Rimmon. Here it"
      + " has been much overgrown by leafy vines which completely"
      + " obscure its surface and much of the landing.\n");
    add_item( ({ "ledge", "landing", "wide landing", "wide ledge",
                 "overlook", "fortification", "here", "area" }),
        "This ledge forms an overlook to the pathway below. It extends"
      + " out from the western wall of rock perhaps five meters before"
      + " stopping abruptly at the foot of a stone wall which runs"
      + " the length of its eastern edge. Much of the stone here is"
      + " overgrown by vines which have swallowed the surface of the"
      + " western wall as well.\n");
    add_item( ({ "edge", "eastern edge", "wall", "stone wall",
                 "wall of stone" }),
        "The wall of stone spans the eastern edge of this landing,"
      + " serving as both a railing and most likely at one time as"
      + " a defensive position. Arrow slots are visible at regular"
      + " intervals in its surface, and a massive pile of stones rests"
      + " in the southernmost corner along its length. An opening at"
      + " its northern end joins with a stairway leading downward.\n");
    add_item( ({ "stair", "stairs", "steps", "stairway", "stone stair",
                 "stone stairs", "stone steps", "stone stairway" }),
        "A stone stairway leads from an opening at the northern end"
      + " of the wall to the pathway far below this landing.\n");
    add_item( ({ "slot", "slots", "narrow slot", "narrow slots",
                 "arrow slot", "arrow slots" }),
        "Narrow slots are visible along the stone wall at regular"
      + " intervals. They run vertically from the base of the wall,"
      + " appearing to allow an archer to adjust his aim up or down.\n");
    add_item( ({ "pile", "massive pile", "stone", "stones", "stone pile",
                 "pile of stones", "massive pile of stones" }),
        "This pile of stones does not look like any natural phenomenon,"
      + " but rather more like a deliberate collection of ammunition to"
      + " be used in the defense of the pass.\n");
    add_item( ({ "stone", "stonework" }),
        "The stonework of this landing is not crude, and yet looks to"
      + " have been performed with haste, as if artistry was of far"
      + " less concern than utility. There is a military feel about"
      + " the place. Much of the stone is covered with thick leafy"
      + " vines which almost completely obscure the wall of rock"
      + " to the west.\n");
    add_item( ({ "metal" }),
        exa_metal);
    add_item( ({ "door", "doors", "metal door", "metal doors" }),
        exa_doors);
    add_item( ({ "path", "pathway" }),
        &exa_cliff_base("The pathway rests at the base of the walls of"
          + " rock upon which this overlook stands, running north and"
          + " south through a narrow corridor which forms the pass to"
          + " the lake of Del Rimmon. "));

    add_cmd_item( ({ "vine", "vines", "leafy vines", "leafy vine",
                     "leaves", "foliage", "leafy foliage" }),
                  ({ "search" }),
        search_vines);
    add_cmd_item( ({ "pile", "massive pile", "pile of stones",
                     "ammunition" }),
                  ({ "search", "dig" }),
        "You dig around in the ammunition, but don't find much of"
      + " anything out of the ordinary. You could probably take stones"
      + " from the pile if you wished.\n");

    add_exit(DELRIMMON_DIR + "lakeside/w_stairway", "down");
    add_exit(DELRIMMON_DIR + "lakeside/cliffs/tunnel1", "west",
             check_exit, 1, check_obvious);

    set_no_exit_msg( ({ "northwest", "southwest" }),
        "You are halted by the western walls of rock in that"
      + " direction.\n");
    set_no_exit_msg( ({ "north", "northeast", "east", "southeast",
                        "south" }),
        "The stone wall which runs along the edge of the landing"
      + " prevents movement in that direction.\n");
    reset_room();

    FIX_EUID

    add_lakeview();
} /* create_del_rimmon */


/*
 * Function name:        exa_tunnel
 * Description  :        allow the player to look at the tunnel if the
 *                       doors are open
 * Returns      :        string - the description
 */
public string
exa_tunnel()
{
    if (Door_Closed)
    {
        return "You find no tunnel.\n";
    }

    return "Beyond the open doors to the west, a tunnel leads deep"
         + " inside the walls of rock.\n";
} /* exa_tunnel */


/*
 * Function name:        climb_stairs
 * Description  :        allows the player to climb down the stairs
 * Arguments    :        string arg - what the player typed
 * Returns      :        int 1 - success, 0 - failure
 */
public int
climb_stairs(string arg)
{
    if (!strlen(arg))
    {
        NFN0("Climb what?");
    }

    if (!parse_command(arg, ({}),
        "[down] [the] [stone] 'stair' / 'stairs' / 'stairway' / 'steps'"))
    {
        return 0; /* unacceptable syntax */
    }

    write("You climb down the stone steps, and make your way to the"
        + " pathway below.\n");

    if (this_player()->query_wiz_level())
    {
        write("Normally, we move the player 'down' here using 'command'."
          + " Since you are a wizard, that won't work, so you'll need"
          + " to move 'down' manually.\n");

        return 1;
    }

    this_player()->command("$down");
    return 1;
} /* climb_stairs */


/*
 * function name:        get_rock
 * description  :        allow the player to try to get a stone
 *                       from the pile
 * arguments    :        string arg -- what the player typed
 * returns      :        1 -- success, 0 -- failure
 */
public int
get_rock(string arg)
{
    object  rock;

    if (!strlen(arg))
    {
        return 0;
    }

    if (!parse_command(arg, ({}),
        "[a] [the] 'stone' / 'stones' / 'rock' / 'rocks' / 'ammunition'"
      + " [from] [the] [massive] [pile] [of] [stones]"))
    {
        return 0; /* bad syntax, so we pass it to the mudlib */
    }

    rock = clone_object(DELRIMMON_DIR + "legacy/random_rock");

    write("You take a " + rock->short() + " from the pile.\n");
    say(QCTNAME(TP) + " picks up a " + rock->short() + " from the"
      + " pile.\n");

    if (rock->move(TP))  /* too heavy for the player */
    {
        WRITE("Oops! You dropped it!");
        say(QCTNAME(TP) + " fumbles and drops what "
          + TP->query_pronoun() + " had taken.\n");

        rock->move(TO, 1);
    }

    return 1;
} /* get_rock */


/*
 * Function name:        search_vines
 * Description  :        allow the players to search the vines and
 *                       discover something behind them.
 * Returns      :        string - what the player sees
 */
public string
search_vines()
{
    if (Overgrown)
    {
        return "Searching through the vines along the wall, your hand"
             + " comes in contact with cold metal behind them. You"
             + " attempt to get a look at what is there, but the vines"
             + " are too thick, and in the way.\n";
    }

    return "You search through the vines, but there does not appear"
         + " to be anything that they have hidden except for the"
         + " doors which are now in plain view.\n";
} /* search_vines */


/*
 * Function name:        exa_metal
 * Description  :        we only see this if the vines have been
 *                       removed
 * Returns      :        string - the description
 */
public string
exa_metal()
{
    if (Overgrown)
    {
        return "You find no metal.\n";
    }

    return "The metal of the doors is heavily weathered and has been"
         + " soiled by many years beneath the vines. It is very plain"
         + " and unadorned save for an emblem at the center of the"
         + " doors.\n";
} /* exa_metal */


/*
 * Function name:        exa_vines
 * Description  :        provide a description of the foliage which
 *                       covers the northern wall, it may or may
 *                       not have been removed.
 * Returns      :        string - the description
 */
public string
exa_vines()
{
    string txt = "Thick and tangled vines have grown to cover almost"
               + " the entire wall of rock to the west of here. The"
               + " leafy foliage extends high above, and also along"
               + " much of the stonework of the landing. ";

    if (Overgrown)
    {
        return txt + "\n";
    }

    return txt + " A portion of the vines have been torn or cut away"
               + " along the wall to the west, revealing metal doors"
               + " which have been set in the rock.\n";
} /* exa_vines */


/*
 * Function name:        check_exit
 * Description  :        see if the door is open
 * Returns      :        int 1 - the door is shut,
 *                           0 - the door is open
 */
public int
check_exit()
{
    if (this_player()->query_prop(FLUX_PROP))
    {
        write("You pass through the vine covered wall.\n");
        return 0;
        /* yes, I suppose some players will try this, so we might as
         * well provide the support.
         */
    }

    if (Overgrown)
    {
        write("A vine-covered wall of rock blocks your"
            + " movement in that direction.\n");
        return 1;
    }

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
    if (Door_Closed || Overgrown)
    {
        return 1;
    }

    return 0;
} /* check_obvious */


/*
 * Function name:        exa_doors
 * Description  :        provide a description for the door add_item.
 *                       this will vary depending on whether the doors
 *                       are open, or covered with vines.
 * Returns      :        string - the description
 */
public string
exa_doors()
{
    string     txt;

    if (Overgrown)
    {
        return "You find no doors.\n";
    }

    txt = "Two metal doors are set in the wall of rock to the west,"
        + " where it appears as if vines have been stripped away"
        + " to reveal the overgrown entrance. They are bare of"
        + " any mark or device except for an emblem at their center. ";

    if (!Door_Closed)
    {
        txt += "The doors have been flung open, revealing a passageway"
             + " leading west.";
    }

    else
    {
        txt += "The doors are closed.";
    }

    return txt + "\n";
} /* exa_doors */


/*
 * Function name:        mess_with_things
 * Description  :        let the player try to open the door
 * Arguments    :        string arg - what the player typed
 * Returns      :        1 - success, 0 - failure
 */
public int
mess_with_things(string arg)
{
    if (!strlen(arg))
    {
        NFN0(CAP(QVB) + " what?");
    }

    if (!parse_command(arg, ({}),
        "[open] [on] [the] [large] [stone] 'door' / 'doors' [open]"))
    {
        if (parse_command(arg, ({}),
        "[on] [the] [leafy] 'vine' / 'vines' / 'foliage'"))
        {
            if (QVB == "pull" ||
                QVB == "move" ||
                QVB == "remove")
            {
                if (!Overgrown)
                {
                    write("The vines have already been torn"
                        + " away from the doors.\n");
                    return 1;
                }

                write("Pulling with all of your might, you slowly"
                    + " toil to remove the vines which obscure a part"
                    + " of the western wall of rock. After a hard"
                    + " workout, you stand back, gazing at metal doors"
                    + " which are set in the rock, and had been hidden"
                    + " from view until now.\n");
                tell_room(this_object(),
                  QCTNAME(this_player()) + " gets to work removing"
                  + " the vines from the western wall of rock. After"
                  + " a few minutes of toil, metal doors emerge from"
                  + " beneath the thick foliage, set in the rock.\n",
                  this_player());
                remove_vines();
                return 1;
            }

            return 0; /* bad syntax */
        }

        return 0;  /* player typed unusable syntax */
    }

    if (Overgrown)
    {
        return 0;
    }

    if (QVB == "pry")
    {
        if (!Door_Closed)
        {
            write("But the doors are already wide open!\n");
            return 1;
        }

        write("These doors do not offer any opportunity for you"
          + " to pry them open. They are set too firmly together.\n");
        return 1;
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

    if (QVB == "push" || QVB == "shove")
    {
        write("You push hard on the doors, but they do not"
          + " budge.\n");
        return 1;
    }

    return 0;
} /* mess_with_things */


/*
 * Function name:        open_doors
 * Description  :        open the doors, and tell the room what is
 *                       happening
 */
public void
open_doors()
{
    tell_room(this_object(), "The doors suddenly swing outward,"
       + " revealing a tunnel leading into the cliff.\n");
    Door_Closed = 0;
} /* open_doors */


/*
 * Function name:        close_doors
 * Description  :        close the doors, and tell the room what
 *                       is happening
 */
public void
close_doors()
{
    tell_room(this_object(), "The doors swing slowly closed.\n");
    Door_Closed = 1;
} /* close_doors */


/*
 * Function name:        init
 * Description  :        add some actions to the player
 */
public void
init()
{
    ::init();

    add_action(climb_stairs, "climb");
    add_action(get_rock, "get");
    add_action(get_rock, "take");
    add_action(mess_with_things, "open");
    add_action(mess_with_things, "pull");
    add_action(mess_with_things, "shove");
    add_action(mess_with_things, "push");
    add_action(mess_with_things, "move");
    add_action(mess_with_things, "remove");
    add_action(mess_with_things, "knock");
    add_action(mess_with_things, "pry");
} /* init */


/*
 * function name:    reset_room
 * description  :    clone and set up the emblem
 */
public void
reset_room()
{
    object  emblem;

    if (!present("kot_emblem"))
    {
        emblem = clone_object(DELRIMMON_DIR + "obj/normal_emblem");
        emblem->set_emblem("You find no emblem.");
        emblem->move(this_object());
    }

    if (random(4))
    {
        Overgrown = 1;
    }
} /* reset_room */


/*
 * Function name:        remove_vines
 * Description  :        remove the vines, and bring the 
 *                       emblem into view
 */
public void
remove_vines()
{
    object  emblem = present("kot_emblem");

    Overgrown = 0;
    emblem->set_emblem("The doors bear the symbol of Telberin - "
      + "a four-pointed star set within a circular band.");
} /* remove_vines */


/*
 * Function name:        hear_knock
 * Description  :        if someone on the other side knocks on the
 *                       doors, we hear it here.
 */
public void
hear_knock()
{
    if (Overgrown)
    {
        tell_room(this_object(), "A faint tapping sound comes"
          + " suddenly from the vines which cover the rock walls"
          + " to the west.\n");

        return;
    }

    tell_room(this_object(), "A faint tapping sound comes suddenly"
      + " from the other side of the doors, as if someone there were"
      + " knocking on them.\n");

    return;
} /* hear_knock */
