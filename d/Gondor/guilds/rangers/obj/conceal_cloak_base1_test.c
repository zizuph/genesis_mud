/*
 * /d/Gondor/guilds/rangers/obj/conceal_cloak_base.c
 * The base code for the cloaks of the Rangers of the North
 * By Rastlin.
 *   Modification Log:
 *     Elessar, 1998.
 *     Alto, February 2002. Adapted for ranger recode.
 *                          Generalize for use by Ithilien and North
 *                          Add close/open hood for true anonymity
 *     Tigerlily, August 8, 2004: made keepable
 *                Dec. 29, 2004:  Added functions to pin and mask cloak
 *                          specific for the mottled version of
 *                          the cloak--for brown, grey, grey-green
 *                          versions, see the classic cloak_base.c
 *     Varian, June 2021    Added the function remove_cloak_shadow
 *                          since the cloak removed other shadows by
 *                          accident
 */
inherit "/std/object";
inherit "/lib/wearable_item";
inherit "/lib/keep.c";
inherit "/cmd/std/command_driver";
inherit "/std/shadow";

#include "/d/Gondor/defs.h"
#include "/d/Gondor/guilds/rangers/rangers.h"

#include <cmdparse.h>
#include <formulas.h>
#include <macros.h>
#include <state_desc.h>
#include <stdproperties.h>
#include <wa_types.h>

#define RANGERS_MASK_CLOSED    "_rangers_mask_closed"
#define RANGERS_I_INCOGNITO    "_rangers_incognito"
#define RANGERS_AS_KNOWN       "_rangers_as_known"
#define RANGER_I_WEARING_CLOAK "_ranger_i_wearing_cloak"
#define RANGER_I_PINNED_CLOAK  "_ranger_i_pinned_cloak"
#define RANGER_I_EXTRA         "_ranger_i_extra"

object gShadow = 0;
string gColour = "brown";
int    gMoreSneak = 0, gMoreHide = 0, gMoreAwareness = 0;


/* Prototypes */
void set_colour(string str);

public void
create_robe()
{
    set_colour("grey");
}

public void
remove_cloak_shadow()
{
    remove_shadow();
}

public nomask void
create_object()
{
    create_robe();

    set_wf(TO);
    seteuid(getuid());

    set_slots(A_ROBE);
    /* This looseness allows the cloak to be worn over other cloaks
       of standard layers of 4. These layers make sure that one
       can't wear two ranger cloaks at the same time. */
    set_looseness(20);
    set_layers(1);
    set_keep(1);

    add_prop(OBJ_I_VOLUME, 400);
    add_prop(OBJ_I_WEIGHT, 300);
    add_prop(OBJ_I_VALUE, 44);
}

/*
 * Function name: wear
 * Description  : Called from the armour when worn
 * Arguments    : what - The object worn.
 * Returns      : True if it went ok, a string or -1 otherwise
 */
public mixed
wear(object what)
{
    if (what != TO)
        return -1;

    if (TP->query_prop(RANGER_I_WEARING_CLOAK))
        return "You cannot wear two Ranger cloaks at once.\n";

    write("You wrap the " + short() + " around your shoulders.\n");
    say(QCTNAME(TP) + " wears " + LANG_ADDART(short()) + ".\n");
    TP->add_prop(RANGER_I_WEARING_CLOAK, 1);
    return 1;
}

/* Function name: fix_skills
 * Description  : Removes extra skills, prop and hood shadow
 *                This should be called in any function that
 *                might open their hood. It won't remove too
 *                many skills, even if called twice.
 */ 
public void
fix_skills(object tp)
{
    if (tp->query_prop(RANGER_I_EXTRA))
    {
        // don't remove more than the current extra skill
        if (tp->query_skill_extra(SS_SNEAK) < gMoreSneak)
            gMoreSneak = tp->query_skill_extra(SS_SNEAK);
        if (tp->query_skill_extra(SS_HIDE) < gMoreHide)
            gMoreSneak = tp->query_skill_extra(SS_HIDE);
        if (tp->query_skill_extra(SS_AWARENESS) < gMoreAwareness)
            gMoreSneak = tp->query_skill_extra(SS_AWARENESS);

        tp->set_skill_extra(SS_SNEAK,
            (tp->query_skill_extra(SS_SNEAK) - gMoreSneak));
        tp->set_skill_extra(SS_HIDE,
            (tp->query_skill_extra(SS_HIDE) - gMoreHide));
        tp->set_skill_extra(SS_AWARENESS,
            (tp->query_skill_extra(SS_AWARENESS) - gMoreAwareness));
        gMoreSneak = 0;
        gMoreHide = 0;
        gMoreAwareness = 0;
        tp->remove_prop(RANGER_I_EXTRA);
    }
    tp->remove_prop(RANGERS_MASK_CLOSED);
    return;
}

/*
 * Function name: remove
 * Description  : Called when the robe is removed
 * Arguments    : what - The object being removed
 * Returns      : False or -1.
 */
public mixed
remove(object what)
{
    object tp = this_player();

    if (what != TO)
        return -1;
    // restore player
    gShadow->remove_cloak_shadow();
    gShadow = 0;
    tp->remove_prop(RANGER_I_WEARING_CLOAK);
    tp->remove_prop(RANGER_I_PINNED_CLOAK);
    this_object()->remove_prop(OBJ_M_NO_DROP);
    fix_skills(tp);
    return 0;
}

/*
 * Function name: hood_player
 * Description  : This will put on the hood for the player. Make sure all
 *                the tests are done before calling this function.
 * Arguments    : player - The player object
 */
public void
hood_player(object player)
{

    gShadow = clone_object(RANGERS_OBJ + "conceal_shadow.c");
    gShadow->set_colour(gColour);
    gShadow->shadow_me(player);
    this_object()->add_prop(OBJ_M_NO_DROP, "You are unable to drop " +
        LANG_THESHORT(this_object()) + " while you are hooded. You must " +
        "unhood yourself first.\n");
    player->add_prop(RANGERS_I_INCOGNITO, 1);
}

/*
 * Function name: wear_hood
 * Description  : Wear the hood.
 * Arguments    : str - The proper string to wear the hood.
 * Returns      : True or false.
 */
public int
wear_hood(string str)
{
    object tp = this_player();
    string name = tp->query_real_name();

    /* Syntax is 'wear hood' or 'hood me/myself/name' */
    if (!str || !strlen(str) || 
      (str != "hood" && query_verb() == "wear") ||
      (str != "me" && str != "myself" && str != name && query_verb() == "hood"))
    {
        notify_fail("Hood me?\n");
        return 0;
    }

    if ((query_worn() != tp))
    {
        notify_fail("You are not wearing a cloak!\n");
        return 0;
    }

    if (gShadow)
    {
        notify_fail("You are already wearing the hood!\n");
        return 0;
    }

    if ((!RANGERS_MEMBER(tp)) && (!tp->query_wiz_level()))
    {
        write("The hood does not fit well enough to stay on your head.\n");
        return 1;
    }

    write("You pull the hood of your cloak low down over your face. You " +
        "feel that you could 'reveal yourself to someone' if you were " +
        "hidden.\n");
    if (RANGERS_FULL_MEMBER(tp))
         write("You may also 'mask myself' or 'pin cloak' " +
        "to obscure your appearance further from onlookers.\n");
    if (RANGERS_FULL_MEMBER(tp))
        write("You can 'unhood me' to remove your hood.\n");
    say(QCTNAME(tp) + " pulls " + tp->query_possessive() +
        " hood over " + tp->query_possessive() + " head, hiding " +
        tp->query_possessive() + " face.\n");

    hood_player(tp);

    return 1;
}

/*
 * Function name: remove_hood
 * Description:   Remove the worn hood.
 * Arguments:     str - The proper string to remove the hood.
 * Returns:       True or false.
 */
public int
remove_hood(string str)
{
    string name;
    object tp = this_player();

    name = tp->query_real_name();
    if (!strlen(str) ||
      (str != "me" && str != "myself" && str != tp->query_real_name()))
    {
        notify_fail("Unhood me?\n");
        return 0;
    }

    if ((query_worn() != tp))
    {
        notify_fail("You are not wearing a cloak!\n");
        return 0;
    }

    if (!gShadow)
    {
        notify_fail("You are not wearing your hood.\n");
        return 0;
    }
    fix_skills(tp);
    write("You remove the hood, and once again reveal your face.\n");
    tp->remove_prop(RANGERS_I_INCOGNITO);
    tp->remove_prop(RANGER_I_PINNED_CLOAK);
    this_object()->remove_prop(OBJ_M_NO_DROP);
    gShadow->remove_cloak_shadow();
    gShadow = 0;

    say(QCTNAME(tp) + " removes " + tp->query_possessive() + " hood and " +
        "flings back the cloak, revealing " + tp->query_objective() +
        "self.\n");


    return 1;
}

/*
 * Function name: mask_me
 * Description  : Close the mask and hood so that you become anonymous.
 * Arguments    : str - The proper string to wear the hood.
 * Returns      : True or false.
 */
public int
mask_me(string str)
{
    object tp = this_player();

    if (!strlen(str) || (str != "me" && str != "myself"))
        return 0;

    if (query_worn() != tp)
        return 0;

    if (!gShadow)
        return 0;

    if (tp->query_prop(RANGERS_MASK_CLOSED) || 
      (!RANGERS_FULL_MEMBER(tp) && !tp->query_wiz_level()))
    {
        write("The mask cannot be closed further.\n");
        return 1;
    }

    write("You draw the hood and mask so close about your face that even " +
        "your own mother would take you for a stranger. You " +
        "feel that you could 'identify yourself to someone' who you " +
        "know if you wanted them to recognize you. You can 'unmask me' " +
        "to reveal more of your face again.\n");
    say(QCTNAME(tp) + " draws " + tp->query_possessive() +
        " cloak and hood as close as possible about " +
        tp->query_possessive() + " head and body.\n");
    gMoreSneak = 0;
    gMoreHide = 0;
    gMoreAwareness = 0;
// RoN have increased sneak skills associated with closing hood
// and are taxed accordingly for this object--see tax docs
    if (NORTH_MEMBER(tp) && !tp->query_prop(RANGER_I_EXTRA))
    {
        gMoreSneak = 20;
        tp->set_skill_extra(SS_SNEAK, min(100, tp->query_skill_extra(SS_SNEAK) + 
            gMoreSneak));
        gMoreHide = 20;
        tp->set_skill_extra(SS_HIDE, min(100, tp->query_skill_extra(SS_HIDE) + 
            gMoreHide));
        gMoreAwareness = 15;
        tp->set_skill_extra(SS_AWARENESS, min(100, 
            tp->query_skill_extra(SS_AWARENESS) + 
            gMoreAwareness));
        tp->add_prop(RANGER_I_EXTRA, 1);
    }
    tp->add_prop(RANGERS_MASK_CLOSED, 1);
    return 1;
}
/*
 * Function name: pin_cloak
 * Description  : Pin the cloak closer so that it conceals the body.
 *                Can only be pinned when it is both worn and player
 *                is also hooded.
 * Arguments    : str - The proper syntax = <pin cloak>
 * Returns      : True or false.
 */
int
pin_cloak(string str)
{
    object tp = this_player();
    if (!RANGERS_FULL_MEMBER(tp))
    {
        notify_fail("You fumble with the brooch, but are unable " +
            "to fasten the cloak tighter.\n");
        return 0;
    }

    if (!strlen(str) || str != "cloak")
    {
        notify_fail("Pin cloak?\n");
        return 0;
    }
    
    if (!tp->query_prop(RANGERS_I_INCOGNITO))
    {
        notify_fail("You must be hooded to pin your cloak.\n");
        return 0;
    }

    if (!gShadow)
        return 0;

    if (tp->query_prop(RANGER_I_PINNED_CLOAK))
    {
        notify_fail("The cloak is already pinned!\n");
        return 0;
    }

    tp->add_prop(RANGER_I_PINNED_CLOAK, 1);
    write("You secure your cloak at the shoulder, pinning it " +
        "with a brooch, successfully " +
        "concealing your body from onlookers.\n");
    say(QCTNAME(tp) + " secures " + tp->query_possessive() +
        " cloak with a brooch at the left shoulder, covering " +
        tp->query_objective() + " from head to foot.\n");
    return 1;
}
/*
 * Function name: unpin_cloak
 * Description  : unpin the cloak to reveal more of the body
 * Arguments    : str - The proper syntax = <unpin cloak>
 * Returns      : True or false.
 */
int
unpin_cloak(string str)
{
    object tp = this_player();
    if (!IS_RANGER(tp))
    {
        notify_fail("What ?\n");
        return 0;
    }

    if (!strlen(str) || str != "cloak")
    {
        notify_fail("Unpin cloak?\n");
        return 0;
    }
    
    if (!tp->query_prop(RANGER_I_PINNED_CLOAK))
    {
        notify_fail("The cloak is not pinned at the moment.\n");
        return 0;
    }


    tp->remove_prop(RANGER_I_PINNED_CLOAK);
    write("You unpin and fling back your cloak, revealing more " +
        "of your appearance.\n");
    say(QCTNAME(tp) + " unpins " + tp->query_possessive() + 
        " cloak, flinging it back to reveal more of " + 
        tp->query_possessive() + " appearance.\n");
    return 1;
}

/*
 * Function name: unmask_me
 * Description  : Unmask oneself so that your friends recognize you.
 * Arguments    : str - The proper string to wear the hood.
 * Returns      : True or false.
 */
public int
unmask_me(string str)
{
    object tp = this_player();

    if (!strlen(str) || (str != "me" && str != "myself"))
        return 0;

    if (query_worn() != tp)
        return 0;

    if (!gShadow)
        return 0;

    if (!tp->query_prop(RANGERS_MASK_CLOSED) ||
      (!RANGERS_FULL_MEMBER(tp) && !tp->query_wiz_level()))
    {
        write("The mask cannot be opened further.\n");
        return 1;
    }
    write("You loosen your mask and hood somewhat, revealing more " +
        "of your appearance.\n");
    say(QCTNAME(tp) + " loosens " + tp->query_possessive() +
        " mask and hood somewhat.\n");
    // adjust ron extra skills, remove props
    fix_skills(tp);
    return 1;
}

public int
do_identify(object who)
{
    object tp = this_player();
    string *known_prop, name = tp->query_real_name();

    if ((member_array(name, m_indexes(who->query_remember_name()))== -1) &&
       (member_array(name, m_indexes(who->query_introduced()))== -1))
    {
        write("You have never been introduced to " +
            who->query_the_name(tp) + ".\n");
        return 0;
    }
    if (tp->query_prop(RANGERS_MASK_CLOSED))
    {
        known_prop = who->query_prop(RANGERS_AS_KNOWN);
        if (sizeof(known_prop))
        {
            /* Let's not add them twice! */
            if (member_array(name, known_prop) == -1)
            {
                known_prop += ({ name });
                who->add_prop(RANGERS_AS_KNOWN, known_prop);
            }
            else
            {
                write("You have already identified yourself to " +
                    who->query_the_name(tp) + ".\n");
                return 0;
            }
        }
        else
        {
            known_prop = ({ name });
            who->add_prop(RANGERS_AS_KNOWN, known_prop);
        }

        /* Ranger has hood closed. Let the target know we're there. */
        who->catch_tell("The cloaked figure identifies " +
            "itself to you as " + tp->query_name() + 
            ", lifting " + tp->query_possessive() + " hood slightly.\n");
        write("You lift your hood slightly, identifying yourself to " +
            who->query_the_name(tp) + ".\n");
        return 1;
    }
    else if ((tp->query_prop(OBJ_I_HIDE) > 0) && 
      (tp->query_prop(RANGERS_I_INCOGNITO)))
    {
        /* Ranger has hood on and is hidden, but doesn't have
           hood closed. Let the target know we are there. */
        who->catch_tell("The cloaked figure identifies " +
            "itself to you as " + tp->query_name() + 
            ", lifting " + tp->query_possessive() + " hood slightly.\n");
        write("You lift your hood slightly, identifying yourself to " +
            who->query_the_name(tp) + ".\n");
        return 1;
    }

    write("You are in plain sight.\n");
    return 0;
}

public int
identify_myself(string str)
{
    int i, size, res = 0;
    mixed *targets;
    object *others;
    object tp = this_player();

    /* This only works with the hood on. */
    if (!tp->query_prop(RANGERS_I_INCOGNITO))
        return 0;

    if (!strlen(str))
    {
        notify_fail("Identify yourself to whom?\n");
        return 0;
    }

    if (str == "me to team" || str == "myself to team")
    {
        targets = tp->query_team_others();
        if (!sizeof(targets))
        {
            write("You have no team members.\n");
            return 1;
        }

        for (i = 0, size = sizeof(targets); i < size; i++)
            res = do_identify(targets[i]);
    }
    else
    {
        if (!parse_command(str, environment(tp), 
          "'myself' / 'me' 'to' %i", targets) ||
          !sizeof(targets = NORMAL_ACCESS(targets, 0, 0)))
        {
            notify_fail("Identify yourself to whom?\n");
            return 0;
        }

        if (sizeof(targets) > 1)
        {
            write("You can only identify yourself to one person, or to your " +
                "entire team if you have one.\n");
            return 1;
        }

        res = do_identify(targets[0]);
    }

    if (res)
    {
        /* Let others in the room see the action if they can. */
        others = filter(all_inventory(environment(tp)), interactive);
        others -= targets;
        others -= ({ tp, 0 });
 
        for (i = 0, size = sizeof(others); i < size; i++)
        {
            if (CAN_SEE(others[i], TP) && 
              (random(others[i]->query_skill(SS_AWARENESS)) > 
              ((tp->query_skill(SS_SNEAK) +
              tp->query_skill(SS_HIDE)) / 2)))
            {
/*
                others[i]->catch_tell("You notice " + 
                    QTNAME(others[i]) + " lift " + 
//                    QTNAME(tp) + " lift " + 
                    tp->query_possessive() + " hood slightly.\n");
*/
// reveals themselves to those they know
        targetbb(" lifts " + tp->query_possessive() + " hood slightly to you.", others);
// reveals themselves to those they don't know
        all2actbb(" lifts " + tp->query_possessive() + " hood slightly.",others);

            }
        }
    }

    return 1;
}

public void
init()
{
    ::init();

    if (TP != ENV(TO))
        return;

    add_action(&wear_hood(),     "wear");
    add_action(&wear_hood(),     "hood");
    add_action(&remove_hood(),   "unhood");
    add_action(&mask_me(),       "mask");
    add_action(&unmask_me(),     "unmask");
    add_action(&identify_myself(), "identify");
    add_action(&pin_cloak(),     "pin");
    add_action(&unpin_cloak(),   "unpin");
    add_action(&remove_hood(), "remove");

}

/*
 * Function name: leave_env
 * Description  : Called when the robe leaves its environment.
 */
public void
leave_env(object from, object to)
{
    gShadow->remove_cloak_shadow();
    gShadow = 0;    
    this_object()->remove_prop(OBJ_M_NO_DROP);
    fix_skills(from);
    ::leave_env(from, to); 
    wearable_item_leave_env(from, to);
    from->update_actions();
}

void
appraise_object(int num)
{
    ::appraise_object(num);
    appraise_wearable_item();
}

public void
set_colour(string str)
{
    gColour = str;
}

public string
query_recover()
{
    return MASTER + ":" + query_keep_recover();
}

public void
init_recover(string arg)
{
    init_keep_recover(arg);
}

