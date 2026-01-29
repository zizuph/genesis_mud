/*
 *  /d/Emerald/blackwall/delrimmon/visions.c
 *
 *  This module controls the visions which are triggered when a player
 *  touches the crystal formation in the Crystal Tower.
 *
 *  Special thanks to Gnadnar, who assisted in coming up with this
 *  code back in 1997, and also to Shiva, who helped refine it for
 *  implementation into Emerald.
 *
 *  Copyright (c) March 2002, by Cooper Sherry (Gorboth)
 */
#pragma strict_types

#include <files.h>
#include <macros.h>
#include <stdproperties.h>
#include "/d/Emerald/blackwall/delrimmon/defs.h"


#define SHADOW_FILE     (DELRIMMON_DIR + "obj/trance_shadow")

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
public void    unbound_vision(object tp, string catalyst, object paralyze);
public void    bound_vision(object tp, string catalyst, object paralyze);
public void    vamp_vision(object tp, string catalyst, object paralyze);


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
    int     result;

    FIX_EUID
    
    shadow_ob = clone_object(SHADOW_FILE);
    if ((result = shadow_ob->shadow_me(tp->query_real_name())) != 1)
    {
        /* XXX log it? */
        SECURITY->do_debug("destroy", SHADOW_FILE);
    }
    shadow_ob->set_debug(0);    /* XXX */

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
      + " eyes fixed unblinking before " + tp->query_objective());
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

    ENV(tp)->trance_toggle(tp);
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
        if (vision != VAMP_VISION)
        {
            Tell_Stage = 1000;
        }
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
                switch (vision)
                {
                    case VAMP_VISION:
                        Tell_Alarm = set_alarm(1.0, 2.0,
                            &vamp_vision(tp, catalyst, paralyze));
                        break;
                    case UNBOUND_VISION:
                        Tell_Alarm = set_alarm(1.0, 2.0,
                            &unbound_vision(tp, catalyst, paralyze));
                        break;
                    case BOUND_VISION:
                        Tell_Alarm = set_alarm(1.0, 2.0,
                            &bound_vision(tp, catalyst, paralyze));
                        break;
                    case VISION_TEST:
                    default:
                        Tell_Alarm = set_alarm(1.0, 2.0,
                            &vision_test(tp, catalyst, paralyze));
                }
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
            tp->trance_msg("\nAs the images steady themselves, you"
              + " realize that you are looking once more at the"
              + " inside room of the tower, and yet something"
              + " seems different.\n");
            break;
        case 4:
            tp->trance_msg("\nSomeone says: It is good that you"
              + " have come.\n");
            break;
        case 7:
            tp->trance_msg("\nLooking up, you see a tall, red-"
              + "robed elf peering at you from the corner of"
              + " the room. He steps toward you.\n");
            break;
        case 11:
            tp->trance_msg("\nThe tall, red-robed elf introduces"
              + " himself as:\nMaeltar, High Cleric of the Order"
              + " of Telan-Ri, male elf.\n");
            break;
        case 14:
            tp->trance_msg("\nMaeltar says: You have, no doubt,"
              + " been through many trials to find this tower,"
              + " and therefore are proven worthy to become a"
              + " wearer of the Crystal Torque.\n");
            break;
        case 18:
            tp->trance_msg("\nMaeltar says: The enchantment you"
              + " have activated will carry on long after I am"
              + " dead, and so in case things go other than we have"
              + " planned, I will take a moment now to tell you what"
              + " you must know of our purpose.\n");
            break;
        case 23:
            tp->trance_msg("\nMaeltar says: We, the Torque Wearers"
              + " of Emerald are on a sacred quest, ordained by"
              + " Telan-Ri himself, to keep constant vigil against"
              + " the growing forces of Darkness, and the minions"
              + " of Val-Shoreil.\n");
            break;
        case 28:
            tp->trance_msg("\nMaeltar says: The Torque is a holy"
              + " relic, created and sustained by the power of light,"
              + " and the will of Telan-Ri. By his command has it"
              + " come to us, and we do his bidding in keeping it"
              + " as a tool in the hands of the worthy.\n");
            break;
        case 33:
            tp->trance_msg("\nMaeltar says: None but the most trusted"
              + " and valiant servants of the Light must ever be"
              + " entrusted with, or even given knowledge of the"
              + " Torque and its power.\n");
            break;
        case 37:
            tp->trance_msg("\nMaeltar says: With this tool, we may"
              + " look out upon the lands of Emerald, keeping constant"
              + " watch for signs of the darkness which we know is"
              + " growing, moving, and becoming ever more organized."
              + " You now shall join us, and our vigil keep.\n");
            break;
        case 42:
            tp->trance_msg("\nMaeltar smiles at you.\n");
            break;
        case 45:
            tp->trance_msg("\nMaeltar says: One thing remains for you"
              + " to do.\n");
            break;
        case 48:
            tp->trance_msg("\nMaeltar reaches within his robe and"
              + " draws forth a gemstone of some kind. The strange"
              + " light in the room obscures its type, and you are"
              + " not sure of its color. At some angles it glints"
              + " as if it were a ruby, and then at other times it"
              + " appears to be an amethyst, or even a diamond. It"
              + " seems impossible to tell what it might be.\n");
            break;
        case 54:
            tp->trance_msg("\nMaeltar says: I certainly hope you have"
              + " brought a gem!\n");
            break;
        case 56:
            tp->trance_msg("\nMaeltar grins evilly.\n");
            break;
        case 58:
            tp->trance_msg("\nMaeltar moves to the north wall, and feels"
              + " with his fingers along the emblem. He places the"
              + " gem into a socket and the emblem flashes with a"
              + " brilliant and dazzling pulse.\n");
             break;
        case 61:
            tp->trance_msg("\nYou are blinded!\n");
            break;
        case 63:
            tp->trance_msg("\n");
            break;
        case 65:
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
    ENV(TP)->trance_toggle(0);

    if (Tell_Stage)
    {
        Tell_Stage = 1000;
    }
} /* stop_trance */


/*
 * Function name:        unbound_vision
 * Description  :        this vision is granted to players who have
 *                       received a torque, but have not yet
 *                       cast the unification spell upon it
 * Arguments    :        object tp -- the player
 *                       string catalyst -- what triggered the vision,
 *                       object paralyze -- the paralyze object
 */
public void
unbound_vision(object tp, string catalyst, object paralyze)
{
    if (!present(tp, TO))
    {
        Tell_Stage = 1000;
    }

    switch(Tell_Stage)
    {
        case 1:
            tp->trance_msg("\nAs the images steady themselves, you"
              + " realize that you are looking once more at the"
              + " inside room of the tower, and yet something"
              + " seems different.\n");
            break;
        case 4:
            tp->trance_msg("\nSomeone says: Ahh ... very good.\n");
            break;
        case 7:
            tp->trance_msg("\nLooking up, you see a tall, red-"
              + "robed elf peering at you from the corner of"
              + " the room. He steps toward you.\n");
            break;
        case 11:
            tp->trance_msg("\nThe tall, red-robed elf introduces"
              + " himself as:\nMaeltar, High Cleric of the Order"
              + " of Telan-Ri, male elf.\n");
            break;
        case 14:
            tp->trance_msg("\nMaeltar says: Now that you have"
              + " been gifted with the Torque, you must bind it"
              + " to yourself using a Unification enchantment."
              + " Once you have done this, you shall be among"
              + " those who watch over Emerald.\n");
            break;
        case 18:
            tp->trance_msg("\nMaeltar smiles approvingly at"
              + " you.\n");
            break;
        case 21:
            tp->trance_msg("\nMaeltar gestures with his hands,"
              + " and your vision wavers, growing confused as the"
              + " room begins to spin out of focus. As your"
              + " vision returns to normal, he is nowhere to be"
              + " seen.\n");
        case 23:
            tp->trance_msg("\n");
            break;
        case 24:
        case 1000:
            remove_alarm(Tell_Alarm);
            Tell_Alarm = 0;
            Tell_Stage = 0;
            paralyze->stop_paralyze();
            break;
    }

    Tell_Stage++;
    return;
} /* unbound_vision */


/*
 * Function name:        bound_vision
 * Description  :        this is the vision a player will receive
 *                       when they have bound with the torque.
 * Arguments    :        object tp -- the player
 *                       string catalyst -- what triggered the vision,
 *                       object paralyze -- the paralyze object
 */
public void
bound_vision(object tp, string catalyst, object paralyze)
{
    if (!present(tp, TO))
    {
        Tell_Stage = 1000;
    }

    switch(Tell_Stage)
    {
        case 1:
            tp->trance_msg("\nAs the images steady themselves, you"
              + " realize that you are looking once more at the"
              + " inside room of the tower, and yet something"
              + " seems different.\n");
            break;
        case 4:
            tp->trance_msg("\nSomeone says: Welcome, Torque"
              + " Wearer!\n");
            break;
        case 7:
            tp->trance_msg("\nLooking up, you see a tall, red-"
              + "robed elf peering at you from the corner of"
              + " the room. He steps toward you.\n");
            break;
        case 11:
            tp->trance_msg("\nThe tall, red-robed elf introduces"
              + " himself as:\nMaeltar, High Cleric of the Order"
              + " of Telan-Ri, male elf.\n");
            break;
        case 14:
            tp->trance_msg("\nMaeltar says: By binding yourself"
              + " to the Crystal Torque, you now are both master"
              + " of, and subject to its powers.\n");
            break;
        case 18:
            tp->trance_msg("\nMaeltar says: The Torque itself is"
              + " but a vessel of a much greater power, which I"
              + " cannot detail here. By tapping into this power,"
              + " you will be able to keep watch, with your fellow"
              + " Torque Wearers, over the lands of Emerald. To do"
              + " this, use the command <scry> to connect yourself"
              + " to the Inner Sight.\n");
            break;
        case 23:
            tp->trance_msg("\nMaeltar says: You must never use"
              + " this power for any purpose other than to protect"
              + " the Light of Telan-Ri! If it is found that you"
              + " have misused your powers, either myself, or"
              + " one of the remaining Guardians of the Torque"
              + " Wearers will use the incantation of Destruction"
              + " upon your Torque.\n");
            break;
        case 28:
            tp->trance_msg("\nMaeltar says: This spell is powerful,"
              + " and can be used from afar. However, I will teach"
              + " to you now a lesser version of this enchantment,"
              + " should you ever grow weary of your role as a"
              + " Torque Wearer.\n");
            break;
        case 33:
            tp->trance_msg("\nMaeltar says: If you wish to destroy"
              + " your Crystal Torque, and forsake your role among"
              + " us, simply incant 'Aidelnic.' Do not attempt to"
              + " use this spell on others, for I assure you, it"
              + " will not work. Furthermore, once you have left"
              + " the ranks of the Torque Wearers, you may never"
              + " return. The Power of the Torque remembers its"
              + " owners, and does not grant more than one to"
              + " each.\n");
            break;
        case 37:
            tp->trance_msg("\nMaeltar says: Go now. You are"
              + " empowered with the inner sight. Use it to preserve"
              + " Light throughout the lands, and be ever vigilant"
              + " for the encroaching minions of darkness!\n");
            break;
        case 42:
            tp->trance_msg("\nMaeltar peers solemnly at you.\n");
            break;
        case 45:
            tp->trance_msg("\nMaeltar closes his eyes, and appears"
              + " to be concentrating. Suddenly, the gemstones on"
              + " his crystal torque flash with a brilliant and"
              + " overpowering light!\n");
             break;
        case 47:
            tp->trance_msg("\nYou are blinded!\n");
            break;
        case 49:
            tp->trance_msg("\n");
            break;
        case 50:
        case 1000:
            remove_alarm(Tell_Alarm);
            Tell_Alarm = 0;
            Tell_Stage = 0;
            paralyze->stop_paralyze();
            break;
    }

    Tell_Stage++;
    return;
} /* bound_vision */



/*
 * Function name:        vamp_vision
 * Description  :        a vision for vampires at the opening
 *                       of Emerald
 * Arguments    :        object tp -- the player
 *                       string catalyst -- what triggered the vision,
 *                       object paralyze -- the paralyze object
 */
public void
vamp_vision(object tp, string catalyst, object paralyze)
{
    switch(Tell_Stage)
    {
        case 1:
            tp->trance_msg("\nConfusion slams through your"
              + " mind! Darkness swirls about you, narrowing"
              + " into a funnel of chaos. The vortex envelopes"
              + " you, and noises scream in your ears!\n");
            break;
        case 4:
            tp->trance_msg("\nPure chaos thunders around you,"
              + " spinning endlessly in a tornado of darkness."
              + " You feel the presence of God.\n");
            break;
        case 7:
            tp->trance_msg("\nCHILD OF DARKNESS, HEAR ME.\n");
            break;
        case 11:
            tp->trance_msg("\nI AM VAL-SHOREIL, FATHER OF DARKNESS"
              + " AND BRINGER OF HOPE.\n");
            break;
        case 14:
            tp->trance_msg("\nTHE BLOOD OF THE LOST CHILDREN HAS"
              + " BECOME BEREFT OF POTENCY.\n");
            break;
        case 18:
            tp->trance_msg("\nI FEEL THE CONFUSION WITHIN YOU.\n");
            break;
        case 23:
            tp->trance_msg("\nSEEK THE DARKLINGS. SEEK THE ALTAR THEY"
              + " HAVE MADE.\n");
            break;
        case 28:
            tp->trance_msg("\nTHERE YOU WILL FIND YOUR LOST STRENGTH,"
              + " IN WORSHIP TO YOUR GOD.\n");
            break;
        case 34:
            tp->trance_msg("\nSEEK THE ALTAR. FIND AND WORSHIP MY"
              + " PRESENCE!\n");
            break;
        case 36:
            tp->trance_msg("\nDarkness slams into your mind! You"
              + " reel in the midst of torrential chaos!\n");
             break;
        case 38:
            tp->trance_msg("\nYou are blinded!\n");
            break;
        case 40:
            tp->trance_msg("\n");
            break;
        case 41:
        case 1000:
            remove_alarm(Tell_Alarm);
            Tell_Alarm = 0;
            Tell_Stage = 0;
            paralyze->stop_paralyze();
            break;
    }

    Tell_Stage++;
    return;
} /* bound_vision */
    
