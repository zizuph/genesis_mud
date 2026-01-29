
 /*
   * Stoiecheio (Elemental Form) Spell for the Windwalkers
   * by Jaacar
   * April 24th, 1998
   */

#pragma strict_types

inherit "/d/Genesis/magic/components";
inherit "/d/Genesis/magic/resist";
inherit "/d/Genesis/magic/targeting";
inherit "/d/Genesis/magic/spell_config";

#include <ss_types.h>
#include <tasks.h>
#include <stdproperties.h>
#include <filter_funs.h>
#include <macros.h>
#include "defs.h"
#include WIND_HEADER

public void stoiecheio(object caster, object *targets, int *resist, 
    int result);
public int create_spell_stoiecheio(object caster, object *targets,
    string argument);

public object *
stoiecheio_target_caster(object caster, string str)
{
    if (!present("_stoiecheio_potion_object_",caster))
    {
        write("You are not under the effects of the stoiecheio "+
            "potion!\n");
        return ({});
    }
    
    return ({ caster });
}

public int
create_spell_stoiecheio(object caster, object *targets, string argument)
{
    set_spell_time(2);
    set_spell_mana(150);
    set_spell_task(TASK_ROUTINE);
    set_spell_element(SS_ELEMENT_AIR,50);
    set_spell_form(SS_PRAYER,50);
    set_spell_ingredients(({ })); // Uses a potion
    set_spell_resist(0);
    set_spell_peaceful(1);
    set_spell_effect(stoiecheio);
    set_spell_object(STOIECHEIO_OB);
    return 0;
}

public void
stoiecheio(object caster, object *targets, int *resist, int result)
{
    if (present("stoiecheio_obj",caster))
    {
        write("You are already in elemental form!\n");
        return;
    }
  
    write("Concentrating all of your efforts on the task, you "+
        "succesfully chant the mantras of Stoiecheio.  You entire body "+
        "is surrounded by winds enveloping everything you own, yet not "+
        "harming anything.\n");
    tell_room(environment(caster),QCTNAME(caster)+" is suddenly and violently "+
        "consumed in a gigantic twister of air.\n",({caster}));
    seteuid(getuid());
    make_spell_effect_object(query_spell_object(), caster, caster, resist,
        result)->move(caster,1);
}

