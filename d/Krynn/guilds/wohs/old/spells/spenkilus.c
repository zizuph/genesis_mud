/*
 * Spenkilus - Hands of Washing
 *
 * Class:	0
 * Ingredients:	water
 * Mana:	5
 * Tax:		0.05		(a "feeling" spell)
 * Skills:	SS_ELEMENT_WATER, 2
 *		SS_ELEMENT_CONJURATION, 5
 * Task:	TASK_SIMPLE
 */

#include <ss_types.h>
#include <macros.h>
#include <tasks.h>


#include "../guild.h";
#include "/d/Krynn/common/defs.h"

inherit SPELL_STD;

#define LIVE_I_DIRTY	"_live_i_dirty"

public varargs int
config_spell(object caster, object *targets, string arg)
{
    set_spell_name("spenkilus");
    set_spell_desc("Scrubbing Hands");

    set_spell_element(SS_ELEMENT_WATER, 5);
    set_spell_form(SS_FORM_CONJURATION, 10);
    
    set_spell_time(3);
    set_spell_task(TASK_SIMPLE);
    set_spell_mana(5);

    set_spell_target(spell_target_one_present_living);
    set_spell_ingredients(({ "water" }));

    set_spell_vocal(1);
    set_spell_peaceful(1);
}

public void
resolve_spell(object caster, object *targets, int *resist, int result)
{
    object tar = targets[0];
    
    object filthy = present("dirty",tar);
    
    if(objectp(filthy))
    {
        filthy->remove_object();
	tar->remove_prop(LIVE_I_DIRTY);
    }
    
    if (tar->query_dirty_shadow() == 666) 
        tar->remove_shire_dirty_shadow();
    
    
    if (caster != tar)
    {
    	caster->catch_msg("You mumble words of power along with some "+
            "impressive looking arcane guestures and with one "+
            "hand, plug your nose, and point the other towards "+
            QCTNAME(tar)+ ".\n"+
            "Suddenly, a pair of watery hands dripping with "+
            "suds begins to vigorously scrub " +QTNAME(tar)+
            " until " +PRONOUN(tar)+ " is a clean and wet "+
            tar->query_race_name() +".\n");
	tar->catch_msg(QCTNAME(caster) + " mumbles some words of power, "+
            "along with some arcane guestures and then with one "+
            "hand, plugs " +POSSESSIVE(caster)+ " nose and points "+
            "the other at you!\n"+
            "Suddenly, a pair of watery hands dripping with suds "+
            "attacks you!\n"+
            "After a few wild and fruitless swings, you realize "+
            "that the hands are merely scrubbing you clean and "+
            "you stand there looking fresh and rather wet.\n");
        
        tell_room(E(caster), QCTNAME(caster) + " mumbles some words "+
            "of power along with some arcane guestures and then with "+
            "one hand, plugs " +POSSESSIVE(caster)+ " nose and points "+
            "the other at " +QTNAME(tar)+".\n"+
            "Suddenly, a pair of watery hands dripping with suds "+
            "attacks " +QTNAME(tar)+"!\n"+
            "After a moment of spraying water, frothing foam, and blubbered "+
            tar->query_race_name()+ " swear words, you realize that "+
            PRONOUN(tar)+ " has merely been washed and scrubbed rather "+
            "vigorously!\n", ({ caster, tar }) );
    }
    else
    {
	caster->catch_msg("You mumble words of power and make some "+
            "impressive looking arcane guestures and with one "+
            "hand, plug your nose and cover your eyes with the "+
            "other.\n"+
            "Suddenly, a pair of watery hands dripping with "+
            "suds decends upon you and starts to vigorously "+
            "scrub and wash any dirtiness from you.\n");
        
        tell_room(E(caster), QCTNAME(caster) + " mumbles some words "+
            "of power along with some arcane guestures and then with "+
            "one hand, plugs " +POSSESSIVE(caster)+ " nose and covers "+
            POSSESSIVE(caster)+ " eyes with the other.\n"+
            "Suddenly, a pair of watery hands dripping with suds "+
            "attacks " +QTNAME(tar)+"!\n"+
            "After a moment of spraying water, frothing foam, and blubbered "+
            tar->query_race_name()+ " swear words, you realize that "+
            PRONOUN(tar)+ " has merely been washed and scrubbed rather "+
            "vigorously!\n", ({ caster, }) );
    }
}
