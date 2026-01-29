/*
 * The Hood-shadow
 *
 * 960117 by Rastlin
 */

// #include <stdproperties.h>
#include <filter_funs.h>
#include <cmdparse.h>
#include <macros.h>
#include <ss_types.h>
#include <language.h>
#include <tasks.h>
#include "../local.h"
#include "../../local.h"
#include "/d/Krynn/common/defs.h"

inherit "/std/shadow";

static string *gAdjs;
static int gAlarm_id;

/*
 * Function name: set_color
 * Description:
 * Arguments:
 * Returns:
 */
public void
set_color(string color)
{
    gAdjs = ({ color + "-robed", "hooded" });
}

/*
 * Function name: query_adj
 * Description:   Gives the adjective(s) of the object.
 * Arguments:     int arg - if true, all adjectives are returns, else only
 *                          the first adjective is returned.
 * Returns:       mixed   - int 0    - if there are no adjectives.
 *                          string   - one adjective if 'arg' is false.
 *                          string * - an array with all adjectives if
 *                                     'arg' is true.
 */
varargs public mixed
query_adj(int arg) 
{ 
    if (arg)
        return gAdjs;
    else
        return gAdjs[0]; 
}

/*
 * Function name: query_adjs
 * Description:   This function returns an array of all adjectives of
 *                this object.
 * Returns:       An array of all adjectives of this object
 *                or false if there are no adjectives.
 */
public string *
query_adjs() 
{ 
    return gAdjs; 
}

/*
 * Description: This function is used by the efun parse_command()
 */
public string *
parse_command_adjectiv_id_list() 
{
    return gAdjs;
}

/*
 * Function name: adjectiv_id
 * Description  : This function can be used to see whether a certain
 *                adjective is used by this object.
 * Arguments    : string str - the adjective you want to test.
 * Returns      : int 1/0 - true if the adjective is indeed used.
 */
public int
adjectiv_id(string str)
{
    return (member_array(str, gAdjs) >= 0);
}

static void
get_introduced(object *targets, object *shadows)
{
    mixed tmp;
    int i = sizeof(targets);
    mapping known = shadow_who->query_prop(WOHS_AM_KNOWN);
    gAlarm_id = 0;

    if (!known)
        known = ([]);

    shadows->remove_shadow();

    while(i--)
    {
        if (targets[i]->query_prop(WOHS_I_GOT_INTRO))
	{
	    targets[i]->remove_prop(WOHS_I_GOT_INTRO);

	    if (!known[targets[i]->query_real_name()])
	        known[targets[i]->query_real_name()] = 1;
	}
    }
    shadow_who->add_prop(WOHS_AM_KNOWN, known);
}

public string
query_presentation()
{
    object *targets, *shadows = ({}), shadow;
    int i;

    if ((calling_function() == "intro_live") && !gAlarm_id) 
    {
        targets = FILTER_LIVE(all_inventory(E(TP))) - ({ shadow_who });

	i = sizeof(targets);
	while (i--)
	{
	    shadow = clone_object(GOBJ + "intro_shadow");
	    shadow->shadow_me(targets[i]);
	    shadows += ({ shadow });
	}
	gAlarm_id = set_alarm(-1.0, 0.0, &get_introduced(targets, shadows));
    }

    return shadow_who->query_presentation();
}

public mixed
query_prop(string prop)
{
    object prev = previous_object();
    mapping known;

    if (prop == LIVE_I_NEVERKNOWN && !prev->query_wiz_level())
    {
	if (shadow_who->query_prop(prop))
	    return 1;

	if (prev == shadow_who)
	    return 0;
	
	if (THIS_GUILD(prev))
	    return 0;

	known = shadow_who->query_prop(WOHS_AM_KNOWN);
	if (known && known[prev->query_real_name()])
	    return 0;
	else
	    return 1;
    }

    return shadow_who->query_prop(prop);
}

public nomask varargs int
shadow_me(mixed to_shadow)
{
    int result = ::shadow_me(to_shadow);
    object *targets;
    int size;
    mapping known = shadow_who->query_prop(WOHS_AM_KNOWN);

    if (result)
    {
        shadow_who->set_wohs_hooded(1);
        shadow_who->add_cmd_item(({"the face", "face"}), "reveal", 
				 "@@do_reveal");
        shadow_who->update_actions();

        targets = FILTER_LIVE(all_inventory(E(shadow_who))) - ({ shadow_who });
 
	if (!known)
	    known = ([]);

	size = sizeof(targets);
	while(size--)
	{
	    if (!known[targets[size]->query_real_name()])
	        known[targets[size]->query_real_name()] = 1;
	}
	shadow_who->add_prop(WOHS_AM_KNOWN, known);
    }
}

public void
remove_shadow()
{
    shadow_who->set_wohs_hooded(0);
    shadow_who->remove_cmd_item("face");
    shadow_who->update_actions();
    ::remove_shadow();
}

public void
remove_wohs_hood_shadow()
{
    remove_shadow();
}

public int
reveal_access(object ob)
{
    return !(!living(ob) || (ob == TP));
}

public mixed
do_reveal()
{
    object *objs, pl;
    string rest = shadow_who->query_item_rest_command();
    string who;
    float skill_tp;

    if (!sscanf(rest, "of %s", who))
        return "Reveal the face of whom?\n";

    objs = CMDPARSE_ONE_ITEM(who, "reveal_access", "reveal_access");

    if (sizeof(objs) > 1)
        return "You may only reveal the face of one person at the time.\n";

    if (!pointerp(objs) || !sizeof(objs))
        return "Noone here matches that description.\n";

    pl = objs[0];

    if (!pl->query_wohs_hooded())
        return "You can't reveal the face of " + 
	       pl->query_The_name(TP) + ".\n";

    if ((pl->query_prop(CONT_I_HEIGHT) - 
	 TP->query_prop(CONT_I_HEIGHT)) >= 50)
        return "You are too short to do that.\n";

    skill_tp = (1.0 - (itof(TP->query_intoxicated()) / 
		       itof(TP->intoxicated_max()))) *
               itof(TP->query_skill(SS_DEX));

    TP->reveal_me(1);

    if (TP->resolve_task(TASK_ROUTINE, ({ ftoi(skill_tp) }), pl, 
		     ({ SS_AWARENESS })) <= 0)
    {
        TP->catch_msg(QCTNAME(pl) + " dudges away as you tries to remove " +
	      POSSESSIVE(pl) + " hood.\n");
	pl->catch_msg(QCTNAME(TP) + " tries to remove your hood, " +
		      "but you manage to dudge away in time.\n");
	tell_room(E(TP), QCTNAME(TP) + " tries to remove " +
		  LANG_POSS(QTNAME(pl)) + " hood, but " +
		  PRONOUN(pl) + " dodges away.\n", ({ pl, TP }));
	return 1;
    }

    TP->catch_msg("You manage to remove the hood from " + 
		  LANG_POSS(QTNAME(pl)) + " face.\n");
    pl->catch_msg(QCTNAME(TP) + " successfully removes your hood, " +
		  "revealing your face.\n");
    tell_room(E(TP), QCTNAME(TP) + " successfully removes the hood from " +
	      LANG_POSS(QTNAME(pl)) + " face.\n", ({ pl, TP }));
    
    remove_shadow();
    return 1;
}

/*
 * Function name:
 * Description:
 * Arguments:
 * Returns:
 */

