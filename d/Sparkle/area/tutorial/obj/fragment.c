/*
 *  /d/Sparkle/area/tutorial/obj/fragment.c
 *
 *  This is the missing piece of Krolock's statue that can be found
 *  in the desk in his study. Location:
 *
 *    /d/Sparkle/area/tutorial/castle/study.c
 *
 *  Created August 2004, by Cooper Sherry (Gorboth)
 */
#pragma strict_types

inherit "/std/object";

#include <stdproperties.h>
#include "../defs.h"

/* global variables */
public string      Part;    /* what part of the statue is this? */

/* prototypes */
public void        create_object();
public void        configure_fragment(object player);
public void        leave_env(object from, object to);
public void        init();
public int         do_connect(string arg);

public string      query_part() { return Part; }

/*
 * Function name:        create_object
 * Description  :        set up the object
 */
public void
create_object()
{
    set_name("fragment");
    add_name( ({ "_tutorial_fragment", "_tutorial_item" }) );

    add_adj( ({ "white", "stone" }) );
    set_short("white stone fragment");

    add_prop(OBJ_M_NO_GIVE, "You'd better hang on to it.\n");
    add_prop(OBJ_I_WEIGHT, 10);
    add_prop(OBJ_I_VOLUME, 7);
} /* create_object */


/*
 * Function name:        configure_fragment
 * Description  :        set up the properties of the fragment
 * Arguments    :        player - the player object
 */
public void
configure_fragment(object player)
{
    switch(strlen(player->query_real_name()))
    {
        case 2:
            Part = "foot";
            break;
        case 3:
            Part = "thumb";
            break;
        case 4:
            Part = "nose";
            break;
        case 5:
            Part = "ear";
            break;
        case 6:
            Part = "hand";
            break;
        case 7:
            Part = "mouth";
            break;
        case 8:
            Part = "toe";
            break;
        case 9:
            Part = "finger";
            break;
        case 10:
            Part = "tooth";
            break;
        case 11:
        default:
            Part = "eye";
            break;
    }

    set_long("This piece of white stone has been expertly carved. It"
      + " is only a fragment though, and appears to have been part of"
      + " a larger object which you could probably <connect> it to"
      + " if you discovered where it belonged.\n");
} /* configure_fragment */


/*
 * Function name:        leave_env
 * Description  :        we don't want these piling up anywhere, so we
 *                       have them vanish if the player drops them
 * Arguments    :        object from - where it came from
 *                       object to   - where it went
 */
public void
leave_env(object from, object to)
{
    ::leave_env(from, to);

    if (!objectp(from) || !objectp(to) || !living(from))
        return;

    if (!to->query_prop(ROOM_I_IS))
    {
        return;
    }

    tell_room(to, "The " + this_object()->short() + " falls to the"
      + " ground and vanishes in a flash of light.\n");
    set_alarm(0.0, 0.0, "remove_object");
} /* leave_env */


/*
 * Function name:        init
 * Description  :        add some actions to the player
 */
public void
init()
{
    ::init();

    add_action(do_connect, "connect");
} /* init */


/*
 * Function name:        do_connect
 * Description  :        allow the player to try to connect the
 *                       fragment to things.
 * Arguments    :        stringa arg - what was typed after the verb
 * Returns      :        1 - success, 0 - otherwise.
 */
public int
do_connect(string arg)
{
    object  obj;

    if (!strlen(arg))
    {
        notify_fail("Connect what?\n");
        return 0;
    }

    if (!parse_command(arg, all_inventory(this_player()),
        "[the] %o 'to' / 'with' [the] [statue] '" + Part + "'"
      + " [of] [the] [statue]", obj))
    {
        if (parse_command(arg, all_inventory(this_player()),
        "[the] %o 'to' / 'with' [the] 'statue'", obj))
        {
            if (!CHECK_TUTORIAL_BIT(FRAGMENT_BIT))
            {
                notify_fail("You have no idea what part of the"
                  + " statue the fragment might connect to.\n");
            }
            else
            {
                notify_fail("What part of the statue do you want to"
                  + " connect the fragment to?\n");
            }
            return 0;
        }

        notify_fail("Connect what to what?\n");
        return 0;
    }

    if (obj != this_object())
    {
        return 0;
    }

    if (!environment(this_player())->id("_tutorial_krolock_statue"))
    {
        notify_fail("You don't see anything to connect it to here.\n");
        return 0;
    }

    if (CHECK_TUTORIAL_BIT(STATUE_BIT))
    {
        write("You have already moved the statue.\n");
        return 1;
    }

    if (!CHECK_TUTORIAL_BIT(FRAGMENT_BIT))
    {
        write("Hmmm ... yes, this fragment does look quite similar"
          + " to the stone of the statue. It isn't immediately"
          + " obvious where it belongs, however. You'd need to do"
          + " some further investigation to see where it might"
          + " connect.\n");
        return 1;
    }

    write("You replace the " + Part + " of the statue. Instantly, the"
      + " materials meld together, and the eyes of the statue begin"
      + " to glow red. A hideously loud grinding noise erupts as the"
      + " statue begins to slide slowly across the floor, revealing"
      + " spiral steps which descend into darkness!\n");
    SET_TUTORIAL_BIT(STATUE_BIT);
    set_alarm(0.5, 0.0, "remove_object");
    return 1;
} /* do_connect */
