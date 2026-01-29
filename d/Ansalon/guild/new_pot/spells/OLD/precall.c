/*
 * pRecall
 */

#pragma strict_types

inherit "/d/Ansalon/guild/pot/spells/std_pot_spell";

#include "/d/Ansalon/common/defs.h"
#include "../spells.h"
#include "../guild.h"
#include <macros.h>
#include <cmdparse.h>
#include <tasks.h>  
#include <wa_types.h>

/*
 * Function name: resolve_spell
 * Description:   Complete the casting of the spell
 * Arguments:     object caster   - the caster
 *                object *targets - an array of targets
 *                int *resist     - resistance percentages corresponding to
 *                                  each target
 *                int result      - how well the spell was cast
 */
public void
resolve_spell(object caster, object *targets, int *resist, int result)
{
    object ob, tar = targets[0];

    if (tar != caster)

    if (result < 5 || resist[0] > result ||
        tar->query_phearing_object())
    {
        caster->catch_tell("You close your eyes for just a moment " +
            "and chant a silent prayer. When you open your eyes again " +
            "the world is as still as it was just moments ago.\n");
        all_msgbb(QCTNAME(caster) + " chants a silent prayer for a " +
            "brief moment.\n", caster);

        return;
    }

    caster->catch_tell("You close your eyes for just a moment and chant " +
        "a silent prayer. When you open your eyes again you almost feel " +
        "overwhelmed by the myriad of sounds that are all around you.\n");
    all_msgbb(QCTNAME(caster) + " chants a silent prayer for a brief " +
        "moment.\n", caster);
        
    setuid();
    seteuid(getuid());
    ob = make_spell_effect_object(HEARING_OBJ, caster, tar, resist, result);
    ob->set_time(1200 + (caster->query_priest_level() * 60 + result));
}

/*
 * Function name: config_spell
 * Description:   configure the spell
 * Arguments:     object caster   - the caster
 *                object *targets - array of spell targets found
 *                string argument - arguments to the spell invocation
 * Returns:       1/0 - spell configured/not configured (cannot be cast)
 */
public varargs int
config_spell(object caster, object *targets, string arg)
{
    set_spell_name("precall");
    set_spell_desc("Word of Recall");

    set_spell_time(6);
    set_spell_element(SS_ELEMENT_EARTH, 14);
    set_spell_form(SS_FORM_ENCHANTMENT, 20);
    set_spell_mana(200);
    set_spell_task(TASK_ROUTINE);
    set_spell_resist(spell_resist_beneficial);
    set_spell_target(spell_target_caster);
    set_spell_target_verify(spell_verify_present);

#ifndef NO_INGREDIENTS
    set_spell_ingredients(({"perfume", "gold coin"}));
#endif

    return 0;
}
