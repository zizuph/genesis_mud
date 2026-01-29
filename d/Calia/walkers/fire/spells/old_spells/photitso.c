
 /*
   * Photitiso (Light) Spell for the Firewalkers
   * by Jaacar
   * June 12th, 1997
   * Converted to new spell system August 28th, 1998
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
    set_spell_form(SS_PRAYER, 20);
    set_spell_ingredients(({"salt","sulphur"}));
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
            write("Your hand is already surrounded by light!\n");
            return;
        }
        caster->catch_tell("Your hand is suddenly surrounded by a blazing "+
            "light.\n");
        tell_room(environment(caster),"A steady flame starts to burn in "+
            QCNAME(TP)+"'s outstretched palm, casting the area in dim "+
            "light.\n",({caster}));
        make_spell_effect_object(query_spell_object(), caster, caster, 
            resist, result)->move(caster,1);
        return;
    }

    if (present(PHOTITSO_OBJ, targets[0]))
    {
        write("Their hand is already surrounded by light!\n");
        return;
    }
    targets[0]->catch_tell(caster->query_The_name(targets[0])+" nods slightly in your "+
        "direction.  Suddenly your hand is surrounded by a blazing light.\n");
    caster->catch_tell("You nod slightly towards "+targets[0]->query_the_name(caster)+
        ".  Suddenly "+TS_HIS+" hand is surrounded by a blazing light.\n");
    tell_room(environment(caster),QCTNAME(caster)+" nods slightly at "+
        QTNAME(targets[0])+".  Suddenly, "+TS_HIS+" hand is surrounded "+
        "by a blazing light.\n",({caster,targets[0]}));
    make_spell_effect_object(query_spell_object(), caster, targets[0], 
        resist, result)->move(targets[0],1);
}

