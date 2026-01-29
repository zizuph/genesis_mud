/*
 * /d/Kalad/common/guilds/new_thanar/spells/thanar_blind.c
 * Blind spell used by the Thanars in Kalad.
 * 
 * Created by Zignur, Jan 2018.
 *
 */
#pragma strict_types
#pragma save_binary
inherit "/d/Genesis/specials/std/spells/blind";
#include <stdproperties.h>
#include <macros.h>
#include <wa_types.h>
#include <ss_types.h>
#include <tasks.h>
#include <composite.h>
#include "../local.h"
#include "/d/Kalad/defs.h"



/*
 * Function:    config_blind_spell
 * Description: Config function for blind spells. Redefine this in your
 *              own blind spells to override the defaults.
 * Arguments:   Same as config_spell
 * Returns:     Same as config spell
 */
public void
config_blind_spell()
{
    set_spell_name("tblind");
    set_spell_vocal(1);
    set_spell_visual(1);
    set_spell_stationary(0);
    set_spell_peaceful(0);
    set_spell_offensive(1);
   
    // Set the effect object filename
    set_spell_object(SPELLS + "obj/thanar_blind_obj");
} /* config_blind_spell */

/*
 * Function:    hook_describe_blind
 * Description: Describe the blind effect
 *              
 * Arguments:   object caster, mixed * targets, int result
 */
public void
hook_describe_blind(object caster, mixed * targets, int result)
{
    caster->catch_msg("Your prayers being heard, you extend " +
              "your hands towards "+ COMPOSITE_LIVE(targets) +
              " and feel dark shadows shoot out from your " +
              "hands.\n");
    targets->catch_msg(QCTNAME(caster) + " extends " + HIS(caster) +
              " hands, dark shadows shoot out towards you.\n");
    tell_room(environment(caster), 
        QCTNAME(caster) + " extends " + HIS(caster) + 
              " hands towards " + COMPOSITE_LIVE(targets) +
              " causing a dark shadows to shoot out.\n",
              ({ caster }) + targets, caster);
} /* hook_describe_blind */

/*
 * Function:    resolve_blind_spell
 * Description: Called at the beginning of resolve_spell in order to perform
 *              spell specific actions.
 * Arguments:   object caster, mixed * targets, int * resist, int result
 */
public void
resolve_blind_spell(object caster, mixed * targets, int * resist, int result)
{

} /* resolve_blind_spell */

/*
 * Function:    hook_already_has_spell_object
 * Description: Checks if the target is already blinded
 * Arguments:   object caster, object target
 */
public void
hook_already_has_spell_object(object caster, object target)
{
    if (objectp(target))
    {
        caster->catch_msg("But " + QTNAME(target) + " is already blinded!\n");
    }
} /* hook_already_has_spell_object */

/*
 * Function:    query_blind_ingredients
 * Description: This function defines what components are required for
 *              this blind vision spell.
 */
public string *
query_blind_ingredients(object caster)
{
    return ({ "" });
} /* query_blind_ingredients */
