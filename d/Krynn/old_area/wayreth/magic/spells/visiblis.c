/*
 * Visiblis
 * Description: A potent darkvision spell with a decent duration, will fade 
 *		    away after a while.
 * Class:       3
 * Ingredients: celery and an eye
 * Mana:        60 (1/3)
 * Tax:    	    0.1
 * Skills:      SS_ELEMENT_FIRE     10
 *              SS_FORM_ABJURATION  15
 * Task:        TASK_ROUTINE
 * Restriction: Must be member and may be in combat,
 *              the caster must not be gagged.
 */
#include <ss_types.h>
#include <wa_types.h>
#include <formulas.h>
#include <tasks.h>
#include <language.h>

#define VISIBLIS_OBJ "/d/Krynn/wayreth/magic/obj/visiblis"

public void visiblis_message(object caster, object *targets);

public int
create_spell_visiblis(string arg)
{
    
    if (check_gagged())
        return 1;

    set_spell_element(SS_ELEMENT_FIRE, 10);
    set_spell_form(SS_FORM_ABJURATION, 15);

    set_spell_fail(spell_wohs_fail);

    set_spell_time(3);
    set_spell_task(TASK_ROUTINE);

    set_spell_mana(50);
    set_find_target(find_one_living_friendly);
    set_spell_message(visiblis_message);
    set_spell_object(VISIBLIS_OBJ);
    set_spell_ingredients(({"celery", "eye"}));
}

public int
do_visiblis(string str)
{
    return cast_spell();
}

public void
visiblis_message(object caster, object *targets)
{
    object tar = targets[0];
    object *effects = tar->query_magic_effects();
    int t = query_spell_result()[0];
    int size = sizeof(effects);
    
    while(size--)
    {
        if (MASTER_OB(effects[size]) == VISIBLIS_OBJ)
	{
	    caster->catch_msg("You realise that this " +
			      "persons eyes allready is " +
			      "enchanted. What a waste of power.\n");
            effects[size]->dispel_magic();
	    set_spell_object(0);
	    return;
	}
    }

   if(tar==caster)
	{
	tell_room(E(caster), QCTNAME(caster) + " utters an arcane "+
	"word while touching " +HIS(tar) + " eyes.\n", ({ caster, tar })); 
	
	caster->catch_msg("You utter an arcane word while touching "+
		"your eyes, "+
		"bestowing the gift of seeing in darkness upon yourself. \n");
	}
	else
	{
	tell_room(E(caster), QCTNAME(caster) + " utter an arcane "+
	"word while leaning to touch " +QTNAME(tar) + "s eyes.\n", ({ caster, tar })); 

	caster->catch_msg("You utter an arcane word while leaning to "+
		"touch "+QTNAME(tar)+ "'s eyes, "+
		"bestowing the gift of seeing in darkness. \n");
       tar->catch_msg(QCTNAME(caster) + " utters an arcane word "+
		"while leaning forth to touch your eyes. You feel your "+
		"vision change.\n");
	}

    set_spell_duration(240 + (t > 1000 ? 1000 : t));
}
