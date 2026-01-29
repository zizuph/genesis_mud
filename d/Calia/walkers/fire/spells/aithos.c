/*

Aithos spell for the Firewalkers, coded 24.6.99 by Bishop of Calia.

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

public void aithos(object caster, object *targets, int *resist,
    int result);
public int create_spell_aithos(object caster, object *targets,
    string argument);

public void
create_spell_aithos(object caster, object *targets, string argument)
{
    set_spell_time(6);
    set_spell_mana(180);
    set_spell_task(TASK_ROUTINE);
    set_spell_element(SS_ELEMENT_FIRE, 60);
    set_spell_form(SS_FORM_CONJURATION, 60);
    set_spell_ingredients(({ }));
    set_spell_resist(spell_resist);
    set_spell_target_verify(spell_verify_present);
    set_spell_effect(aithos);
    set_spell_offensive(1);
    set_spell_object(AITHOS_OBJ);
    return 0;
}

public void
aithos(object caster, object *targets, int *resist, int result)
{
    if (random(100) < resist[0])
    {
        caster->catch_tell("You complete the spell, but it seems to have "+
            "no effect.\n");
        return;
    }

    setuid();
    seteuid(getuid());

    make_spell_effect_object(query_spell_object(), caster, targets[0], 
        resist, result)->move(targets[0], 1);
}