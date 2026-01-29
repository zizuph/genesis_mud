/*
 *  /d/Sparkle/area/tutorial/pre_creation_new/3.c
 *
 *  This room teaches people how to move around, pre-creation.
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
public int         init();

/* global variables */
public int         Tell_Alarm;


/*
 * Function name:        create_room
 * Description  :        set up the room
 */
public void
create_room()
{
    set_name("3");
    set_short("as you walk forward, the clouds seem to close behind you."
      + " Ahead, the images become clearer, taking the form of a dirt"
      + " path leading through some woods. The path turns northwest here,"
      + " and you feel the urge to follow it forward");
    set_long(capitalize(short()) + ".\n\n");

    add_prop(ROOM_M_NO_TELEPORT,
        "A strange force prevents your travel.\n");
    add_prop(ROOM_I_INSIDE, 1);

    add_item( ({ "path", "dirt path", "dirt" }),
        "The path is still very hazy, but it clearly is the only way"
      + " forward.\n");
    add_item( ({ "wood", "woods", "tree", "trees", "forest" }),
        "The woods are very hazy, just lingering on the edges of"
      + " reality.\n");

    add_exit("4", "northwest", &log_move("4"), 1, 0);

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

    who->catch_tell("\nA friendly voice says: Very good. Let's see if"
      + " you can find the end of the path. Notice the \"obvious exit\""
      + " that tells you that you can type <northwest> to travel onward.\n");

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

    who->catch_tell(one_of_list( ({
        "\nThe obvious exit to the <northwest> seems to beckon you onward.\n",
        "\nYou could also simply type <nw> to save keystrokes.\n",
        "\nTo see where you are, simply type <look> or <l> to use your"
      + " eyes, and then follow the obvious exit.\n" }) ) );

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
    set_short("you stand on a dirt path leading through some woods."
      + " The path turns northwest here, and you feel the urge to follow"
      + " it forward");
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

    set_alarm(10.0, 0.0, &first_message(ob));
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
        case "skip":
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
} /* init */