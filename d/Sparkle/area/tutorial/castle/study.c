/*
 *  /d/Sparkle/area/tutorial/castle/study.c
 *
 *  The Study of Baron von Krolock.
 *
 *  Created October 2005, by Cooper Sherry (Gorboth)
 *  Updated July 24, 2016 by Gronkas - fixed a typo
 */
#pragma strict_types
#include "../defs.h"

inherit CASTLE_DIR + "castle_room";

#include <stdproperties.h>

/* Global Variables */
public int         Open = 0;   /* is the safe open? */
public int         Locked = 1; /* is the safe locked? */

/* Prototypes */
public void        create_castle_room();
public void        enter_inv(object ob, object from);
public string      describe(string arg);
public void        init();
public int         get_fragment(string arg);
public void        close_safe();
public int         mess_with_safe(string arg);

/*
 * Function name:    create_castle_room
 * Description  :    set up the room
 */
public void
create_castle_room()
{
    set_short("a dimly-lit study");
    set_long("You stand in a dimly-lit study. Here, large candle"
      + " stands have been set up around the room to cast light"
      + " enough to read by. A safe in the western wall overlooks"
      + " a wooden desk which has been placed in the corner. An"
      + " archway leads north toward a long hallway.\n\n");

    add_item( ({ "here", "area", "room", "study" }),
        long);
    add_item( ({ "archway", "arch", "north", "hall",
                 "hallway" }),
        "A long hallway is visible through an archway to the"
      + " north.\n");
    add_item( ({ "desk", "wooden desk", "corner" }),
        "A wooden desk rests in the corner of the room, just beneath"
      + " a wallsafe. Upon the desk you see various items of study,"
      + " but a particular open book catches your eye. It looks like"
      + " a handwritten diary.\n");
    add_item( ({ "stand", "stands", "large stand", "large stands",
                 "candle stand", "candle stands", "large candle stand",
                 "large candle stands" }),
        "The candle stands are tall and wrought from iron that has"
      + " been painted black. Each contains a single white candle.\n");
    add_item( ({ "candle", "white candle", "candles",
                 "white candles" }),
        "White candles have been placed around the room for light"
      + " to read by. Each is positioned within a candle stand.\n");
    add_item( ({ "diary", "handwritten diary" }),
        "The diary on the desk is written in what appears to be"
      + " blood. Perhaps you could <read> it.\n");
    add_item( ({ "safe", "wallsafe", "iron safe",
                 "iron wallsafe" }), &describe("safe"));
    add_item( ({ "fragment", "stone fragment" }), &describe("frag"));
    add_item( ({ "drawer" }), &describe("drawer"));
    add_item( ({ "keyhole", "triangle" }),
        "The keyhole in the wallsafe is rather large, and shaped"
      + " like a perfect triangle.\n");
    add_item( ({ "blood", "writing" }),
        "The writing in the diary does indeed appear to be blood."
      + " Perhaps you could <read> it.\n");

    add_cmd_item( ({ "diary", "handwritten diary", "the diary",
                     "blood", "writing" }),
                  ({ "read" }),
        "You flip through the diary and scan the various entries."
      + " They appear to have been written by Krolock himself. He"
      + " details his various efforts to defile and master the"
      + " lands of Silverdell. One interesting log describes how he"
      + " sent a group of demonic bunnies to destroy the crops of"
      + " garlic grown by Farmer Brown. Garlic, it seems, is the"
      + " only thing he fears.\n");

    add_castle_items();
    add_torch_items();

    add_prop(OBJ_S_SEARCH_FUN, "do_search");

    add_exit("hallway_6s", "north");

    reset_room();
} /* create_castle_room */


/*
 * Function name:        reset_room
 * Description  :        make sure the safe is closed
 */
public void
reset_room()
{
    Open = 0;
} /* reset_room */


/* 
 * Function name: enter_inv
 * Description:   Broadcast the Baron's voice to players who enter
 * Arguments:     ob: The object that just entered this inventory
 *                from: The object from which it came.
 */
public void
enter_inv(object ob, object from)
{
    string    txt = "";

    ::enter_inv(ob, from);

    if (!strlen(from->query_trigger_room()) ||
        !interactive(ob))
    {
        return;
    }

    set_this_player(ob);

    if (CHECK_TUTORIAL_BIT(DESTROYER_BIT))
    {
        txt = "WELCOME, FAITHFUL SERVANT.";
    }
    else
    {
        txt = one_of_list( ({
            "BEGONE, FOOL! LEAVE AT ONCE!",
            "GET OUT OF MY STUDY, OR YOU SHALL BE SKINNED ALIVE!",
            "THERE IS NOTHING HERE FOR YOU, WORM!" }) );
    }

    set_alarm(0.5, 0.0, &broadcast(txt, ob));
} /* enter_inv */


/*
 * Function name:        describe
 * Description  :        provide a status dependant descriptions
 * Arguments    :        string arg - what are we describing?
 * Returns      :        string - various descriptions of things
 */
public string
describe(string arg)
{
    switch(arg)
    {
        case "frag":
            if (present("_tutorial_fragment", this_player()) || !Open ||
                CHECK_TUTORIAL_BIT(STATUE_BIT))
            {
                return "You find no fragment.\n";
            }

            return "You see a stone fragment inside the safe.\n";
            break;
        case "safe":
            if (!Open)
            {
                return "An iron safe has been built into the western"
                  + " wall. It is closed.\n";
            }

            if (!present("_tutorial_fragment", this_player()) &&
                !CHECK_TUTORIAL_BIT(STATUE_BIT))
            {
                return "An iron safe has been built into the western"
                  + " wall. It is open, and inside you see a stone"
                  + " fragment of some kind.\n";
            }

            Open = 0;
            Locked = 1;
            return "An iron safe has been built into the western"
              + " wall. You don't see anything important inside it,"
              + " so you close it once again. It clicks locked.\n";
            break;
    } /* switch(arg) */
} /* describe */


/*
 * Function name:        init
 * Description  :        add some actions to the player
 */
public void
init()
{
    ::init();

    add_action(get_fragment, "get");
    add_action(get_fragment, "take");
    add_action(get_fragment, "remove");
    add_action(get_fragment, "pick");
    add_action(mess_with_safe, "open");
    add_action(mess_with_safe, "pull");
    add_action(mess_with_safe, "push");
    add_action(mess_with_safe, "close");
    add_action(mess_with_safe, "lock");
    add_action(mess_with_safe, "unlock");
} /* init */



/*
 * Function name:        get_fragment
 * Description  :        allow players to take the fragment from the
 *                       safe.
 * Arguments    :        string arg - what the player typed after the
 *                                    verb.
 * Returns      :        int 1 - success, 0 - otherwise
 */
public int
get_fragment(string arg)
{
    object  fragment;

    if (!strlen(arg))
    {
        return 0; /* let the mudlib handle it */
    }

    if (!Open)
    {
        notify_fail("Get what?\n");
        return 0;
    }

    if (!parse_command(arg, ({}),
        "[the] [a] [white] [stone] 'fragment' / 'all' 'from' [the]"
      + " [iron] 'safe' / 'wallsafe'"))
    {
        if (parse_command(arg, ({}),
            "[a] [the] [white] [stone] 'fragment'"))
        {
            write("The fragment is inside the safe.\n");
            return 1;
        }

        if (parse_command(arg, ({}),
            "[a] [the] 'fragment' 'in' [the] [iron] 'safe'"
          + " / 'wallsafe'"))
        {
            write("Use syntax: <get [item] from [place]>\n");
            return 1;
        }

        return 0; /* give it to the mudlib */
    }

    if (present("_tutorial_fragment", this_player()) ||
        CHECK_TUTORIAL_BIT(STATUE_BIT))
    {
        write("You have already taken it.\n");
        return 1;
    }

    fragment = clone_object(OBJ_DIR + "fragment");
    fragment->configure_fragment(this_player());
    fragment->move(this_player(), 1);
    write("You take the stone fragment from the safe, shutting the"
      + " safe afterwards. It clicks locked.\n");
    Open = 0;
    Locked = 1;

    set_alarm(1.0, 0.0, &write("A voice booms: I WILL KILL YOU MYSELF,"
      + " THIEF!\n"));

    return 1;
} /* get_key */


/*
 * Function name:        close_safe
 * Description  :        close the safe after 20 seconds if it is not
 *                       already closed.
 */
public void
close_safe()
{
    if (Open)
    {
        tell_room(this_object(), "The wallsafe swings suddenly shut,"
          + " and you hear a click as it locks itself.\n");
        Open = 0;
        Locked = 1;
    }

    return;
} /* close_safe */


/*
 * Function name:        mess_with_safe
 * Description  :        let the player open and close the safe
 * Arguments    :        string arg - what was typed after the verb
 * Returns      :        int 1 - success, 0 - otherwise
 */
public int
mess_with_safe(string arg)
{
    if (!strlen(arg))
    {
        notify_fail(capitalize(query_verb()) + " what?\n");
        return 0;
    }

    if (!parse_command(arg, ({}),
        "[the] [iron] 'safe' / 'wallsafe' [with] [the]"
      + " [large] [key]"))
    {
        return 0; /* bad syntax */
    }

    switch(query_verb())
    {
        case "open":
        case "pull":
            if (Open)
            {
                write("The safe is already open.\n");
                return 1;
            }

            if (Locked)
            {
                write("The safe is locked.\n");
                return 1;
            }

            write("You pull the safe open.\n");
            Open = 1;
            set_alarm(60.0, 0.0, close_safe);
            return 1;
            break;
        case "push":
        case "close":
            if (Open)
            {
                write("You push the safe closed. You hear a click as"
                  + " it locks.\n");
                Open = 0;
                Locked = 1;
                return 1;
            }

            write("The safe is already closed.\n");
            return 1;
        case "lock":
            if (Locked)
            {
                write("The safe is already locked.\n");
                return 1;
            }

            if (present("_tutorial_castle_key", this_player()))
            {
                write("You lock the safe, using the large key.\n");
                Locked = 1;
                return 1;
            }

            write("You don't seem to have the key.\n");
            return 1;
            break;
        case "unlock":
            if (!Locked)
            {
                write("The safe is already unlocked.\n");
                return 1;
            }

            if (present("_tutorial_castle_key", this_player()))
            {
                write("You unlock the safe, using the large key.\n");
                Locked = 0;
                return 1;
            }

            write("You don't seem to have the key.\n");
            return 1;
            break;
    } /* switch(query_verb()) */

    return 0; /* shouldn't ever happen. */
} /* mess_with_drawer */


/*
 * Function name:        do_search
 * Description  :        allow the player to search things in the room
 * Arguments    :        object pl  - the player object,
 *                       string arg - what the player tried to search
 * Returns      :        int 1 - success, 0 - failure
 */
public string
do_search(object pl, string arg)
{
    if (!strlen(arg) || (member_array(arg,
        ({ "desk", "wooden desk", "safe", "wallsafe" }) ) == -1))
    {
        return "Your search reveals nothing special.\n";
    }

    switch(arg)
    {
        case "desk":
        case "wooden desk":
            return "You search the desk thoroughly, but don't find"
              + " anything more interesting than a diary which is"
              + " open for you to read.\n";
            break;
        case "safe":
        case "wallsafe":
            if (!Open)
            {
                return "You search the wallsafe, and notice that"
                  + " it contains a keyhole that is shaped like a"
                  + " triangle.\n";
            }

            if (!present("_tutorial_fragment", this_player()) ||
                !CHECK_TUTORIAL_BIT(STATUE_BIT))
            {
                return "You notice nothing special about the safe,"
                  + " but it does contain a stone fragment.\n";
            }

            return "You notice nothing special about the safe. It"
              + " is empty.\n";
            break;
        default:
            return "You search around the area, but don't find anything"
              + " of interest.\n";
    }

    return "Your search does not reveal anything at all.\n";
} /* do_search */
