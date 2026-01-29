/*
 * The base code for the cloaks of the Rangers of the North
 * By Rastlin.
 *   Modification Log:
 *     Elessar, 1998.
 *     Alto, February 2002. Adapted for ranger recode.
 *                          Generalize for use by Ithilien and North
 *                          Add close/open hood for true anonymity
 *     Tigerlily, August 8, 2004: made keepable
 */
inherit "/std/object";
inherit "/lib/wearable_item";
inherit "/lib/keep.c";

#include "/d/Gondor/defs.h"
#include "../rangers.h"

#include <cmdparse.h>
#include <formulas.h>
#include <macros.h>
#include <state_desc.h>
#include <stdproperties.h>
#include <wa_types.h>

#define RANGERS_HOOD_CLOSED    "_rangers_hood_closed"
#define RANGERS_I_INCOGNITO    "_rangers_incognito"
#define RANGERS_AS_KNOWN       "_rangers_as_known"
#define RANGER_I_WEARING_CLOAK "_ranger_i_wearing_cloak"
object gShadow = 0;
string gColour = "brown";
int    gMoreSneak = 0, gMoreHide = 0;

/* Prototypes */
void set_colour(string str);

public void
create_robe()
{
    set_colour("grey");
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
fix_skills()
{
    if (TP->query_prop(RANGERS_HOOD_CLOSED));
    {
        TP->set_skill_extra(SS_SNEAK,
            (TP->query_skill_extra(SS_SNEAK) - gMoreSneak));
        TP->set_skill_extra(SS_HIDE,
            (TP->query_skill_extra(SS_HIDE) - gMoreHide));
        TP->remove_prop(RANGERS_HOOD_CLOSED);
        gMoreSneak = 0;
        gMoreHide = 0;
    }

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
    if (what != TO)
        return -1;

    gShadow->remove_shadow();
    gShadow = 0;
    TP->remove_prop(RANGER_I_WEARING_CLOAK);
    fix_skills();
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

    gShadow = clone_object(RANGERS_OBJ + "hood_shadow");
    gShadow->set_colour(gColour);
    gShadow->shadow_me(player);
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
    string name = TP->query_real_name();

    /* Syntax is 'wear hood' or 'hood me/myself/name' */
    if (!str || !strlen(str) || 
      (str != "hood" && query_verb() == "wear") ||
      (str != "me" && str != "myself" && str != name && query_verb() == "hood"))
    {
        notify_fail("Hood me?\n");
        return 0;
    }

    if ((query_worn() != TP))
    {
        notify_fail("You are not wearing a cloak!\n");
        return 0;
    }

    if (gShadow)
    {
        notify_fail("You are already wearing the hood!\n");
        return 0;
    }

    if ((!RANGERS_MEMBER(TP)) && (!TP->query_wiz_level()))
    {
        write("The hood does not fit well enough to stay on your head.\n");
        return 1;
    }

    write("You pull the hood of your cloak low down over your face. You " +
        "feel that you could 'reveal yourself to someone' if you were " +
        "hidden.\n");
    say(QCTNAME(TP) + " pulls " + TP->query_possessive() +
        " hood over " + TP->query_possessive() + " head, hiding " +
        TP->query_possessive() + " face.\n");

    hood_player(TP);

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
    string name = TP->query_real_name();

    if (query_verb() == "remove")
    {
        if (!strlen(str) || str != "hood")
        {
            notify_fail("Remove hood?\n");
            return 0;
        }
    }
    else if (!strlen(str) ||
      (str != "me" && str != "myself" && str != TP->query_real_name()))
    {
        notify_fail("Unhood me?\n");
        return 0;
    }

    if ((query_worn() != TP))
    {
        notify_fail("You are not wearing a cloak!\n");
        return 0;
    }

    if (!gShadow)
    {
        notify_fail("You are not wearing your hood.\n");
        return 0;
    }

    write("You remove the hood, and once again reveal your face.\n");
    TP->remove_prop(RANGERS_I_INCOGNITO);
    say(QCTNAME(TP) + " removes " + TP->query_possessive() + " hood from " +
        TP->query_possessive() + " face.\n");

    gShadow->remove_shadow();
    gShadow = 0;

    fix_skills();

    return 1;
}

/*
 * Function name: close_hood
 * Description  : Close the hood so that you become anonymous.
 * Arguments    : str - The proper string to wear the hood.
 * Returns      : True or false.
 */
public int
close_hood(string str)
{
    if (!strlen(str) || str != "hood")
        return 0;

    if (query_worn() != TP)
        return 0;

    if (!gShadow)
        return 0;

    if (TP->query_prop(RANGERS_HOOD_CLOSED) || 
      (TP->query_ranger_level() != NORTH_LEVEL && !TP->query_wiz_level()))
    {
        write("The cloak and hood cannot be closed further.\n");
        return 1;
    }

    write("You draw the cloak and hood so close about you that even " +
        "your own mother would take you for a stranger. You " +
        "feel that you could 'reveal yourself to someone' if you " +
        "wanted them to recognize you.\n");
    say(QCTNAME(TP) + " draws " + TP->query_possessive() +
        " cloak and hood as close as possible about " +
        TP->query_possessive() + " head and body.\n");

    if (!TP->query_ranger_has_virtues())
    {
        gMoreSneak = 15;

        TP->set_skill_extra(SS_SNEAK, min(100, TP->query_skill_extra(SS_SNEAK) + 
            gMoreSneak));

        gMoreHide = 15;

        TP->set_skill_extra(SS_HIDE, min(100, TP->query_skill_extra(SS_HIDE) + 
            gMoreHide));
    }
    TP->add_prop(RANGERS_HOOD_CLOSED, 1);
    return 1;
}

/*
 * Function name: open_hood
 * Description  : Open the hood so that your friends recognize you.
 * Arguments    : str - The proper string to wear the hood.
 * Returns      : True or false.
 */
public int
open_hood(string str)
{
    if (!strlen(str) || str != "hood")
        return 0;

    if (query_worn() != TP)
        return 0;

    if (!gShadow)
        return 0;

    if (!TP->query_prop(RANGERS_HOOD_CLOSED) ||
      (TP->query_ranger_level() != NORTH_LEVEL && !TP->query_wiz_level()))
    {
        write("The cloak and hood cannot be opened further.\n");
        return 1;
    }

    write("You loosen your cloak and hood somewhat.\n");
    say(QCTNAME(TP) + " loosens " + TP->query_possessive() +
        " cloak and hood somewhat.\n");

    fix_skills();

    return 1;
}

public int
do_reveal(object who)
{
    string *known_prop, name = TP->query_real_name();

    if (TP->query_prop(RANGERS_HOOD_CLOSED))
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
        }
        else
        {
            known_prop = ({ name });
            who->add_prop(RANGERS_AS_KNOWN, known_prop);
        }

        /* Ranger has hood closed. Let the target know we're there. */
        who->catch_tell(TP->query_The_name(who) + " reveals " +
            TP->query_objective() + "self to you, lifting " + 
            TP->query_possessive() + " hood slightly.\n");
        write("You lift your hood slightly, revealing yourself to " +
            who->query_the_name(TP) + ".\n");

        return 1;
    }
    else if ((TP->query_prop(OBJ_I_HIDE) > 0) && 
      (TP->query_prop(RANGERS_I_INCOGNITO)))
    {
        /* Ranger has hood on and is hidden, but doesn't have
           hood closed. Let the target know we are there. */
        who->catch_tell(TP->query_The_name(who) + " reveals " +
            TP->query_objective() + "self to you, lifting " + 
            TP->query_possessive() + " hood slightly.\n");
        write("You lift your hood slightly, revealing yourself to " +
            who->query_the_name(TP) + ".\n");
        return 1;
    }

    write("You are in plain sight.\n");
    return 0;
}

public int
reveal_myself(string str)
{
    int i, size, res = 0;
    mixed *targets;
    object *others;

    /* This only works with the hood on. */
    if (!TP->query_prop(RANGERS_I_INCOGNITO))
        return 0;

    if (!strlen(str))
    {
        notify_fail("Reveal yourself to whom?\n");
        return 0;
    }

    if (str == "me to team" || str == "myself to team")
    {
        targets = TP->query_team_others();
        if (!sizeof(targets))
        {
            write("You have no team members.\n");
            return 1;
        }

        for (i = 0, size = sizeof(targets); i < size; i++)
            res = do_reveal(targets[i]);
    }
    else
    {
        if (!parse_command(str, environment(TP), 
          "'myself' / 'me' 'to' %i", targets) ||
          !sizeof(targets = NORMAL_ACCESS(targets, 0, 0)))
        {
            notify_fail("Reveal yourself to whom?\n");
            return 0;
        }

        if (sizeof(targets) > 1)
        {
            write("You can only reveal yourself to one person, or to your " +
                "entire team if you have one.\n");
            return 1;
        }

        res = do_reveal(targets[0]);
    }

    if (res)
    {
        /* Let others in the room see the action if they can. */
        others = filter(all_inventory(environment(TP)), interactive);
        others -= targets;
        others -= ({ TP, 0 });
 
        for (i = 0, size = sizeof(others); i < size; i++)
        {
            if (CAN_SEE(others[i], TP) && 
              (random(others[i]->query_skill(SS_AWARENESS)) > 
              ((TP->query_skill(SS_SNEAK) +
              TP->query_skill(SS_HIDE)) / 2)))
            {
                others[i]->catch_tell("You notice " + 
                    TP->query_the_name(others[i]) + " lift " + 
                    TP->query_possessive() + " hood slightly.\n");
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

    add_action(wear_hood,     "wear");
    add_action(wear_hood,     "hood");
    add_action(remove_hood,   "remove");
    add_action(remove_hood,   "unhood");
    add_action(close_hood,    "close");
    add_action(open_hood,     "open");
    add_action(reveal_myself, "reveal");
}

/*
 * Function name: leave_env
 * Description  : Called when the robe leaves its environment.
 */
public void
leave_env(object from, object to)
{
    gShadow->remove_shadow();
    gShadow = 0;

    fix_skills();

    ::leave_env(from, to);     
    wearable_item_leave_env(from, to);
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

