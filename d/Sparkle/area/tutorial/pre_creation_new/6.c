/*
 *  /d/Sparkle/area/tutorial/pre_creation_new/6.c
 *
 *  This room teaches people how to get and wield weapons, pre-creation.
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


/* global variables */
public int         Tell_Alarm;
public object      Sword;
public int         Sword_Grabbed = 0;
public int         Inventory_Checked = 0;

/* prototypes */
public void        create_room();
public void        first_message(object who);
public void        second_message(object who);
public void        new_descs();
public void        enter_inv(object ob, object from);
public int         catch_all(string str);
public int         block_exit();
public int         init();
public void        set_inventory_checked(object who);
public void        inventory_message(object who);
public void        set_sword_grabbed(int i);
public void        sword_grabbed_flag(int i);

public int         query_sword_grabbed() { return Sword_Grabbed; }
public int         query_inventory_checked() { return Inventory_Checked; }


/*
 * Function name:        create_room
 * Description  :        set up the room
 */
public void
create_room()
{
    set_name("6");
    set_short("As you move forward, a flash of magic blinds you"
      + " momentarily! Blinking, you see that a gleaming artifact has"
      + " appeared before you on the path");
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

    if (!Sword_Grabbed)
    {
        who->catch_tell("\nA friendly voice says: Use your hands"
          + " hands, my friend! Type <get artifact> to pick up the item.\n");
    }

    set_alarm(7.0, 0.0, &second_message(who));

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
        "\nThe obvious exit to the <north> seems to beckon you onward.\n",
        "\nYou could simply type <n> here to save keystrokes.\n",
        "\nTo see where you are, simply type <look> or <l> to use your"
      + " eyes, and then follow one of the obvious exits.\n" }) ) );

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
    set_short("The forest around you now seems very much real and alive, and"
      + " a sense of urgency builds in you, bidding you to follow the"
      + " path onward. It seems the path now turns to the north");
    set_long(capitalize(short()) + ".\n\n");

    add_exit("7", "north", block_exit, 1, 0);

    if (!objectp(Sword))
    {
        Sword = clone_object(
            "/d/Sparkle/area/tutorial/pre_creation_new/sword");
        Sword->move(this_object());
    }
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

    set_alarm(8.0, 0.0, &first_message(ob));
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
        case "get":
        case "wield":
        case "unwield":
        case "take":
        case "pick":
        case "commune":
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
 * Description  :        block the exit if the player does not yet
 *                       possess the weapon
 * Returns      :        int 1 - block, 0 - allow
 */
public int
block_exit()
{
    if (environment(Sword) == this_player())
    {
        if (!Inventory_Checked)
        {
            write("Before moving on, you should see what it is you have"
              + " just picked up. To do this, type <i> to see what is"
              + " in your inventory.\n");
            return 1;
        }

        if (!Sword->query_wielded() &&
            !this_player()->query_prop("_tutorial_sword_wield"))
        {
            write("There is a sense of danger ahead. You somehow know"
              + " it would be safer to <wield> your sword before moving"
              + " on.\n");
            return 1;
        }

        log_move("7");
        return 0;
    }

    write("You sense that you should pick up the artifact before moving"
      + " on. Type <get artifact> to do so.\n");
    return 1;
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


/*
 * Function name:        set_inventory_checked
 * Description  :        Set a flag when the player first checks their
 *                       inventory and set an alarm to deliver them a
 *                       message about it.
 * Arguments    :        object who - the player
 */
public void
set_inventory_checked(object who)
{
    Inventory_Checked = 1;

    if (!objectp(who))
    {
        return;
    }

    set_alarm(3.0, 0.0, &inventory_message(who));
    return;
} /* set_inventory_checked */


/*
 * Function name:        inventory_message
 * Description  :        Give the player some info about their next
 *                       move after checking their inventory
 * Arguments    :        object who - the player
 */
public void
inventory_message(object who)
{
    if (!objectp(who) || !interactive(who) ||
         sizeof(who->query_weapon(-1)))
    {
        return;
    }

    who->catch_tell("\nWell done! You've managed to check your inventory,"
      + " and it looks like the artifact was a sword. You can now"
      + " type <wield sword> to ready it for use.\n");

    return;
} /* inventory_message */


/*
 * Function name:        set_sword_grabbed
 * Description  :        Set a flag when the sword is grabbed, but with
 *                       a slight delay for cosmetic reasons
 * Arguments    :        int i - the value we want
 */
public void
set_sword_grabbed(int i)
{
    set_alarm(0.1, 0.0, &sword_grabbed_flag(i));
    return;
} /* set_sword_grabbed */


/*
 * Function name:        sword_grabbed_flag
 * Description  :        the resolution of the set_sword_grabbed call
 * Arguments    :        int i - the value we want
 */
public void
sword_grabbed_flag(int i)
{
    Sword_Grabbed = i;
} /* sword_grabbed_flag */