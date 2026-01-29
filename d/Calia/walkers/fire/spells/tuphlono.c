
 /*
  * Tuphlono (Blinding Flash) Spell for the Firewalkers
  * by Jaacar
  * April 28th, 1998
  * Descriptions and spell form changed April 9th 1999, Bishop.
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
#include FIRE_HEADER

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
    set_spell_element(SS_ELEMENT_FIRE,30);
    set_spell_form(SS_FORM_CONJURATION,30);
    set_spell_ingredients(({ }));
    set_spell_resist(spell_resist);
    set_spell_target_verify(spell_verify_present);
    set_spell_effect(tuphlono);
    set_spell_offensive(1);
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

    if (present("_tuphlono_obj_", targets[0]))
    {
        caster->catch_tell("Your spell has no effect, as the target" +
            " is already blinded.\n");
        return;
    }
    
    caster->catch_tell("You concentrate on the image of " +
        targets[0]->query_the_name(caster)+
        " and complete the Tuphlono spell. A small, intense ball of light" +
        " appears in your hand. With a flick of your wrist, you send it" +
        " at the eyes of " + targets[0]->query_the_name(caster) +
        ", blinding " + targets[0]->query_objective() + ".\n");
    tell_room(environment(caster), "A small, intense ball of light appears" +
        " in " + caster->query_the_name(targets[0]) + "'s hand. With a" +
        " flick of " +
        caster->query_possessive() + " wrist, " + caster->query_pronoun() +
        " sends the ball at the" +
        " eyes of " + targets[0]->query_the_name(caster) + ", causing" +
        " blindness!\n", ({caster,targets[0]}));
    targets[0]->catch_tell("A small, intense ball of light appears in " +
        caster->query_the_name(targets[0]) + "'s hand. With a flick of " +
        caster->query_possessive() + " wrist, " + caster->query_pronoun() +
        " sends the ball right at your eyes, blinding you!\n");
    make_spell_effect_object(query_spell_object(), caster, targets[0], resist, 
        result)->move(targets[0]);
    
}
