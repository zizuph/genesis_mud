/*
 * Merak
 *
 * Description: A simple light spell
 * Class:       2
 * Ingredients: two copper coins
 * Mana:        40 (1/3)
 * Tax:         0.1
 * Skills:      SS_ELEMENT_FIRE     3
 *              SS_FORM_CONJURATION 4
 * Task:        TASK_SIMPLE
 * Restriction: Must be member and not engaged in combat,
 *              the caster must not be gagged and the caster must
 *              have something to cast the spell on, at lower level
 *              the object will disappear.
 */
#include <ss_types.h>
#include <wa_types.h>
#include <formulas.h>
#include <macros.h>
#include <tasks.h>
#include <language.h>

#include "../guild.h";
#include "/d/Krynn/common/defs.h"

inherit SPELL_STD;

public varargs int
config_spell(object caster, object *targets, string arg)
{
    set_spell_name("merak");
    set_spell_desc("Halo");
    
    set_spell_element(SS_ELEMENT_FIRE, 3);
    set_spell_form(SS_FORM_CONJURATION, 4);

    set_spell_time(3);
    set_spell_task(TASK_SIMPLE);

    set_spell_mana(40);
    set_spell_target(spell_target_one_present_non_living);
    
    set_spell_peaceful(1);
    set_spell_vocal(1);
}

public void
resolve_spell(object caster, object *targets, int *resist, int result)
{
    object ob;
    object tar = targets[0];
    object *effects = tar->query_magic_effects();
    int size;

    size = sizeof(effects);
    
    while(size--)
    {
        if (MASTER_OB(effects[size]) == SPELL_OBJ + "merak")
	{
	    caster->catch_msg("Too late you discover that the " +
			      tar->query_name() + " already was " +
			      "affected by another halo spell.\n");
	    tell_room(E(caster), "The " + tar->query_name() +
		      " disappears in a puff of smoke.\n");
	    tar->remove_object();
	    set_spell_object(0);
	    return;
	}
    }

    tell_room(E(caster), QCTNAME(caster) + " starts to form a glowing " +
        "halo around the " + tar->short() + ".\n", caster); 
    
    caster->catch_msg("You form a glowing halo around the " + 
        tar->short() + ".\n");
    
    if (tar->query_prop(OBJ_M_NO_GET) || tar->query_prop(OBJ_M_NO_DROP) ||
	tar->query_prop(OBJ_I_HIDE) || tar->query_prop(OBJ_I_INVIS) ||
	tar->query_prop(OBJ_I_NO_MAGIC))
    {
        tell_room(E(caster), "The halo vanishes as soon as it is " +
            "complete.\n");
	return;
    }
    
    
    ob = make_spell_effect_object(SPELL_OBJ + "merak", caster, tar, 0, 
        result);
    ob->set_spell_duration(240 + (result > 1000 ? 1000 : result) * 2);
}






