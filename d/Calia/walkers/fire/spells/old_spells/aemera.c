
 /*
   * Aemera (Daylight) Spell for the Firewalkers
   * by Jaacar
   * June 12th, 1997
   * Converted to new spell system May 19th, 1998
   */

#pragma strict_types

inherit "/d/Genesis/magic/components";
inherit "/d/Genesis/magic/resist";
inherit "/d/Genesis/magic/targeting";
inherit "/d/Genesis/magic/spell_config";

#include <tasks.h>
#include <stdproperties.h>
#include <filter_funs.h>
#include <macros.h>
#include <ss_types.h>
#include "defs.h"
#include FIRE_HEADER

public void aemera(object caster, object *targets, int *resist,
    int result);
public int create_spell_aemera(object caster, object *targets,
    string argument);

public int
create_spell_aemera(object caster, object *targets, string argument)
{
    set_spell_time(2);
    set_spell_mana(88);
    set_spell_task(TASK_ROUTINE);
    set_spell_element(SS_ELEMENT_FIRE, 40);
    set_spell_form(SS_PRAYER, 40);
    set_spell_ingredients(({"obsidian","laminaria"}));
    set_spell_effect(aemera);
    set_spell_object(AEMERA_OB);
    return 0;
}

public void
aemera(object caster, object *targets, int *resist, int result)
{
    if (present(AEMERA_OBJ,caster))
    {
        write("You are already surrounded by light!\n");
        return;
    }
    caster->catch_tell("Your flesh begins to glow, dimly at first, then "+
        "the light engulfs your entire body making you appear fashioned "+
        "entirely out of light.\n");
    tell_room(environment(caster),QCTNAME(caster)+"'s flesh begins "+
        "to glow, dimly at first, until "+C_HE+" appears fashioned "+
        "from light.\n",({caster}));
    make_spell_effect_object(query_spell_object(), caster, caster, 
        resist, result)->move(caster,1);
    return;
}

