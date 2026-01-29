
 /*
  * Tuphlono (Eyes Of Dust) Spell for the Stonewalkers
  * by Jaacar
  * November 7th, 1998
  */

#pragma strict_types

inherit "/d/Genesis/magic/components";
inherit "/d/Genesis/magic/resist";
inherit "/d/Genesis/magic/targeting";
inherit "/d/Genesis/magic/spell_config";

#include <tasks.h>
#include <stdproperties.h>
#include <filter_funs.h>
#include <ss_types.h>
#include <macros.h>
#include "defs.h"
#include STONE_HEADER

public void tuphlono(object caster, object *targets, int *resist,
    int result);
public int create_spell_tuphlono(object caster, object *targets,
    string argument);

public void
create_spell_tuphlono(object caster, object *targets, string argument)
{
    set_spell_time(1);
    set_spell_mana(46);
    set_spell_task(TASK_ROUTINE);
    set_spell_element(SS_ELEMENT_EARTH,30);
    set_spell_form(SS_PRAYER,30);
    set_spell_ingredients(({"laminaria","salt"}));
    set_spell_resist(spell_resist);
    set_spell_target_verify(spell_verify_present);
    set_spell_effect(tuphlono);
    set_spell_object(TUPHLONO_OB);
    return 0;
}

public void
tuphlono(object caster, object *targets, int *resist, int result)
{
    if (random(100) < resist[0])
    {
        caster->catch_tell("You complete the spell, but it seems to have "+
            "no effect.\n");
        return;
    }
    
    caster->catch_tell("You concentrate on the image of "+targets[0]->query_the_name(caster)+
        " and call upon the powers of Tuphlono.  "+targets[0]->query_The_name(caster)+
        " appears to fumble slightly, and can no longer see.\n");
    tell_room(environment(caster),QCTNAME(caster)+" closes "+C_HIS+
        " eyes in concentration.  "+QCTNAME(targets[0])+" begins "+
        "to stumble around as though blind.\n",({caster,targets[0]}));
    targets[0]->catch_tell(caster->query_The_name(targets[0])+" closes "+C_HIS+" eyes "+
        "in concentration.  Dust fills your eyes suddenly, leaving "+
        "you blinded!\n");
    caster->attack_object(targets[0]);  // Just in case they aren't fighting yet.
    make_spell_effect_object(query_spell_object(), caster, targets[0], resist, 
        result);
    
}
