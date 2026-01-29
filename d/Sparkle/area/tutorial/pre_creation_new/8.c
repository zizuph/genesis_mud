/*
 *  /d/Sparkle/area/tutorial/pre_creation_new/8.c
 *
 *  This room teaches people how to <exa> things, pre-creation.
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
public void        init();


/* global variables */
public int         Tell_Alarm;
public int         Moving_Now = 0;
public int         Cave_Seen = 0;


/*
 * Function name:        create_room
 * Description  :        set up the room
 */
public void
create_room()
{
    set_name("8");
    set_short("again, the woods close behind you as you move forward."
      + " You stand in a clearing in the woods beside a tall cliff."
      + " You notice a cave in the cliff wall");
    set_long(capitalize(short()) + ".\n\n");

    add_prop(ROOM_M_NO_TELEPORT,
        "A strange force prevents your travel.\n");
    add_prop(ROOM_I_INSIDE, 1);

    add_item( ({ "wood", "woods", "tree", "trees", "forest" }),
        "The woods have grown vivid, and nearly lifelike.\n");
    add_item( ({ "animal", "animals", "sounds", "calls", "call" }),
        "You only hear them, but their calls seem very real.\n");
    add_item( ({ "clearing" }),
        "You are standing in the middle of the clearing.\n");
    add_item( ({ "cliff", "tall cliff", "cliff wall", "wall" }),
        "You notice a cave in the cliff wall. Perhaps you should"
      + " <examine cave> instead?\n");
    add_item( ({ "cave" }), "@@exa_cave@@");

    /* For instancing purposes, we do this with an invisible exit. */
    add_exit("9", "north", block_exit, 1, 1);

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

    who->catch_tell("\nA friendly voice says: You must explore things"
      + " in this world, friend. Type <exa cave> or <examine cave> to"
      + " learn more about your surroundings!\n");
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

    if (Cave_Seen)
    {
        who->catch_tell(one_of_list( ({
            "\nNow that you have looked more closely at the cave, you"
          + " can <enter> it to move on.\n",
            "\nYou feel the cave beckoning to you. Perhaps you should"
          + " <enter> it now?\n",
            "\nYou now feel confident to <enter> the cave.\n" }) ) );
    }
    else
    {
        who->catch_tell(one_of_list( ({
            "\nYou feel you could learn something if you <examine cave>"
          + " here.\n",
            "\nYou could simply type <exa cave> to save keystrokes.\n",
            "\nThere appear to be no exits here. You'll need to <exa cave>"
          + " (<exa> is a shortcut for <examine>) to discover more.\n" }) ) );
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
    set_short("you stand in a clearing in the woods next to a tall cliff."
      + " You notice a cave in the cliff wall");
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
 * Function name:        do_enter
 * Description  :        Allow players to enter the cave
 * Arguments    :        string arg - what was typed after the verb
 * Returns      :        int 1 - success, 0 - failure
 */
public int
do_enter(string arg)
{
    notify_fail("Do you want to <enter cave> perhaps?\n");

    if (!strlen(arg))
    {
        return 0;
    }

    if (!parse_command(arg, ({}),
        "[the] 'cave'"))
    {
        return 0;
    }

    write("You carefully enter the cave.\n\n");
    Moving_Now = 1;
    this_player()->command("$north");

    return 1;
} /* do_enter */


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

    log_move("9");
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
    add_action(do_enter, "enter");
} /* init */


/*
 * Function name:        exa_cave
 * Description  :        trip a flag when the player examines the cave
 * Returns      :        string - the cave description
 */
public string
exa_cave()
{
    if (Cave_Seen)
    {
        return "You should probably try to <enter cave> to move onward,"
          + " now that you have successfully inspected the cave.\n";
    }

    Cave_Seen = 1;

    return "The cave looks large enough to explore. You may <enter cave>"
      + " to move onward. Congratulations, you have learned something"
      + " by using <examine>!\n";
} /* exa_cave */