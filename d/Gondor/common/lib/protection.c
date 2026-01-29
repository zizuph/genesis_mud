/*
 * A module to help npcs protect their frail but potent fellas.
 *
 * Usage:
 *
 * o Inherit /d/Gondor/common/lib/protection into the protected npc.
 *
 *
 * o Add the array of protectors to the protected npc:
 *
 * frail_mage->add_protectors(brutish_fighters);
 *
 *
 * o Make sure your protectors have some skill in SS_PROTECT_TEAM_MEMBER
 *   as defined by /d/Gondor/defs.h:
 *
 * map(brutish_fighters, &->set_skill(SS_PROTECT_TEAM_MEMBER, 60 + random(5)));
 *
 *
 * o If you want fancier messages redefine tell_all_protection in the protected
 *   npc.
 *
 *
 * o Set the SS_PROTECT_TEAM_MEMBER to 100 if you want absolute protection.
 *
 */

#include <wa_types.h>
#include <macros.h>
#include "/d/Gondor/defs.h"

object *Protectors;
object  Protector;

public nomask void add_protectors(object *pr);
public nomask object* order_protectors(object *arr);
public int query_not_attack_me(object who, int aid);
public object get_protector();
public nomask int filter_present_protectors(object person);
public void tell_all_protection(object protected,
				object protector,
				object agressor);
public int best_pr_skill(object first, object second);


public int
query_not_attack_me(object aggressor, int aid)
{
    mixed attack;
    object weapon;
    object protector = get_protector();

    if (objectp(protector))
    {	
	attack = aggressor->query_combat_object()->query_attack(aid);
	
	if (pointerp(attack))
	{
	    weapon = attack[6];

	    if (weapon && weapon->query_wt() == W_MISSILE)
	    {
		return 0;
	    }
	}

	if (protector->query_skill(SS_PROTECT_TEAM_MEMBER) > random(100))
	{	    
	    this_object()->
		tell_all_protection(this_object(), protector, aggressor);
	    
	    protector->heal_hp(-20);
	    protector->add_fatigue(-3);

	    if (protector->query_hp() <= 0)
	    {
		protector->do_die(aggressor);
	    }
	    
	    return 1;
	}
    }
    return 0;
}

public nomask void
add_protectors(object *pr)
{
    Protectors = order_protectors(pr);
}

public nomask object*
order_protectors(object *arr)
{
    arr -= ({ 0 });
    
    return sort_array(arr, "best_pr_skill");
}

public object
get_protector()
{
    object *present_protectors;
    
    if (Protector && environment(Protector) == environment(this_object()))
    {
	return Protector;
    }
    
    if (!sizeof(Protectors))
    {
	Protector = 0;
	return 0;
    }

    Protectors -= ({ 0 });
    
    present_protectors = filter(Protectors, &filter_present_protectors());

    if (!sizeof(present_protectors))
    {
	Protector = 0;	
	return 0;
    }

    Protector = present_protectors[0];
    
    return Protector;
}

public nomask int
filter_present_protectors(object person)
{
    if (!person)
    {
	return 0;
    }

    return environment(person) == environment(this_object());
}

public void
tell_all_protection(object protected, object protector, object aggressor)
{
    if (interactive(aggressor))
    {
	tell_object(aggressor, protector->query_The_name(aggressor) + 
		    " blocks your attempt to harm " +
		    protected->query_the_name(aggressor) + ".\n");
    }
    
    if (interactive(protected))
    {
	tell_object(protected,
		    protector->query_The_name(protected) + " blocks " +
		    LANG_POSS(aggressor->query_the_name(protected)) +
		    " attempt to harm you.\n");
    }

    if (interactive(protector))
    {
	tell_object(protector, "You block " +
		    LANG_POSS(aggressor->query_the_name(protector)) +
		    " attempt to harm " +
		    protected->query_the_name(protector) + ".\n");
    }
}

public int
best_pr_skill(object first, object second)
{
    int first_skill = first->query_skill(SS_PROTECT_TEAM_MEMBER);
    int second_skill = second->query_skill(SS_PROTECT_TEAM_MEMBER);

    if (first_skill < second_skill)
    {
	return -1;
    }
    else if (first_skill > second_skill)
    {
	return 1;
    }
    else
    {
	return 0;
    }
}

