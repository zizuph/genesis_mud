/*

Ektomon spell for the Firewalkers, coded by Bishop 23.6.99.

*/

#pragma strict_types

inherit "/d/Genesis/magic/components";
inherit "/d/Genesis/magic/resist";
inherit "/d/Genesis/magic/targeting";
inherit "/d/Genesis/magic/spell_config";

#include <ss_types.h>
#include <tasks.h>
#include <macros.h>
#include <stdproperties.h>
#include <filter_funs.h>
#include "defs.h"
#include FIRE_HEADER

public void ektomon(object caster, object *targets, int *resist,
    int result);
public int create_spell_ektomon(object caster, object *targets,
    string argument);

public int
create_spell_ektomon(object caster, object *targets, string argument)
{
    set_spell_time(5);
    set_spell_mana(220);
    set_spell_task(TASK_ROUTINE);
    set_spell_element(SS_ELEMENT_FIRE, 80);
    set_spell_form(SS_FORM_ENCHANTMENT, 60);
    set_spell_ingredients(({ }));
    set_spell_object(EKTOMON_OBJ);
    return 0;
}

public void
ektomon(object caster, object *targets, int *resist, int result)
{
    if (present("_ektomon_obj_", environment(caster)))
    {
        caster->catch_msg("This area has already been bestowed with the" +
            " Ektomon enchantment.\n");
        return;
    }

    caster->catch_msg("You complete the Ektomon enchantment and a red haze" +
        " spreads through the area as the heat here increases manyfold. The" +
        " haze is accompanied by a faint smell of sulphur.\n");
    tell_room(environment(caster), QCTNAME(caster) + " completes the spell" +
        " and a red haze spreads through the area as the heat here increases" +
        " manyfold. The haze is accompanied by the faint smell of sulphur.\n",
        caster);

    seteuid(getuid());
    make_spell_effect_object(query_spell_object(), caster, caster, 
        resist, result)->move(environment(caster));
}