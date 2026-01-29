/*
 *  /d/Sparkle/area/tutorial/pre_creation_new/7.c
 *
 *  This room teaches people how to kill monsters, pre-tutorial.
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
public void        new_descs();
public void        enter_inv(object ob, object from);
public int         catch_all(string str);
public int         block_exit();
public int         init();

/* global variables */
public int         Tell_Alarm;
public int         Snake_Called = 0;
public object      Serpent;


/*
 * Function name:        create_room
 * Description  :        set up the room
 */
public void
create_room()
{
    set_name("7");
    set_short("again, the woods close behind you as you move forward."
      + " The trees here crowd in on either side of the path, forcing"
      + " you through a very narrow passage in the forest. To the north,"
      + " you spy a clearing ahead");
    set_long(capitalize(short()) + ".\n\n");

    add_prop(ROOM_M_NO_TELEPORT,
        "A strange force prevents your travel.\n");
    add_prop(ROOM_I_INSIDE, 1);

    add_item( ({ "path", "dirt path", "dirt" }),
        "The path travels to the north, through this forest.\n");
    add_item( ({ "wood", "woods", "tree", "trees", "forest" }),
        "The woods have grown vivid, and nearly lifelike.\n");
    add_item( ({ "animal", "animals", "sounds", "calls", "call" }),
        "You only hear them, but their calls seem very real.\n");
    add_item( ({ "clearing" }),
        "The clearing is visible to the north.\n");

    add_exit("8", "north", block_exit, 1, 0);

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

    who->catch_tell(one_of_list( ({
        "\nThe obvious exit to the <north> seems to beckon you onward.\n",
        "\nYou could simply type <n> here to save keystrokes.\n",
        "\nTo see where you are, simply type <look> or <l> to use your"
      + " eyes, and then follow one of the obvious exits.\n" }) ) );

    Tell_Alarm = set_alarm(20.0, 0.0, &first_message(who));

    return;
} /* first_message */


/*
 * Function name:      new_descs
 * Description  :      change the descs once the player has already 
 *                     seen them.
 */
public void
new_descs()
{
    set_short("the trees here crowd in on either side of the path, forcing"
      + " you through a very narrow passage in the forest. To the north,"
      + " you spy a clearing ahead");
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

    set_alarm(15.0, 0.0, &first_message(ob));
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
        case "kill":
        case "commune":
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
 * Function name:        block_exit
 * Description  :        block the exit if the player has not yet killed
 *                       the serpent.
 * Returns      :        int 1 - block, 0 - allow
 */
public int
block_exit()
{
    object  sword;

    if (!Snake_Called)
    {
        write("A shadow serpent materializes out of thin air, blocking"
          + " your path! You can try to <kill> it with your weapon.\n");

        Serpent = clone_object(
            "/d/Sparkle/area/tutorial/pre_creation_new/serpent");
        Serpent->move(this_object());

        Snake_Called = 1;

        return 1;
    }

    if (Serpent)
    {
        write("The shadow serpent blocks your path! You will first need"
          + " to <kill> it before moving on.\n");
        return 1;
    }

    sword = present("_pre_creation_sword", this_player());

    if (objectp(sword))
    {
        sword->remove_object();
        write("\nYour sword disappears in a flash of light!\n\n");
    }

    log_move("8");
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
} /* init */