/*
 * /d/Kalad/common/guilds/new_thanar/spells/thanar_stun.c
 * Stun spell used by the Thanars in Kalad.
 * 
 * Created by Zignur, Jan 2018.
 *
 */
 
#pragma strict_types
inherit "/d/Genesis/specials/std/spells/stun";
#include <macros.h>
#include <tasks.h>
#include <stdproperties.h>
#include <flags.h>
#include <composite.h>
#include "../local.h"
#include "/d/Kalad/defs.h"


// Prototypes
public void resolve_stun_spell(object caster, mixed * targets, int * resist, 
int result);
public void hook_describe_cast_stun(object caster, object * targets);
public void hook_target_stun_resisted(object caster, object * targets);
public void hook_target_stun_succeeded(object caster, object * targets);
 
/*
 * Function:    config_stun_spell
 * Description: Config function for stun spells. Redefine this in your
 *              own stun spells to override the defaults.
 * Arguments:   Same as config_spell
 * Returns:     Same as config spell
 */
public void
config_stun_spell()
{
    set_spell_name("tstun");
    set_spell_desc("Stun your foe.");
    set_spell_vocal(1);
    set_spell_visual(1);
    set_spell_stationary(0);
    set_spell_peaceful(0);
    set_spell_offensive(1);
    set_spell_combat_aid(100.0);

    set_spell_object(SPELLS + "obj/deity_stun_obj");    
} /* config_stun_spell */

/*
 * Function:    query_stun_ingredients
 * Description: This function defines what components are required for
 *              this stun spell.
 */
public string *
query_stun_ingredients(object caster)
{
    return ({ });
} /* query_stun_ingredients */


// HOOKS TO BE DEFINED

/*
 * Function:    resolve_stun_spell
 * Description: Called at the beginning of resolve_spell in order to perform
 *              spell specific actions.
 * Arguments:   Same as resolve_spell
 */
public void
resolve_stun_spell(object caster, mixed * targets, int * resist, int result)
{
    
}/* resolve_stun_spell */

/*
 * Function:    hook_describe_cast_stun
 * Description: Function that gets called to display the caster casting the
 *              spell towards his intended targets.
 */
public void
hook_describe_cast_stun(object caster, object * targets)
{
    caster->catch_tell("You show a moment of your true form and turn it " +
        "towards " + COMPOSITE_LIVE(targets) + ".\n");
    caster->tell_watcher(QCTNAME(caster) + " briefly reveals "
		+ caster->query_possessive() +" true form.\n", ({ }) );
} /* hook_describe_cast_stun */

/*
 * Function:    hook_target_stun_resisted
 * Description: Called to show the messages of the targets that were not
 *              stunned because they resisted the spell.
 */
public void
hook_target_stun_resisted(object caster, object * targets)
{
    if (!sizeof(targets))
    {
        return;
    }
    
    caster->catch_tell(" " + COMPOSITE_LIVE(targets) + ", seems "
        + "immune of your ghastly visage of Thanar.\n");
    targets->catch_tell("You are unaffected by the ghastly visage of "
        + "Thanar.\n"); 
} /* hook_target_stun_resisted */

/*
 * Function:    hook_target_stun_succeeded
 * Description: Called to show the messages of the targets that were
 *              affected by the stun. Part of the stun messages
 *              will also be described by the stun object itself. Note
 *              that it's entirely possible the stun spell may hit,
 *              but because of a cooldown period, the stun may not
 *              actually have any effect.
 */
public void
hook_target_stun_succeeded(object caster, object * targets)
{
    if (!sizeof(targets))
    {
        return;
    }
    
    caster->catch_tell("You hit " + COMPOSITE_LIVE(targets) + " with your "
        + "stun spell.\n");
    targets->catch_tell("You are stare at the ghastly visage in absolute "
        + "terror unable to move.\n");
} /* hook_target_stun_succeeded */
