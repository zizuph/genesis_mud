/*
 * Consensus
 *
 * Description: Using this spell a mage can declare his thoughts on 
 *              who should serve as the head of the conclave.
 *              It's completely powerless. 
 * Class:       0
 * Ingredients: None
 * Mana:        80
 * Tax:         0.0
 * Skills:      SS_ELEMENT_FIRE     9
 *              SS_FORM_CONJURATION 4
 * Task:        TASK_SIMPLE
 * Restriction: Must be member and not engaged in combat,
 *              the caster must not be gagged and the caster must
 *              have something to cast the spell on, at lower level
 *              the object will disappear.
 */

#include "../guild.h"

inherit SPELL_STD;

#include <ss_types.h>
#include <tasks.h>

string target;


/* We need the target function to be called just before exection */
int query_spell_pretarget() { return 0; }


object *
conclave_target(object caster, string arg)
{
    if (!stringp(arg)) {
        write("You must specify the name of the conclave member you " + 
            "wish to support.\n");
        return 0;
    }
    
    arg = lower_case(arg);
    
    if (!ADMIN->query_conclave_member(arg))
    {
        write("There is no conclave member by the name '" + capitalize(arg) +
            "'.\n");
        return 0;
    }
    
    target = arg;
    return ({ caster });
}

public varargs int
config_spell(object caster, object *targets, string arg)
{
    set_spell_name("consensus");
    set_spell_desc("Declare your view");
    
    set_spell_element(SS_ELEMENT_AIR, 0);
    set_spell_form(SS_FORM_DIVINATION, 0);

    set_spell_time(3);
    set_spell_task(TASK_SIMPLE);

    set_spell_mana(40);
    set_spell_target(conclave_target);
    
    set_spell_peaceful(1);
    set_spell_vocal(1);
}

public void
resolve_spell(object caster, object *targets, int *resist, int result)
{
    
    caster->catch_tell("You hear a sharp click as your choice of '" +
        capitalize(target) + "' is registered.\n");
    ADMIN->set_data(caster, "consensus", target);
}
