#pragma strict_types

#include <files.h>
#include <macros.h>
#include <stdproperties.h>
#include "/d/Emerald/blackwall/delrimmon/defs.h"
#include "/d/Emerald/blackwall/delrimmon/defs.h"


#define	SHADOW_FILE	(DELRIMMON_DIR + "obj/trance_shadow")

/* global variables */
public int    Tell_Alarm,
              Tell_Stage = 0;

/* prototypes */
public void    trance_paralyze(object tp, string catalyst);
public void    enter_trance(object tp, string vision, string catalyst);
public void    trigger_vision(object tp, string vision, string catalyst, object
paralyze);
public void    vision_test(object tp, string catalyst, object paralyze);
public void    stop_trance();


/*
 * Function name:        trance_paralyze
 * Description  :        add a paralysis to the player, for the
 *                       length of time this trance takes.
 * Returns      :        the paralyze object
 */
public object
trance_paralyze(object tp, string catalyst)
{
    object  paralyze, shadow_ob;
    int	    result;

    FIX_EUID
    
    shadow_ob = clone_object(SHADOW_FILE);
    if ((result = shadow_ob->shadow_me(tp->query_real_name())) != 1)
    {
	/* XXX log it? */
        SECURITY->do_debug("destroy", SHADOW_FILE);
    }
    shadow_ob->set_debug(1);	/* XXX */

    paralyze = clone_object("/std/paralyze");
    paralyze->set_stop_verb("wake");
    paralyze->set_stop_fun("stop_trance");
    paralyze->set_stop_object(TO);
    paralyze->set_stop_message("You snap out of the trance, and back away"
                             + " from the " + catalyst + ".\n");
    paralyze->set_fail_message("You are in a trance, and cannot perform"
                             + " actions right now. You must 'wake' to"
                             + " do something else.\n");
    paralyze->move(tp, 1);
    tp->add_prop(LIVE_S_SOULEXTRA,
        "standing perfectly still with " + tp->query_possessive()
      + " eyelids closed");
    tp->add_prop(OBJ_M_NO_ATTACK,
        "A strange force stays your hand.\n");
    ENV(tp)->add_prop(ROOM_M_NO_STEAL,
        "A strange force prevents that here.\n");

    return paralyze;
} /* trance_paralyze */


/*
 * Function name:        enter_trance
 * Description  :        sets up the trance paralysis for the player
 * Arguments    :        object tp -- the player,
 *                       string vision -- the vision name,
 *                       string catalyst -- what triggered the vision
 */
public void
enter_trance(object tp, string vision, string catalyst)
{
    object  paralyze;

    tp->catch_msg("Your body stiffens as you touch the " + catalyst
      + " and the world around you seems to suddenly fade.\n");
    tell_room(ENV(tp), QCTNAME(tp) + " stiffens suddenly, and appears"
      + " to have entered a some kind of trance.\n", tp);

    paralyze = trance_paralyze(tp, catalyst);

    if (!Tell_Alarm || !sizeof(get_alarm(Tell_Alarm)))
    {
        Tell_Alarm = set_alarm(1.0, 2.0,
                       &trigger_vision(tp, vision, catalyst, paralyze));
    }
} /* enter_trance */



/*
 * Function name:        trigger_vision
 * Description  :        triggers the particular vision the player
 *                       will experience.
 * Arguments    :        object tp -- the player,
 *                       string vision -- the vision name,
 *                       string catalyst -- what triggered the vision,
 *                       object paralyze -- the paralyze object
 */
public void
trigger_vision(object tp, string vision, string catalyst, object paralyze)
{
    if (!present(tp, TO))
    {
        Tell_Stage = 1000;
    }

    switch(Tell_Stage)
    {
        case 0:
            tp->trance_msg("\n");
            break;
        case 2:
            tp->trance_msg("As your mind relaxes, your eyelids close.\n");
            break;
        case 3:
            tp->trance_msg("\n");
            break;
        case 4:
            tp->trance_msg("The feeling in your own body departs from"
                        + " you, and you drift into a trance.\n");
            break;
        case 6:
            tp->trance_msg("\n");
            break;
        case 8:
            tp->trance_msg("\n");
            break;
        case 9:
            tp->trance_msg("Images and sounds begin to slowly unfold"
                        + " in your mind.\n");
            break;
        case 11:
            tp->trance_msg("\n");
            break;
        case 13:
        case 999:
            remove_alarm(Tell_Alarm);
            Tell_Alarm = 0;
            Tell_Stage = 0;

            if (!Tell_Alarm || !sizeof(get_alarm(Tell_Alarm)))
            {
                Tell_Alarm = set_alarm(1.0, 2.0,
                       &vision_test(tp, catalyst, paralyze));
            }

            break;
        case 1000:
            remove_alarm(Tell_Alarm);
            Tell_Alarm = 0;
            Tell_Stage = 0;
            paralyze->stop_paralyze();
            break;
        default:
            break;
    }

    Tell_Stage++;
    return;
} /* trigger_vision */



/*
 * Function name:        vision_test
 * Description  :        sets up a pattern of tells for the player,
 *                       but this is only a test
 * Arguments    :        object tp -- the player
 *                       string catalyst -- what triggered the vision,
 *                       object paralyze -- the paralyze object
 */
public void
vision_test(object tp, string catalyst, object paralyze)
{
    if (!present(tp, TO))
    {
        Tell_Stage = 1000;
    }

    switch(Tell_Stage)
    {
        case 1:
            tp->trance_msg("You drift slowly forward through"
              + " a dark tunnel, surrounded by stony walls on all"
              + " sides.\n");
            break;
        case 3:
            tp->trance_msg("\nThe tunnel falls away, and you enter into"
              + " the center of a large chamber with a high vaulted"
              + " ceiling.\n");
            break;
        case 5:
            tp->trance_msg("\nA pale, stone-faced human arrives from"
              + " the shadows.\n");
            break;
        case 8:
            tp->trance_msg("\nThe pale, stone-faced human intones:"
              + " I have found you, " + CAP(tp->query_real_name())
              + ".\n");
            break;
        case 10:
            tp->trance_msg("\nThe pale, stone-faced human leaves"
              + " north.\n");
            break;
        case 11:
            tp->trance_msg("\nYou follow, drifting north, through a"
              + " doorway in the cave wall.\n");
            break;
        case 13:
            tp->trance_msg("\nYou have entered a carefully carved"
              + " tunnel which runs to the east and west. The"
              + " pale, stone-faced human stands directly before"
              + " you here.\n");
            break;
        case 16:
            tp->trance_msg("\nThe pale, stone-faced human points to an"
              + " emblem of a tree surmounted by seven stars all"
              + " within a circular band which has been carved upon"
              + " the northern wall face.\n");
            break;
        case 19:
            tp->trance_msg("\nThe pale, stone-faced human says: It is"
              + " now you who must search for me.\n");
            break;
        case 21:
            tp->trance_msg("\n");
            break;
        case 23:
        case 1000:
            remove_alarm(Tell_Alarm);
            Tell_Alarm = 0;
            Tell_Stage = 0;
            paralyze->stop_paralyze();
            break;
    }

    Tell_Stage++;
    return;
} /* vision_test */


/*
 * Function name:        stop_trance
 * Description  :        this is called when the paralyze ends in
 *                       the player
 */
public void
stop_trance()
{
    object shadow;

    if (objectp(shadow = TP->query_trance_shadow()))
    {
	shadow->remove_shadow();
    }

    WRITE("You blink a few times, and become again aware of your normal"
      + " senses.");
    tell_room(ENV(TP), QCTNAME(TP) + " blinks a few times, and seems"
      + " to come out of " + TP->query_possessive() + " trance.\n", TP);
    TP->add_prop(LIVE_S_SOULEXTRA, "peering thoughtfully around");
    TP->add_prop(OBJ_M_NO_ATTACK);
    ENV(TP)->remove_prop(ROOM_M_NO_STEAL);

    if (Tell_Stage)
    {
        Tell_Stage = 1000;
    }
} /* stop_trance */
