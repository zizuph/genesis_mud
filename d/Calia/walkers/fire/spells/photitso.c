
 /*
   * Photitiso (Light) Spell for the Firewalkers
   * by Jaacar
   * June 12th, 1997
   * Converted to new spell system August 28th, 1998
   * Bishop, April 9th, 1999:
   * Description changed, made only possible target self.
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

public void photitso(object caster, object *targets, int *resist,
    int result);
public int create_spell_photitso(object caster, object *targets,
    string argument);

public int
create_spell_photitso(object caster, object *targets, string argument)
{
    set_spell_time(2);
    set_spell_mana(24);
    set_spell_task(TASK_SIMPLE);
    set_spell_element(SS_ELEMENT_FIRE, 20);
    set_spell_form(SS_FORM_CONJURATION, 20);
    set_spell_ingredients(({ }));
    set_spell_effect(photitso);
    set_spell_object(PHOTITSO_OB);
    return 0;
}

public void
photitso(object caster, object *targets, int *resist, int result)
{
    if (targets[0] == caster)
    {
        if (present(PHOTITSO_OBJ,caster))
        {
            write("You have already summoned the flame!\n");
            return;
        }
        caster->catch_tell("A steady flame starts to burn in the air above" +
            " your outstretched palm, casting the area in dim light.\n");
        tell_room(environment(caster),"A steady flame starts to burn in"+
            " the air above " +QCNAME(caster)+"'s outstretched palm, casting" +
            " the area in dim light.\n",({caster}));
        make_spell_effect_object(query_spell_object(), caster, caster, 
            resist, result)->move(caster,1);
        return;
    }
    else
    {
        write("You can only target yourself with this spell.\n");
        return;
    }
}

