/*
 *  /d/Sparkle/area/tutorial/pre_creation_new/1.c
 *
 *  This is the pre-creation room that teaches players how to look at
 *  their environment.
 *
 *  Created May 2011, by Cooper Sherry (Gorboth)
 */
#pragma strict_types
#include "../defs.h"
#include "/d/Genesis/start/newbie/newbie.h"

inherit "/std/room";
inherit LIB_DIR + "skip";

#include <macros.h>
#include <stdproperties.h>

/* definitions */
#define            TOLD_TO_LOOK   "_pre_creation_told_to_look"

/* prototypes */
public void        create_room();
public void        first_message(object who);
public void        second_message(object who);
public void        third_message(object who);
public void        fourth_message(object who);
public void        fifth_message(object who);
public void        transfer(object who);
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
    set_name("1");
    set_short("utter darkness ... Void ... Stretching endlessly toward"
      + " nothing ...");
    set_long("\n" + capitalize(short()) + ".\n");

    add_prop(ROOM_M_NO_TELEPORT,
        "A strange force prevents your travel.\n");
    add_prop(ROOM_I_INSIDE, 1);

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

    who->catch_tell("\nA friendly voice says: Welcome, traveller."
    + " If you wish you can at any time leave this tutorial with"
    + " the command <skip tutorial>.\n");
    set_alarm(4.0, 0.0, &second_message(who));

    set_short("your eyes are having trouble focusing yet. You try to"
      + " blink a few times, as odd sensations wash over you");
    set_long("Your eyes are having trouble focusing yet. You try to"
      + " blink a few times, as odd sensations wash over you.\n");

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

    who->catch_tell("\nAt the sound of the voice, your mind seems to awaken,"
      + " and your awareness spreads out, searching for meaning in the"
      + " void.\n");
    set_alarm(7.0, 0.0, &third_message(who));

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

    who->catch_tell("\nA friendly voice says: You have eyes, my friend!"
      + " Use them!\n");
    Tell_Alarm = set_alarm(5.0, 0.0, &fourth_message(who));

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

    who->catch_tell("\nType <look> or simply <l>"
      + " to use your eyes.\n");

    who->add_prop(TOLD_TO_LOOK, 1);

    Tell_Alarm = set_alarm(15.0, 0.0, &fifth_message(who));

    return;
} /* fourth_message */


/*
 * Function name:        fifth_message
 * Description  :        fifth message for the player
 * Arguments    :        object who - the player
 */
public void
fifth_message(object who)
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
        "\nA friendly voice says: Don't be afraid, you can <look> with your"
      + " eyes. Typing <l> will also work.\n",
        "\nYou may type <l> or <look> at any time.\n",
        "\nTo see where you are, simply type <look> or <l> to use your"
      + " eyes.\n" }) ) );

    Tell_Alarm = set_alarm(20.0, 0.0, &fifth_message(who));

    return;
} /* fifth_message */


/*
 * Function name:        transfer
 * Description  :        move the player to the new room
 * Arguments    :        object who - the player
 */
public void
transfer(object who)
{
    object  room = clone_object(
        "/d/Sparkle/area/tutorial/pre_creation_new/2");

    who->move_living("M", room);

    remove_alarm(Tell_Alarm);
    log_move("2");

    set_alarm(1.0, 0.0, &remove_object());
    return;
} /* transfer */


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

    find_object("/w/gorboth/workroom")->tell_gorboth(
        capitalize(this_player()->query_real_name()) + " enters the"
      + " pre-creation! <---!!!\n");
    set_alarm(5.0, 0.0, &first_message(ob));
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
        case "quit":
        case "commune":
        case "skip":
            return 0;
            break;
        case "look":
        case "l":
            if (!this_player()->query_prop(TOLD_TO_LOOK))
            {
                return 0;
            }

            set_alarm(0.0, 0.0, &transfer(this_player()));
            return 1;
            break;
        default:
            write("Your mind is still coming to grips with things."
              + " Apparently, you aren't able to do much now other than"
              + " wait and learn.\n");
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