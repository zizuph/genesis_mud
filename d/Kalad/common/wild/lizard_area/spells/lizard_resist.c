/*
 * Resist Spell for Lizard Shamans
 * By Mirandus, February 2022
 */

#include <ss_types.h>
#include <composite.h>
#include <cmdparse.h>
#include <macros.h>
#include <tasks.h>
#include <composite.h>
#include "../local.h"

#include "/d/Genesis/specials/local.h"
inherit SPELL_DIR + "resistance";


/*
* Function:    config_shadow_spell
* Description: Config function for shadow spells. Redefine this in your
*              own shadow spells to override the defaults.
* Arguments:   Same as config_spell
* Returns:     Same as config spell
*/
public void
config_resistance_spell()
{
    set_spell_name("lresist");
    set_spell_desc("Resist the effects of magic");

    set_spell_element(SS_ELEMENT_LIFE, 40);
    set_spell_form(SS_FORM_CONJURATION, 40);
    set_spell_task(TASK_HARD);

    set_spell_vocal(1);
    set_spell_visual(1);
    set_spell_stationary(0);
    set_spell_peaceful(0);
    set_spell_offensive(0);
	
	
    add_resistance(MAGIC_I_RES_MAGIC, 30);  // general
    add_resistance(MAGIC_I_RES_DEATH, 30); 
    

    set_spell_target(spell_target_caster);

    set_spell_object(SPELLS + "obj/lizard_resist_obj");
}


/*
* Function:    query_resistance_ingredients
* Description: This function defines what components are required for
*              this resistance spell.
*/
public string *
query_resistance_ingredients(object caster)
{
    return ({ });
} /* query_resistance_ingredients */

/*
* Function:    hook_describe_cast_resistance
* Description: Function that gets called to display the caster casting the
*              spell towards his intended targets.
*/
public void
hook_describe_cast_resistance(object caster, object * targets)
{
    caster->catch_tell("You summon the ancestors to protect " +
        "yourself against magic.\n");
    caster->tell_watcher(QCTNAME(caster) + " seems to be imbued with some " +
         "ancient strength.\n", ({ }) );
}

/*
 * Function:    resolve_resistance_spell
 * Description: Called at the beginning of resolve_spell in order to perform
 *              spell specific actions.
 * Arguments:   Same as resolve_spell
 */
public void
resolve_resistance_spell(object caster, mixed * targets,
int * resist, int result)
{
}