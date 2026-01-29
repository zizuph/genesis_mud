/*
 *  /d/Sparkle/area/tutorial/pre_creation/5.c
 *
 *  This room demonstrates the way doors and locks work in Genesis. The
 *  reason I have not simply cloned normal door code into the room
 *  is that I want more than one player to be able to complete this
 *  room at the same time. In other words, I don't want anyone to be
 *  able to open the door for anyone else - so, the door exists relative
 *  to each individual player.
 *
 *  Created August 2004, by Cooper Sherry (Gorboth)
 */
#pragma strict_types
#include "../defs.h"

inherit "/std/room";
inherit LIB_DIR + "skip";
inherit LIB_DIR + "lib_sign";

#include <language.h>
#include <stdproperties.h>


/* definitions */
#define  TUTORIAL_CHAPTER    5  /* the chapter for the sign */


/* prototypes */
public void        create_room();
public string      exa_door();
public void        reset_room();
public int         check_exit();
public int         player_opened(object player, int open_or_lock = 0);
public int         mess_with_door(string arg);
public void        init();
public int         get_key(string arg);
public int         hint(string arg);


/*
 * Function name:        create_room
 * Description  :        set up the room
 */
public void
create_room()
{
    set_name("5");
    set_short("a small room with a door");
    set_long("This room is small and fairly plain. The walls are"
    + " mostly bare except for a door set in the north"
    + " wall.\n\n");

    add_item( ({ "hue", "color", "colour", "sage", "forest",
                 "sage green", "forest green" }),
        "The hue is not quite forest green and not quite sage green,"
      + " it is something in between.\n");
    add_item( ({ "wall", "walls" }),
        "Which wall do you wish to examine?\n");
    add_item( ({ "east", "south", "east wall", "south wall",
                 "eastern wall", "southern wall" }),
        "This wall has been painted green, but is otherwise"
      + " nondescript.\n");
    add_item( ({ "paint", "green", "green paint" }),
        "This room has been painted green. The hue is somewhere"
      + " between sage and forest green.\n");
    add_item( ({ "west", "west wall", "western wall",
                 "opening", "passage",
                 "passage in the western wall" }),
        "A passage in the northern portion of the western wall leads"
      + " back to the previous room of this tutorial.\n");
    add_item( ({ "north", "northern wall", "north wall", "door",
                 "doorway", "open door", "closed door",
                 "open doorway", "closed doorway" }), exa_door);
    add_item( ({ "floor", "ground", "down" }),
        "Even the floor of this room has been painted green.\n");
    add_item( ({ "up", "ceiling", "roof" }),
        "Peering up, you notice that the ceiling is painted green.\n");
    add_item( ({ "box", "small box", "box of keys", "key box" }),
        "The box is filled with many keys. When you need to get something"
      + " which is inside a container such as this, you must specify"
      + " both what you want to get, and where you want to get it from."
      + " For instance, <get flower from pot>.\n");
    add_item( ({ "key", "keys", "many keys" }),
        "There are many keys inside of the box.\n");
    add_item( ({ "lock", "keyhole", "shiny keyhole", "silver keyhole",
                 "shiny silver keyhole" }),
        "A shiny silver keyhole is set in the door.\n");
    
    add_prop(ROOM_I_INSIDE, 1);

    add_exit("4", "northwest", &log_move("4"), 1, 0);
    add_exit("6", "north", check_exit, 1, 0);

    setuid();
    seteuid(getuid());

    reset_room();
} /* create_room */

   
/*
 * Function name:        exa_door
 * Description  :        give a description with the changing state
 *                       of the door involved
 * Returns      :        string - the description
 */
public string
exa_door()
{
    string  door;

    if (this_player()->query_prop(OPENED_DOOR_PROP))
    {
        door = "open";
    }
    else
    {
        door = "closed";
    }

    return capitalize(LANG_ADDART(door)) + " doorway stands in the center of"
      + " the north wall. Mounted on the wall next to the door is a"
      + " small box.\n";
} /* exa_door */


/*
 * Function name:        reset_room
 * Description  :        add a sign to the room
 */
public void
reset_room()
{
    object   sign;

    if (!present("_tutorial_sign"))
    {
        add_sign(TUTORIAL_CHAPTER);
    }

    return;
} /* reset_room */


/*
 * Function name:        player_opened
 * Description  :        check to see if a prop has been set in the player
 *                       telling us that s/he has opened or unlocked
 *                       the door.
 * Arguments    :        int open_or_lock - this function is used to check
 *                                          both for opened and locked
 *                                          status of the door. default
 *                                          checks are for opened status.
 * Returns      :        int 1 = closed/locked, 0 = open/unlocked
 */
public int
player_opened(object player, int open_or_lock = 0)
{
    if (open_or_lock)
    {
        return player->query_prop(UNLOCKED_DOOR_PROP);
    }

    return player->query_prop(OPENED_DOOR_PROP);
} /* player_opened */


/* 
 * Function name:        check_exit
 * Description  :        check to see if the door is open. If not prevent
 *                       the player from leaving
 * Returns      :        1 - the door is closed, 0 - the door is open
 */
public int
check_exit()
{
    if (player_opened(this_player()))
    {
        log_move("6");
        return 0;
    }

    write("You need to open the door first.\n");
    return 1;
} /* check_exit */




/*
 * Function name:        mess_with_door
 * Description  :        allow the player to unlock and open the door
 * Arguments    :        string arg - what the player typed
 * Returns      :        1 - success, 0 - failure
 */
public int
mess_with_door(string arg)
{
    object   ob;

    if (query_verb() == "knock")
    {
        if (!strlen(arg))
        {
            notify_fail("Knock on what?\n");
            return 0;
        }

        if (!parse_command(arg, ({}),
            "[on] [the] 'door'"))
        {
            return 0; /* bad syntax */
        }

        write("You knock on the door, but get no answer.\n");
        return 1;
    }

    if (!strlen(arg))
    {
        notify_fail("What do you wish to " + query_verb() + "?\n");
        return 0;
    }

    if (query_verb() == "open")
    {
        if (!parse_command(arg, ({}),
            "[the] 'door'"))
        {
            return 0; /* let the mudlib handle this one */
        }

        if (this_player()->query_prop(OPENED_DOOR_PROP))
        {
            write("The door is already open.\n");
            return 1;
        }

        if (!this_player()->query_prop(UNLOCKED_DOOR_PROP))
        {
            write("The door is locked.\n");
            return 1;
        }

        this_player()->add_prop(OPENED_DOOR_PROP, 1);
        write("You open the door.\n"
          + "Congratulations! Now that you've figured out how to use a few"
          + " basic commands such as <get>, <open>, <unlock>, etcetera,"
          + " you are ready for the next room of the tutorial. It is"
          + " right through this door to the north.\n");

        return 1;
    }

    if (query_verb() == "close" || query_verb() == "shut")
    {
        if (!parse_command(arg, ({}),
            "[the] 'door'"))
        {
            return 0; /* let the mudlib take it from here */
        }

        if (!this_player()->query_prop(OPENED_DOOR_PROP))
        {
            write("The door is already closed.\n");
            return 1;
        }

        this_player()->add_prop(OPENED_DOOR_PROP, 0);
        write("You close the door.\n");

        return 1;
    }

    if (query_verb() == "lock")
    {
        if (!parse_command(arg, ({}),
            "[the] 'door' 'with' [the] 'key'"))
        {
            if (parse_command(arg, ({}),
                "[the] 'door'"))
            {
                write("What do you want to lock the door with?\n");
                return 1;
            }
        
            return 0; /* bad syntax */
        }

        if (!present("_tutorial_key", this_player()))
        {
            write("You don't have the key.\n");
            return 1;
        }

        if (this_player()->query_prop(OPENED_DOOR_PROP))
        {
            write("You would need to close the door first.\n");
            return 1;
        }

        if (!this_player()->query_prop(UNLOCKED_DOOR_PROP))
        {
            write("The door is already locked.\n");
            return 1;
        }

        write("You lock the door, using your key.\n");
        this_player()->add_prop(UNLOCKED_DOOR_PROP, 0);

        return 1;
    }

    if (!parse_command(arg, all_inventory(this_player()),
        "[the] 'door' 'with' [the] %o", ob))
    {
        if (parse_command(arg, ({}),
            "[the] 'door'"))
        {
            write("Unlock the door with what?\n");
            return 1;
        }

        return 0; /* can't parse the syntax */
    }

    if (!ob->id("_tutorial_key"))
    {
        write("You can't unlock the door with that.\n");
        return 1;
    }

    if (this_player()->query_prop(UNLOCKED_DOOR_PROP))
    {
        write("The door is already unlocked.\n");
        return 1;
    }

    write("You unlock the door with the key.\n");
    this_player()->add_prop(UNLOCKED_DOOR_PROP, 1);

    return 1;
} /* mess_with_door */


/*
 * Function name:        init
 * Description  :        add some actions to the player
 */
public void
init()
{
    ::init();

    add_action(mess_with_door, "open");
    add_action(mess_with_door, "unlock");
    add_action(mess_with_door, "lock");
    add_action(mess_with_door, "close");
    add_action(mess_with_door, "shut");
    add_action(mess_with_door, "knock");
    add_action(get_key, "take");
    add_action(get_key, "get");
    add_action(hint, "hint");
    add_action(skip, "skip");
    add_action(tutorial_stat, "stats");
    add_action(tutorial_quit, "quit");
} /* init */


/*
 * Function name:        get_key
 * Description  :        allow mortals to get a single key from the box
 * Arguments    :        string arg - what the player typed
 * Returns      :        int 1 - success, 0 - failure
 */
public int
get_key(string arg)
{
    object   key;

    if (!strlen(arg))
    {
        return 0; /* let the mudlib handle it */
    }

    if (arg == "flower from pot")
    {
        write("No, no ... that was only an example. There are no flowers"
          + " or pots here. You need to use the syntax <get x from x>"
          + " to retrieve items from containers.\n");

        return 1;
    }

    if (!parse_command(arg, ({}),
        "[the] [a] 'key' / 'keys' 'from' [the] [small] 'box'"))
    {
        if (parse_command(arg, ({}),
            "[a] [the] 'key' / 'keys'"))
        {
            write("The keys are inside the box.\n");
            return 1;
        }

        if (parse_command(arg, ({}),
            "[a] [the] 'key' / 'keys' 'in' [the] [small] 'box'"))
        {
            write("Use syntax: <get [item] from [place]>\n");
            return 1;
        }

        return 0; /* give it to the mudlib */
    }

    if (present("_tutorial_key", this_player()))
    {
        write("You already have a key. There is no need to take more.\n");
        return 1;
    }

    key = clone_object(OBJ_DIR + "key")->move(this_player());
    write("You take a key from the box. Congratulations! You now have an"
      + " item in your inventory. To see everything you are carrying, you"
      + " can type <i>. You can also <exa> anything you have in your"
      + " inventory.\n");

    return 1;
} /* get_key */


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
          + "    <exa door>\n"
          + "    <exa box>\n"
          + "    <get key from box>\n"
          + "    <unlock door with key>\n"
          + "    <open door>\n"
          + "    <n>\n\n"
          + "Don't be afraid to experiment! :-)\n");

        return 1;
    }

    write("Need a hint? No problem ... first of all, you should use <exa>"
      + " to look at everything you can in the room. Once you do, you"
      + " might notice something next to the door. It has what you need"
      + " to unlock the door and move on. If you are still stuck after"
      + " trying these suggestions, you can get more specific help by"
      + " typing <hint full>.\n");

    return 1;
} /* hint */



