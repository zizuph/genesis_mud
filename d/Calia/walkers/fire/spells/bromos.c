
 /*
  * Bromos spell for the Firewalkers, by Bishop 1.6.99.
  * 
  * Causes a frenzy in the target, with several effects.
  *
  * The spell object is at /d/Calia/walkers/fire/spells/bromos_obj.c,
  * where these effects are implemented and explained.
  */

#pragma strict_types

inherit "/d/Genesis/magic/components";
inherit "/d/Genesis/magic/resist";
inherit "/d/Genesis/magic/targeting";
inherit "/d/Genesis/magic/spell_config";

#include <tasks.h>
#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include "defs.h"
#include FIRE_HEADER

public void bromos(object caster, object *targets, int *resist,
    int result);
public int create_spell_bromos(object caster, object *targets,
    string argument);

public void
create_spell_bromos(object caster, object *targets, string argument)
{
    set_spell_time(3);
    set_spell_mana(110);
    set_spell_task(TASK_ROUTINE);
    set_spell_element(SS_ELEMENT_FIRE, 45);
    set_spell_form(SS_FORM_ENCHANTMENT, 45);
    set_spell_ingredients(({ }));
    set_spell_resist(spell_resist);
    set_spell_target_verify(spell_verify_present);
    set_spell_effect(bromos);
    set_spell_object(BROMOS_OB);
    return 0;
}

public void
bromos(object caster, object *targets, int *resist, int result)
{
    if (random(100) < resist[0])
    {
        caster->catch_tell("You complete the spell, but it seems to have "+
            "no effect.\n");
        return;
    }
    
    if (present("_bromos_obj_", targets[0]))
    {
        caster->catch_tell("You complete the spell, but it has no" +
            " effect, as your target is already under the effects of" +
            " this enchantment.\n");
        return;
    }

    setuid();
    seteuid(getuid());

    make_spell_effect_object(query_spell_object(), caster, targets[0], 
        resist, result)->move(targets[0]);
}
