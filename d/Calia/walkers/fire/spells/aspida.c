
  /*
   * Aspida (Flame Shield) Spell for the Firewalkers
   * by Jaacar
   * April 28th, 1998
   */

#pragma strict_types

inherit "/d/Genesis/magic/components";
inherit "/d/Genesis/magic/resist";
inherit "/d/Genesis/magic/spell_config";
inherit "/d/Genesis/magic/targeting";

#include <ss_types.h>
#include <tasks.h>
#include <stdproperties.h>
#include <filter_funs.h>
#include <cmdparse.h>
#include <macros.h>
#include "defs.h"
#include FIRE_HEADER

public void aspida(object caster, object *targets, int *resist,
    int result);
public int create_spell_aspida(object caster, object *targets,
    string argument);

public int
create_spell_aspida(object caster, object *targets, string argument)
{
    set_spell_time(2);
    set_spell_mana(80);
    set_spell_task(TASK_SIMPLE);
    set_spell_element(SS_ELEMENT_FIRE,40);
    set_spell_form(SS_FORM_CONJURATION,40);
    set_spell_ingredients(({ }));
    set_spell_effect(aspida);
    set_spell_object(ASPIDA_ARM);
    return 0;
}

public void
aspida(object caster, object *targets, int *resist, int result)
{
    if (present(ASPIDA_OBJ, caster))
    {
        caster->catch_tell("You are already protected!\n");
        return;
    }
 
    write("You are suddenly surrounded by a shimmering shield of "+
        "liquid fire.\n");
    tell_room(environment(caster), QCTNAME(caster) +" is suddenly "+
        "surrounded by a shimmering shield of liquid fire.\n",({caster}));
    make_spell_effect_object(query_spell_object(), caster, caster, 
        resist, result)->move(caster);
}