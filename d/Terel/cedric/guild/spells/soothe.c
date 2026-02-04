#pragma strict_types

#include "../guild_defs.h"

inherit (GUILD + "spells/base");
inherit "/d/Genesis/specials/std/spells/heal";

#include <wa_types.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <files.h>
#include <composite.h>

#include <macros.h>
#include <tasks.h>

/*
 * Function:    config_heal_spell
 * Description: Config function for heal spells. Redefine this in your
 *              own heal spells to override the defaults.
 */
public void
config_heal_spell(void)
{
    set_spell_name("soothe");
    set_spell_desc("This Song of Power is designed to heal with a sweet " + 
        "and soothing tune");

    configure_minstrel_spell();
    set_spell_combat_aid(50.0);
}

/*
 * Function:    query_spell_can_be_learned
 * Description: Place restrictions on whether this spell can be used
 *              by the guild member.
 */
public int
query_spell_can_be_learned(object player)
{
    return 1;
}

/*
 * Function:    query_heal_ingredients
 * Description: This function defines what components are required for
 *              this heal spell.
 */
public string *
query_heal_ingredients(object caster)
{
    return ({  });
}

/*
 * Function name: hook_describe_heal_result
 * Description:   Describe the results of the spell upon its targets. This
 *                happens after the healing has happened.
 *                This can be redefined for custom messages.
 * Arguments:     object caster   - the caster
 *                object * target - the target(s)
 *                int * heal_amts - the amounts healed
 */
public void
hook_describe_heal_result(object caster, object *targets, int * heal_amounts)
{
    object target = targets[0]; 

    t_set("actor", caster);
    t_set("target", target);

    if (target != caster)
        t_tell(caster, "The sweet tune rushes over {target:s} body, healing {target:his} wounds.");
    t_tell(target, "The sweet tune rushes over your body, healing your wounds.");
    t_watchers("{actor} plays a soothing melody for {target}, who seems to benefit thereby.", caster, target);
}
