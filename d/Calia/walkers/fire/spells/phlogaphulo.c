
 /*
   * Phlogaphulo (Flame Blade) Spell for the Firewalkers
   * by Bishop June 12 1999.
   * 
   */

#pragma strict_types

inherit "/d/Genesis/magic/components";
inherit "/d/Genesis/magic/resist";
inherit "/d/Genesis/magic/targeting";
inherit "/d/Genesis/magic/spell_config";

#include <stdproperties.h>
#include <filter_funs.h>
#include <ss_types.h>
#include <tasks.h>
#include <cmdparse.h>
#include <composite.h>
#include <macros.h>
#include "defs.h"
#include FIRE_HEADER

public void phlogaphulo(object caster, object *targets, int *resist,
    int result);
public int create_spell_phlogaphulo(object caster, object *targets,
    string argument);

public object *
phlogaphulo_target_caster(object caster, string str)
{
    object *weapons;  
    
    weapons = caster->query_weapon(-1);
    if (sizeof(weapons))
    {
        caster->catch_msg("You cannot summon the flame weapon if" +
            " you are already wielding a weapon.\n");
        return ({});
    }

    return ({ caster });    
}

public int 
create_spell_phlogaphulo(object caster, object *targets, string argument)
{
    set_spell_time(10);
    set_spell_mana(120);
    set_spell_task(TASK_ROUTINE);
    set_spell_element(SS_ELEMENT_FIRE, 55);
    set_spell_form(SS_FORM_CONJURATION, 55);
    set_spell_ingredients(({}));
    set_spell_resist(spell_resist_beneficial);
    set_spell_peaceful(1);
    set_spell_object(PHLOGAPHULO_WEP);
    return 0;
}

public void 
phlogaphulo(object caster, object *targets, int *resist, int result)
{
    caster->catch_msg("You complete the Phlogaphulo spell, and a great" +
        " spear of flame appears in your hands.\n");
    tell_room(environment(caster), QCTNAME(caster) + " completes " +
        caster->query_possessive() + " spell, and a great spear of flame" +
        " appears in " + caster->query_possessive() + " hands.\n", caster); 
    make_spell_effect_object(query_spell_object(), caster, caster, 
        resist, result)->move(caster);
}


