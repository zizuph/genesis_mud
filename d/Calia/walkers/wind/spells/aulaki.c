
 /* Aulaki (Far Sight) spell for the Windwalkers of Thalassia
  * by Jaacar 
  */

#pragma strict_types

inherit "/d/Genesis/magic/components";
inherit "/d/Genesis/magic/resist";
inherit "/d/Genesis/magic/targeting";
inherit "/d/Genesis/magic/spell_config";
inherit "/d/Calia/std/contents_desc";

#include <ss_types.h>
#include <macros.h>
#include <tasks.h>
#include <filter_funs.h>
#include <stdproperties.h>
#include <language.h>
#include "defs.h"
#include WIND_HEADER

public void aulaki(object caster, object *targets, int *resist,
    int result);
public int create_spell_aulaki(object caster, object *targets,
    string argument);

public object *
tell_target_one_distant_guild_member_or_known_living(object caster, string str, string guild)
{
    object living;

    if (!strlen(str))
    {
        caster->catch_tell("Target whom?\n");
        return ({});
    }

    living = find_living(str);

    if (!objectp(living) ||
        !(living->query_guild_member(guild) ||
        caster->query_met(living)) ||
        living->query_wiz_level())
    {
	caster->catch_tell("You do not sense " + LANG_POSS(str) +
            " presence in the realms.\n");
	return ({ });
    }

    return ({ living });     
}

public object *
find_aulaki_targets(object caster, string name)
{
    if (!present("_aulaki_potion_object_",caster))
    {
        caster->catch_tell("You are not under the effects of the "+
            "aulaki potion!\n");
        return ({});
    }

    return tell_target_one_distant_guild_member_or_known_living(caster,
        name, GUILD_NAME);
}

public void
aulaki(object caster, object *targets, int *resist, int result)
{
    string desc;
    object env;

    env = environment(targets[0]);
    
    desc = ("\n" + room_desc(env,1));

    if (desc[strlen(desc)-1] == '\n')
        desc = desc[0..(strlen(desc)-2)];

    caster->catch_msg("You place your fingers upon your head and "+
        "concentrate on the image of " + QCNAME(targets[0]) + ".\n");

    caster->catch_tell("You successfully cast Aulaki and "+
        "see:\n" + desc + "\n");
    
    tell_room(environment(caster),QCTNAME(caster)+" places "+
        C_HIS+" fingers upon "+C_HIS+" forehead briefly.\n",({caster}));
}

public int
create_spell_aulaki(object caster, object *targets, string argument)
{
    set_spell_time(1);
    set_spell_mana(50);
    set_spell_task(TASK_ROUTINE);
    set_spell_element(SS_ELEMENT_AIR, 50);
    set_spell_form(SS_PRAYER, 50);
    set_spell_ingredients(({ })); // Uses a potion
    set_spell_resist(spell_resist_basic);
    return 0;
}
