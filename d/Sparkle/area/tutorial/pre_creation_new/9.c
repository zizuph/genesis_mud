/*
 *  /d/Sparkle/area/tutorial/pre_creation_new/9.c
 *
 *  This room teaches people how to <search> things, pre-creation.
 *
 *  Created May 2011, by Cooper Sherry (Gorboth)
 */
#pragma strict_types
#include "../defs.h"
#include "/d/Genesis/start/newbie/newbie.h"

inherit "/std/room";
inherit LIB_DIR + "instance";
inherit LIB_DIR + "skip";

#include <macros.h>
#include <stdproperties.h>


/* prototypes */
public void        create_room();
public void        first_message(object who);
public void        second_message(object who);
public void        new_descs();
public void        enter_inv(object ob, object from);
public int         catch_all(string str);
public int         block_exit();
public string      do_search(object pl, string arg);
public int         read_writing(string arg);
public void        init();


/* global variables */
public int         Tell_Alarm;
public int         Button_Seen = 0;
public int         Cave_Searched = 0;
public int         Moving_Now = 0;


/*
 * Function name:        create_room
 * Description  :        set up the room
 */
public void
create_room()
{
    set_name("9");
    set_short("as you enter, the entrance closes behind you, leaving"
      + " you standing in a dark featureless cave");
    set_long(capitalize(short()) + ".\n\n");

    add_prop(ROOM_M_NO_TELEPORT,
        "A strange force prevents your travel.\n");
    add_prop(ROOM_I_INSIDE, 1);
    add_prop(OBJ_S_SEARCH_FUN, "do_search");

    add_item( ({ "cave", "dark cave", "featureless cave",
                 "dark featureless cave" }),
        "At first glance, the cave seems empty. Perhaps if you were"
      + " to <search> you might find something.\n");
    add_item( ({ "writing", "writing on the wall" }),
        "You notice writing on the wall that you could probably"
      + " <read> if you wished.\n");
    add_item( ({ "wall", "walls" }),
        "The walls of the cave surround you. If you were to <search>"
      + " here you might find something more interesting, though.\n");
    add_item( ({ "button" }),
        "There is a button beneath the writing on the wall. Perhaps"
      + " you could <press> it?\n");

    /* For instancing purposes, we do this with an invisible exit. */
    add_exit("10", "north", block_exit, 1, 1);

    setuid();
    seteuid(getuid());
} /* create_room */


/*
 * Function name:        first_message
 * Description  :        first message for the player
 * Arguments    :        object who - the player
 */
public void
first_message(object who)
{
    if (!objectp(who))
    {
        return;
    }

    if (environment(who) != this_object())
    {
        return;
    }

    who->catch_tell("\nA friendly voice says: Here, you must use"
      + " your sense of exploration further. To investigate an area,"
      + " type <search> to see what can be found.\n");
    set_alarm(15.0, 0.0, &second_message(who));

    return;
} /* first_message */


/*
 * Function name:        second_message
 * Description  :        second message for the player
 * Arguments    :        object who - the player
 */
public void
second_message(object who)
{
    if (!objectp(who))
    {
        return;
    }

    if (environment(who) != this_object())
    {
        return;
    }

    if (Button_Seen)
    {
        who->catch_tell(one_of_list( ({
            "\nThe button on the wall beckons you to <press> it.\n",
            "\nYou somehow know that your next move would be to"
          + " <press> the button on the wall.\n",
            "\nSurely something more would happen if you were to"
          + " <press> the button on the wall.\n" }) ) );
    }
    else if (Cave_Searched)
    {
        who->catch_tell(one_of_list( ({
            "\nThat writing on the wall looks interesting. Perhaps you"
          + " should <read> it.\n",
            "\nYour thoughts are continually drawn to the writing on"
          + " the wall, which you could probably <read>.\n",
            "\nYou sense that you will need to <read> the writing on"
          + " the wall to discover more.\n" }) ) );
    }
    else
    {
        who->catch_tell(one_of_list( ({
            "\nYou feel you might learn something if you <search>"
          + " here.\n",
            "\nIt is often useful to <search> if you find yourself"
          + " unsure of what is in a room.\n",
            "\nThere appear to be no exits here. You'll need to <search>"
          + " to discover more.\n" }) ) );
    }

    Tell_Alarm = set_alarm(20.0, 0.0, &second_message(who));

    return;
} /* second_message */


/*
 * Function name:      new_descs
 * Description  :      change the descs once the player has already 
 *                     seen them.
 */
public void
new_descs()
{
    set_short("you are standing in a dark featureless cave");
    set_long(capitalize(short()) + ".\n\n");
} /* new_descs */


/* 
 * Function name: enter_inv
 * Description:   Called when objects enter this container or when an
 *                object has just changed its weight/volume/light status.
 * Arguments:     ob: The object that just entered this inventory
 *                from: The object from which it came.
 */
public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if (!living(ob))
    {
        return;
    }

    set_alarm(0.1, 0.0, new_descs);

    set_alarm(9.0, 0.0, &first_message(ob));
    return;
} /* enter_inv */


/*
 * Function name:        catch_all
 * Description  :        When players type things we want to give them a
 *                       message, rather than just "What?"
 * Arguments    :        string str
 * Returns      :        1 - to block the command, 0 - to let it through
 */
public int 
catch_all(string str)
{
    if (this_player()->query_wiz_level())
    {
        return 0;
    }

    switch (query_verb())
    {
        case "north":
        case "northwest":
        case "west":
        case "southwest":
        case "south":
        case "southeast":
        case "east":
        case "northeast":
        case "up": 
        case "down":
            return 0;
            break;
        case "quit":
        case "look":
        case "l":
        case "exa":
        case "examine":
        case "commune":
        case "enter":
        case "get":
        case "wield":
        case "unwield":
        case "take":
        case "pick":
        case "search":
        case "push":
        case "press":
        case "read":
        case "skip":
        case "i":
        case "inventory":
            return 0;
            break;
        default:
            write("Your mind is still coming to grips with things."
              + " Apparently, you aren't able to do much now other than"
              + " look, move around and learn.\n");
            return 1;
            break;
    }
} /* catch_all */


/*
 * Function name:        press_button
 * Description  :        Allow players to enter the cave
 * Arguments    :        string arg - what was typed after the verb
 * Returns      :        int 1 - success, 0 - failure
 */
public int
press_button(string arg)
{
    notify_fail("Do you want to <press button> perhaps?\n");

    if (!strlen(arg))
    {
        return 0;
    }

    if (!parse_command(arg, ({}),
        "[the] 'button'"))
    {
        return 0;
    }

    write("You press the button, and there is a blinding flash!\n\n");

    Moving_Now = 1;
    this_player()->command("$north");

    return 1;
} /* press_button */


/*
 * Function name:        block_exit
 * Description  :        block the exit if the player has not yet killed
 *                       the serpent.
 * Returns      :        int 1 - block, 0 - allow
 */
public int
block_exit()
{
    if (!Moving_Now)
    {
        write("There is no obvious exit north.\n");
        return 1;
    }

    log_move("10");
    return 0;
} /* block_exit */


/*
 * Function name:        init
 * Description  :        add some actions to the player
 */
public void
init()
{
    ::init();

    add_action(skip, "skip");
    add_action(tutorial_quit, "quit");
    add_action(catch_all, "", 1);
    add_action(press_button, "press");
    add_action(press_button, "push");
    add_action(read_writing, "read");
} /* init */


/*
 * Function name:        do_search
 * Description  :        Provide a room-specific result for the
 *                       basic <search> command
 * Arguments    :        object pl - the player
 *                       string arg - what was typed
 * Returns      :        string - the result message.
 */
public string
do_search(object pl, string arg)
{
    Cave_Searched = 1;

    return "You give the cave a thorough search, and notice some writing"
      + " on the wall that you could <read>.\n";
} /* do_search */


/*
 * Function name:        read_writing
 * Description  :        Allow players to read the writing on the wall
 * Arguments    :        string arg - whatever was typed after the verb
 * Returns      :        int 1 - success, 0 - failure
 */
public int
read_writing(string arg)
{
    notify_fail("Do you want to <read writing> perhaps?\n");

    if (!strlen(arg))
    {
        return 0;
    }

    if (!parse_command(arg, ({}),
        "[the] 'writing' [on] [the] [cave] [wall]") &&
        !parse_command(arg, ({}),
        "[the] [cave] 'wall' / 'walls'"))
    {
        return 0;
    }

    write("The writing on the wall reads:\n\n"
      + "\tTO FIND ME, YOU MUST PRESS THE BUTTON.\n\n"
      + "You notice a button beneath the writing, embedded in the wall.\n");

    Button_Seen = 1;

    return 1;
} /* read_writing */