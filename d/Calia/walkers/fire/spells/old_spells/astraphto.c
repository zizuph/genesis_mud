
 /* Astraphto (Tell Line) spell for the Firewalkers of Thalassia
  * by Jaacar 
  */

#pragma strict_types

inherit "/d/Genesis/magic/spells/tell";

#include <options.h>
#include <ss_types.h>
#include <macros.h>
#include "defs.h"
#include FIRE_HEADER

public object *
tell_target_one_distant_guild_member_by_skill_or_known_living(object caster,
    string str, int skill)
{
    object living;

    if (!strlen(str))
    {
        caster->catch_tell("Target whom?\n");
        return ({});
    }

    living = find_living(str);

    if (!objectp(living) ||
        !(living->query_skill(skill) ||
        caster->query_met(living)) || 
        (living->query_wiz_level() && living->query_invis()))
    {
	caster->catch_tell("You do not sense " + LANG_POSS(str) +
            " presence in the realms.\n");
	return ({ });
    }

    return ({ living });     
}

public object *
find_tell_targets(object caster, string name)
{
    return tell_target_one_distant_guild_member_by_skill_or_known_living(caster,
        name, SS_PATRON_ELEMENTAL);
}

public void
tell(object caster, object *targets, int *resist, int result)
{
    write("You place your fingers upon your head and "+
        "send forth your thoughts.\n");

    if (caster->query_option(OPT_ECHO))
    {
        caster->catch_tell("You use the powers of Astraphto to "+
            "speak to " + targets[0]->query_met_name() + ": " +
            query_tell_message() + "\n");
    }
    targets[0]->catch_tell("A sudden burning sensation forms in "+
        "your head, quickly becoming the voice of " + 
        caster->query_met_name() +
        " saying: " + query_tell_message() + "\n");

    tell_room(environment(caster),QCTNAME(caster)+" places "+
        C_HIS+" fingers upon "+C_HIS+" forehead briefly.\n",({caster}));
}

public int
create_spell_tell(object caster, object *targets, string argument)
{
    ::create_spell_tell(caster, targets, argument);
    set_spell_element(SS_ELEMENT_FIRE, 10);
    set_spell_form(SS_PRAYER, 10);
    set_spell_ingredients(({"ash"}));
}
