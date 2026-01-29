/*
 *  /d/Sparkle/area/tutorial/pre_creation_new/10.c
 *
 *  This is the final room in the pre-creation tutorial. It teaches
 *  people about the upcoming tutorial signs, and instructs them to
 *  begin the creation process.
 *
 *  Created May 2011, by Cooper Sherry (Gorboth)
 */
#pragma strict_types
#include "../defs.h"
#include "/d/Genesis/start/newbie/newbie.h"

inherit "/std/room";
inherit LIB_DIR + "instance";
inherit LIB_DIR + "skip";

#include <login.h>
#include <macros.h>
#include <stdproperties.h>

#define         SURVEY_CHECK     "_tutorial_survey_check"


/* prototypes */
public void        create_room();
public void        first_message(object who);
public void        new_descs();
public void        enter_inv(object ob, object from);
public int         catch_all(string str);
public int         init();
public void        summon_portal(object who);
public void        open_portal(object who);
public int         do_enter(string arg);
public string      exa_portal();
public int         try_survey(object player);
public int         start_survey(string arg);

/* global variables */
public int         Tell_Alarm;
public int         Sign_Read = 0;
public int         Portal = 0;


/*
 * Function name:        create_room
 * Description  :        set up the room
 */
public void
create_room()
{
    set_name("10");
    set_short("You find yourself in a glowing chamber, surrounded"
      + " by a feeling of warmth and safety");
    set_long(capitalize(short()) + ".\n\n");

    add_prop(ROOM_M_NO_TELEPORT,
        "A strange force prevents your travel.\n");
    add_prop(ROOM_I_INSIDE, 1);

    add_item( ({ "chamber", "room", "here", "warmth",
                 "safety", "feeling", "feeling of warmth",
                 "feeling of safety",
                 "feeling of warmth and safety" }),
        "A feeling of warmth and safety descends on you here.\n");
    add_item( ({ "portal", "blue portal", "shimmering portal",
                 "shimmering blue portal" }),
        "@@exa_portal@@");

    room_add_object("/d/Sparkle/area/tutorial/pre_creation_new/sign");

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

    if (present("survey", who))
    {
        return;
    }

    if (Portal)
    {
        who->catch_tell(one_of_list( ({
            "\nYou feel called to <enter> the portal.\n",
            "\nA friendly voice whispers: Do not be afraid, my friend."
          + " You may <enter> the portal whenever you feel ready.\n",
            "\nA warm feeling descends on you, and you feel ready"
          + " to <enter> the portal.\n" }) ) );
    }
    else
    {
        who->catch_tell(one_of_list( ({
            "\nYou notice a sign here that you could <read>.\n",
            "\nThe sign here looks interesting. Perhaps you should"
          + " <read> it?\n",
            "\nA warm feeling descends on you, and your attention is"
          + " drawn to a sign you could <read> if you wished.\n" }) ) );
    }

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
    set_short("you find yourself in a glowing chamber, surrounded"
      + " by a feeling of warmth and safety. A shimmering blue portal"
      + " has appeared, beckoning you to <enter>");
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
        case "commune":
        case "get":
        case "wield":
        case "unwield":
        case "take":
        case "pick":
        case "skip":
        case "i":
        case "inventory":
        case "search":
        case "read":
        case "enter":
        case "survey":
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
    add_action(do_enter, "enter");
    add_action(start_survey, "survey");
} /* init */


/*
 * Function name:        summon_portal
 * Description  :        bring a portal into existance here
 * Arguments    :        object who - the player
 */
public void
summon_portal(object who)
{
    if (Portal)
    {
        return;
    }

    new_descs();
    set_alarm(3.0, 0.0, &open_portal(who));
    return;
} /* summon_portal */


/*
 * Function name:        open_portal
 * Description  :        The portal opens for the player to use
 * Arguments    :        object who - the player
 */
public void
open_portal(object who)
{
    if (Portal)
    {
        return;
    }

    who->catch_tell("\nA shimmering blue portal rises from the ground!\n");

    Portal = 1;
    return;
} /* open_portal */


/*
 * Function name:        do_enter
 * Description  :        Allow players to begin the character creation
 *                       process
 * Arguments    :        string arg - what the player typed
 * Returns      :        int 1 - success, 0 - failure
 */
public int
do_enter(string arg)
{
    if (!Portal)
    {
        notify_fail("You do not seem to be able to do that yet.\n");
        return 0;
    }

    notify_fail("Do you wish to <enter portal>?\n");

    if (!strlen(arg))
    {
        return 0;
    }

    if (!parse_command(arg, ({}),
        "[the] [blue] [shimmering] 'portal'"))
    {
        return 0;
    }

    if (try_survey(this_player()))
    {
        return 1;
    }

    write_file(LOG_DIR + "moves", ctime(time())
      + " " + this_player()->query_name() + " **entered** the portal.\n");

 
    write("You step through the portal, and feel yourself magically"
      + " transported.\n\n");
    this_player()->move_living("M", TUTORIAL_DIR + "town/hilltop", 1, 0);
    tell_room(environment(this_player()), QCTNAME(this_player())
      + " appears through the shimmering blue portal!\n", this_player());
    return 1;

} /* do_enter */


/*
 * Function name:        exa_portal
 * Description  :        allow players to examine the portal
 * Returns      :        a description of the portal if it exists
 */
public string
exa_portal()
{
    if (!Portal)
    {
        return "You find no such thing.\n";
    }

    return "A shimmering blue portal has risen from the ground. You can"
      + " <enter portal> whenever you feel ready.\n";
} /* exa_portal */


/*
 * Function name:        try_survey
 * Description  :        attempt to get the player to take the new
 *                       player survey
 * Arguments    :        object who - the player
 * Returns      :        int 1 - the player hasn't yet been asked
 *                       int 0 - the player has been asked
 */
public int
try_survey(object who)
{
    if (who->query_prop(SURVEY_CHECK))
    {
        return 0;
    }

    who->catch_tell("\nAh, but first, please take 60 seconds to complete"
      + " our new-player survey. You'll be given gold for your time! To"
      + " do so, just type <survey> now.\n\nOr, if you prefer, you can"
      + " just enter the portal ... your choice.\n\n");

    who->add_prop(SURVEY_CHECK, 1);

    return 1;
} /* try_survey */


/*
 * Function name:        start_survey
 * Description  :        allow the player to start the survey
 * Arguments    :        string arg - what was typed
 * Returns      :        int 1 - success, 0 - failure
 */
public int
start_survey(string arg)
{
    object  ob;

    if (present("survey", this_player()))
    {
        notify_fail("You've already started the survey.\n");
        return 0;
    }

    write("\nWonderful! We very much appreciate your answers!\n\n");

    ob = clone_object("/d/Genesis/census/survey/survey");
    ob->move(this_player());

    return 1;
} /* start_survey */