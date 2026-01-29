/*
 *  /d/Sparkle/area/tutorial/review/6.c
 *
 *  These rooms are part of the original character creation tutorial,
 *  which has since been replaced. It is left in the library in Greenhollow
 *  as a quest of sorts to provide players with review and practice of
 *  basic concepts.
 *
 *  Created August 2004, by Cooper Sherry (Gorboth)
 */
#pragma strict_types
#include "../defs.h"

inherit "/std/room";
inherit REVIEW_DIR + "skip";
inherit LIB_DIR + "lib_sign";

/* definitions */
#define  TUTORIAL_CHAPTER    6  /* the chapter for the sign */

#include <stdproperties.h>


/* prototypes */
public void        create_room();
public string      exa_gate();
public void        reset_room();
public int         check_exit();
public int         hint(string arg);
public string      do_search(object pl, string arg);
public int         do_open(string arg);
public void        init();
public int         pull_torch(string arg);
public void        open_gate(object player);


/*
 * Function name:        create_room
 * Description  :        set up the room
 */
public void
create_room()
{
    set_name("6");
    set_short("a room with stone walls and passages leading north"
      + " and south");
    set_long("This room is surrounded by stone walls on all sides."
      + " A passageway leads through the south wall. To the north,"
      + " a strong iron gate is set before a long hallway which"
      + " travels on in that direction. A heavy carpet covers the floor"
      + " here, and a single torch along the west wall lights the"
      + " room. A tapestry adorns the eastern wall.\n\n");

    add_item( ({ "door" }),
        "The door is just barely visible at the far end of the"
      + " passageway which leads through the south wall.\n");
    add_item( ({ "mechanism", "hidden mechanism" }),
        "The torch is connected to a hidden mechanism of some kind."
      + " You might be able to trigger the mechanism if you were to"
      + " <pull> the torch.\n");
    add_item( ({ "room", "area", "here" }), long);
    add_item( ({ "wall", "walls", "stone wall", "stone walls" }),
        "The walls are made of stone in this room. You notice"
      + " something hanging on the east wall.\n");
    add_item( ({ "north wall", "north", "northern wall",
                 "gate", "iron gate", "strong gate", "strong iron gate" }),
        exa_gate);
    add_item( ({ "hallway", "hall", "long hall", "long hallway" }),
        "The hallway lies beyond the gate in the northern wall.\n");
    add_item( ({ "up", "roof", "ceiling", "vaulted ceiling" }),
        "The ceiling is high above the floor, and slightly vaulted.\n");
    add_item( ({ "west wall", "west", "western wall",
                 "torch", "single torch", "burning torch" }),
        "A burning torch is fixed to the western wall. It spreads a"
      + " flickering light throughout the room.\n");
    add_item( ({ "light", "flickering light", "flame", "fire" }),
        "The flame on the burning torch illuminates the area.\n");
    add_item( ({ "carpet", "heavy carpet", "floor", "ground",
                 "rug", "heavy rug", "stone" }),
        "A heavy carpet is spread out across the floor, covering the"
      + " stone that otherwise would make up the ground.\n");
    add_item( ({ "south", "southern wall", "south wall",
                 "passage", "passageway" }),
        "A passageway leads back to the previous room of the tutorial"
      + " through the southern wall.\n");
    add_item( ({ "east", "east wall", "eastern wall",
                 "something", "something hanging" }),
        "A large tapestry is hanging on the east wall.\n");
    add_item( ({ "tapestry", "large tapestry" }),
        "The tapestry is woven of expensive looking threads which"
      + " have been expertly placed to create a stunning image.\n");
    add_item( ({ "image", "stunning image", "thread", "threads",
                 "expensive looking threads" }),
        "The tapestry depicts a very fat man peering greedily into"
      + " an oven filled with doughnuts.\n");
    add_item( ({ "fatty", "fat man", "man", "very fat man" }),
        "The man looks as if he is about to steal the doughnuts.\n");
    add_item( ({ "doughnut", "doughnuts" }),
        "The doughnuts in the oven look almost real enough to eat.\n");
    add_item( ({ "oven", "oven filled with doughnuts" }),
        "The oven is open, and filled with doughnuts, though it looks"
      + " as if the fat man will soon change that.\n");

    add_cmd_item( ({ "door" }),
                  ({ "close", "open", "unlock", "lock", "search" }),
        "The door is quite a ways to the south at the far end of the"
      + " passageway. You can't reach it from here.\n");
    add_cmd_item( ({ "torch", "single torch", "burning torch" }),
                  ({ "get", "take", "remove" }),
        "The torch appears to be stuck firmly in place. Or ... hmmm ..."
      + " maybe there is more than meets the eye here.\n");
    add_cmd_item( ({ "torch", "single torch", "burning torch" }),
                  ({ "douse", "extinguish" }),
        "The flame is magical and cannot be extinguished.\n");

    add_prop(ROOM_I_INSIDE, 1);
    add_prop("_room_i_tutorial", 1);
    add_prop(OBJ_S_SEARCH_FUN, "do_search");
    add_prop(ROOM_S_MAP_FILE, "tutorial_map.txt");

    add_exit("7", "north", check_exit, 1, 0);
    add_exit("5", "south");

    reset_room();
} /* create_room */


/*
 * Function name:        exa_gate
 * Description  :        give a description with the changing state
 *                       of the gate involved
 * Returns      :        string - the description
 */
public string
exa_gate()
{
    string  gate;

    if (this_player()->query_prop(OPENED_GATE_PROP))
    {
        gate = "open";
    }
    else
    {
        gate = "closed";
    }

    return "A strong iron gate is set in the north wall, controlling"
      + " access to a long hallway beyond. The gate is "
      + gate + ".\n";
} /* exa_gate */


/*
 * Function name:       reset_room
 * Description  :       restore signs and npcs as needed
 */
public void
reset_room()
{
    if (!present("_tutorial_sign"))
    {
        add_sign(TUTORIAL_CHAPTER);
    }
} /* reset_room */


/* 
 * Function name:        check_exit
 * Description  :        check to see if the gate is open. If not prevent
 *                       the player from leaving
 * Returns      :        1 - the gate is closed, 0 - the gate is open
 */
public int
check_exit()
{
    if (this_player()->query_prop(OPENED_GATE_PROP))
    {
        write("As you travel north, the gate swings closed behind you!\n");
        return 0;
    }

    write("The closed gate prevents you from going that way. You'll have"
      + " to find a way to open it first.\n");
    return 1;
} /* check_exit */


/*
 * Function name:        hint
 * Description  :        give the player a hint if they get stuck
 * Arguments    :        string - what the player typed
 * Returns      :        int 1
 */
public int
hint(string arg)
{
    if (arg == "full")
    {
        write("Here's what you should do:\n\n"
          + "    <l>\n"
          + "    <exa torch>\n"
          + "    <search torch>\n"
          + "    <pull torch>\n"
          + "    <n>\n\n"
          + "There are other, fun secrets to find here though. :-)\n");

        return 1;
    }

    write("Need a hint? Sure ... first you should <l>ook at the room"
      + " and notice that there are some things to look at. You might"
      + " try to <exa> the tapestry, rug, and torch. Of course, to find"
      + " the way to open the gate, you will have to make use of the"
      + " <search> command. If you still need more help, type <hint"
      + " full>.\n");

    return 1;
} /* hint */




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
        ({ "tapestry", "large tapestry",
           "gate", "iron gate", "strong iron gate", "strong gate",
           "carpet", "heavy carpet", "rug", "heavy rug",
           "torch", "burning torch" }) ) == -1))
    {
        return "Your search reveals nothing special. Perhaps you"
          + " should try to search something specific in the room"
          + " instead? For example, you could <search gate> or some"
          + " other thing you see here.\n";
    }

    switch(arg)
    {
        case "tapestry":
        case "large tapestry":
            return "You move the tapestry aside to see if there is"
              + " anything behind it. All you find is a bare stone"
              + " wall.\n";
            break;
        case "gate":
        case "iron gate":
        case "strong gate":
        case "strong iron gate":
            return "You thoroughly search the gate. It does not appear"
              + " to have any lock or keyhole.\n";
            break;
        case "carpet":
        case "heavy carpet":
        case "rug":
        case "heavy rug":
            return "You lift the rug to see if there is anything of"
              + " interest beneath. Unfortunately, there is not.\n";
            break;
        case "torch":
        case "burning torch":
            return "Searching the torch, you notice that it appears to"
              + " be attached to a mechanism of some kind! You might be"
              + " able to <pull> it if you tried.\n";
            break;
        default:
            return "You search around the area, but don't find anything"
              + " of interest.\n";
    }

    return "Your search does not reveal anything at all.\n";
} /* do_search */


/*
 * Function name:        do_open
 * Description  :        allow players to try to open, unlock, close,
 *                       or lock the gate.
 * Arguments    :        string arg - what the player typed
 * Returns      :        int 1 - success, 0 - failure
 */
public int
do_open(string arg)
{
    if (!strlen(arg))
    {
        notify_fail("What do you wish to " + query_verb() + "?\n");
        return 0;
    }

    if (!parse_command(arg, ({}),
        "[the] [strong] [iron] 'gate' [with] [the] [key]"))
    {
        return 0;
    }

    if (query_verb() == "lock" || query_verb() == "unlock")
    {
        write("Even if you did have the proper key, this gate"
          + " does not appear to have any lock.\n");
        return 1;
    }

    if (query_verb() == "close")
    {
        if (this_player()->query_prop(OPENED_GATE_PROP))
        {
            write("You aren't able to budge the gate. Perhaps the way"
              + " to close it is similar to the way it was opened.\n");
            return 1;
        }

        write("The gate is already closed.\n");
        return 1;
    }

    if (this_player()->query_prop(OPENED_GATE_PROP))
    {
        write("The gate is already open.\n");
        return 1;
    }

    write("You tug and pull on the gate, but it simply will" 
      + " not budge. Perhaps there is another way to open it"
      + " that is not so obvious. Try using the <search> command"
      + " on the things you see in this room.\n");
    return 1;
} /* do_open */


/*
 * Function name:
 * Function name:        init
 * Description  :        add some actions to the player
 */
public void
init()
{
    ::init();

    add_action(do_open, "open");
    add_action(do_open, "close");
    add_action(do_open, "lock");
    add_action(do_open, "unlock");
    add_action(do_open, "pull");
    add_action(do_open, "push");
    add_action(do_open, "move");
    add_action(pull_torch, "pull");
    add_action(pull_torch, "move");
    add_action(pull_torch, "push");
    add_action(hint, "hint");
    add_action(skip, "skip");
    add_action(tutorial_quit, "quit");
} /* init */


/*
 * Function name:        pull_torch
 * Description  :        allow players to pull the torch, opening the gate
 * Arguments    :        string arg - what the player typed
 * Returns      :        int 1 - success, 0 - failure
 */
public int
pull_torch(string arg)
{
    int     gate_prop = this_player()->query_prop(OPENED_GATE_PROP);

    if (!strlen(arg))
    {
        notify_fail("What do you want to " + query_verb() + "?\n");
        return 0;
    }

    if (!parse_command(arg, ({}),
        "[the] [burning] 'torch' / 'mechanism'"))
    {
        return 0; /* let the mudlib handle this */
    }

    if (gate_prop >= 2)
    {
        write("The torch is slowly moving upward right now, and"
          + " you are not able to pull it.\n");
        return 1;
    }

    write("You pull on the torch, bending it downward into a position"
      + " where it sticks straight out from the wall. As you release"
      + " your grip, the torch begins to bend slowly upward. As it"
      + " continues to rise, you hear the turning of gears in the"
      + " wall.\n");
    set_alarm(2.0, 0.0, &open_gate(this_player()));
    this_player()->add_prop(OPENED_GATE_PROP, gate_prop + 2);

    return 1;
} /* pull_torch */


/*
 * Function name:        open_gate
 * Description  :        have the gate open for the player, with a
 *                       slight delay
 * Arguments    :        object player - the player object
 */
public void
open_gate(object player)
{
    if (player->query_prop(OPENED_GATE_PROP) == 3)
    {
        write("The torch snaps back into place in its upward position."
          + " With a slight creak, the gate in the north wall swings"
          + " shut.\n");
        player->add_prop(OPENED_GATE_PROP, 0);

        return;
    }

    write("The torch snaps back into place in its upward position. With"
      + " a slight creak, the gate in the north wall swings open.\n");
    player->add_prop(OPENED_GATE_PROP, 1);

    return;
} /* open_gate */
