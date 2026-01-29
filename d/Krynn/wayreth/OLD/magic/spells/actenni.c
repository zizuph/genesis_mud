/*
 * Actenni
 *
 * Description: A haste spell. Will work on the caster or any friendly

 * Class:       3
 * Ingredients: licorice root
 * Mana:        175 (1/3)
* Tax:    0.7
 * Skills:      SS_ELEMENT_AIR     15
 *              SS_FORM_ABJURATION 10
 * Task:        TASK_ROUTINE
 * Restriction: Must be member and may be in combat,
 *              the caster must not be gagged.
 */
#include <ss_types.h>
#include <wa_types.h>
#include <formulas.h>
#include <tasks.h>
#include <language.h>

#define ACTENNI_OBJ "/d/Krynn/wayreth/magic/obj/actenni"

#define SUCCESSMOD caster->query_wohs_level() / 5

public void actenni_message(object caster, object *targets);

public int
create_spell_actenni(string arg)
{
    if (check_gagged())
        return 1;

    set_spell_element(SS_ELEMENT_AIR, 15);
    set_spell_form(SS_FORM_ABJURATION, 10);

    set_spell_fail(spell_wohs_fail);

    set_spell_time(3);
    set_spell_task(TASK_ROUTINE);

    set_spell_mana(175);
    set_find_target(find_one_living_friendly);
    set_spell_message(actenni_message);
    set_spell_object(ACTENNI_OBJ);
    set_spell_ingredients("licorice");
}

public int
do_actenni(string str)
{
    return cast_spell();
}

public void
actenni_message(object caster, object *targets)
{
    object tar = targets[0];
    object *effects = tar->query_magic_effects();
    int t = query_spell_result()[0];
    int size = sizeof(effects);
    
    while(size--)
    {
        if (MASTER_OB(effects[size]) == ACTENNI_OBJ)
	{
	    if(tar == caster)
	      {
	    	caster->catch_msg("Too late you discover that " +
			      "you were already " +
			      "affected by another hasting.\n");
	      }
	    caster->catch_msg("Too late you discover that "+
		QCTNAME(tar) + " was already affected by "+
		" another hasting.\n");
		
            effects[size]->dispel_magic();
	    set_spell_object(0);
	    return;
	}
    }

    tell_room(E(caster), QCTNAME(tar) + " seems to blur and shimmer " +
	"as " + tar->query_pronoun() + " starts to move very "+
	"fast!\n", ({ caster, tar })); 

    if(caster != tar)
    {
    	caster->catch_msg("You mumble words of power, lay your "+
		"hand on "+QTNAME(tar)+ "'s shoulder and step "+
		"back as "+PRONOUN(tar)+" begins to shimmer and "+
		"move as a blur.\n");
	tar->catch_msg(QCTNAME(caster) + " mumbles some words of power, "+
		"lays " + POSSESSIVE(caster) + " hands on you, and "+
		"you feel a surge of quickness and energy flow through "+
		"your body");
    }
    else
	caster->catch_msg("You mumble words of power and touch "+
		"your cheeks with your fingertips. You feel a surge "+
		"of quickness and energy flow through your body.\n");

    set_spell_duration(50 + (t * SUCCESSMOD > 600 ? 600 : t * SUCCESSMOD));
}
