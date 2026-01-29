/*
 *  /d/Sparkle/area/tutorial/pre_creation_new/2.c
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

/* definitions */
#define            TOLD_TO_WALK   "_pre_creation_told_to_walk"

/* prototypes */
public void        create_room();
public void        first_message(object who);
public void        second_message(object who);
public void        third_message(object who);
public void        fourth_message(object who);
public void        enter_inv(object ob, object from);
public int         catch_all(string str);
public int         init();
public void        new_descs();

/* global variables */
public int         Tell_Alarm;


/*
 * Function name:        create_room
 * Description  :        set up the room
 */
public void
create_room()
{
    set_name("2");
    set_short("your eyes suddenly blink into focus, and you see many vapours"
      + " and colours swirling around you. The images settle into a"
      + " cloud-like room in which you stand with one clear path"
      + " forward");
    set_long(capitalize(short()) + ".\n\n");

    add_prop(ROOM_M_NO_TELEPORT,
        "A strange force prevents your travel.\n");
    add_prop(ROOM_I_INSIDE, 1);

    set_instance_entrance(1);

    add_exit("3", "north", &log_move("3"), 1, 0);

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

    who->catch_tell("\nA friendly voice says: It seems your eyes are"
      + " working perfectly, so let's move on to your legs.\n");
    set_alarm(7.0, 0.0, &second_message(who));

    set_short("you are standing in a cloud-like room with only one clear"
      + " path forward");
    set_long("You are standing in a cloud-like room with only one clear"
      + " path forward.\n\n");

    return;
} /* first_message */


/*
 * Function name:        second_message
 * Description  :        second message for the  player
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

    who->catch_tell("\nThe \"obvious exits\" that you see when you"
      + " type <look> tell you what directions you can travel. To use"
      + " your legs, type <north> or simply <n> to move around.\n");

    who->add_prop(TOLD_TO_WALK, 1);

    Tell_Alarm = set_alarm(15.0, 0.0, &third_message(who));

    return;
} /* second_message */


/*
 * Function name:        third_message
 * Description  :        third message for the  player
 * Arguments    :        object who - the player
 */
public void
third_message(object who)
{
    if (!objectp(who))
    {
        return;
    }

    if (environment(who) != this_object())
    {
        return;
    }

    who->catch_tell("\nA friendly voice says: Your legs need prompting,"
      + " so type <north> or <n> to move forward.\n");
    Tell_Alarm = set_alarm(15.0, 0.0, &fourth_message(who));

    return;
} /* third_message */


/*
 * Function name:        fourth_message
 * Description  :        fourth message for the player
 * Arguments    :        object who - the player
 */
public void
fourth_message(object who)
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
        "\nYou may type <l> or <look> at any time. Then, type in one of"
      + " the obvious exits to move around - <north> for example.\n",
        "\nTo see where you are, simply type <look> or <l> to use your"
      + " eyes, and then follow one of the obvious exits.\n" }) ) );

    Tell_Alarm = set_alarm(20.0, 0.0, &fourth_message(who));

    return;
} /* fourth_message */


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
            if (!this_player()->query_prop(TOLD_TO_WALK))
            {
                write("You aren't sure how to do that yet.\n");
                return 1;
            }

            return 0;
            break;
        case "quit":
        case "look":
        case "l":
        case "commune":
        case "skip":
            return 0;
            break;
        default:
            write("Your mind is still coming to grips with things."
              + " Apparently, you aren't able to do much now other than"
              + " look and learn.\n");
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


/*
 * Function name:      new_descs
 * Description  :      change the descs once the player has already 
 *                     seen them.
 */
public void
new_descs()
{
    set_short("you are standing in a cloud-like room with only one clear"
      + " path forward");
    set_long(capitalize(short()) + ".\n\n");
} /* new_descs */