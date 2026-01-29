/*
 * Melberentis
 *
 * Description: A slow spell. Will work on anyone, and will initiate combat

 * Class:       3
 * Ingredients: honey
 * Mana:        175 (1/3)
 * Tax:		0.7
 * Skills:      SS_ELEMENT_DEATH   15
 *              SS_FORM_CONJURATION 10
 * Task:        TASK_ROUTINE
 * Restriction: Must be member and may be in combat,
 *              the caster must not be gagged.
 */
#include <ss_types.h>
#include <wa_types.h>
#include <formulas.h>
#include <tasks.h>
#include <language.h>

#define MELBERENTIS_OBJ "/d/Krynn/wayreth/magic/obj/melberentis"

#define SUCCESSMOD caster->query_wohs_level() / 5

public void melberentis_message(object caster, object *targets);

public int
create_spell_melberentis(string arg)
{
    if (check_gagged())
        return 1;

    set_spell_element(SS_ELEMENT_DEATH, 15);
    set_spell_form(SS_FORM_CONJURATION, 10);

    set_spell_fail(spell_wohs_fail);

    set_spell_time(3);
    set_spell_task(TASK_ROUTINE);

    set_spell_offensive(); /* We initiate combat, but no direct damage */
    set_spell_mana(180);
    set_find_target(find_one_living_target);
    set_spell_message(melberentis_message);
    set_spell_object(MELBERENTIS_OBJ);
    set_spell_ingredients("honey");
}

public int
do_melberentis(string str)
{
    return cast_spell();
}

public void
melberentis_message(object caster, object *targets)
{
    object tar = targets[0];
    object *effects = tar->query_magic_effects();
    int t = query_spell_result()[0],
	 res = MAX(tar->query_magic_res(MAGIC_I_RES_MAGIC),
		tar->query_magic_res(MAGIC_I_RES_DEATH));
    int size = sizeof(effects);
    
    while(size--)
    {
      /* The order of these two checks should be inconsequential as */
      /* having one should mutually take out the other */
      	if (MASTER_OB(effects[size]) == ACTENNI_OBJ)
	  {
		caster->catch_msg("You cancel out the "+
			"haste effect on " + QTNAME(tar) +
			" with your MelbeRentis spell.\n");
		effects[size]->dispel_magic();
		set_spell_object(0);
		return;
	  }
        if (MASTER_OB(effects[size]) == MELBERENTIS_OBJ)
	{
	    caster->catch_msg("Too late you discover that "+
		QCTNAME(tar) + " was already affected by "+
		" another slow spell.\n");
		
            effects[size]->dispel_magic();
	    set_spell_object(0);
	    return;
	}
    }

    if(random(101) < random(res))
      {
	caster->catch_tell("Somehow your target seems to resist your spell!\n");
        tar->catch_tell("You feel the aura of death wash over you, but you "+
		"somehow resist!\n"); 
	set_spell_object(0);
	return;
      }

    tell_room(E(caster), QCTNAME(caster) + " mumbles some words of "+
	"power and reaches forward to touch " +QTNAME(tar) + " who "+
	"seems to stumble for a second and continues moving, but "+
	"in a sluggish, lethargic manner!\n", ({ caster, tar })); 

    caster->catch_msg("You mumble words of power, reach over and "+
		"brush your hand against "+QTNAME(tar)+ "'s body "+
		"and step back as "+PRONOUN(tar)+" stumbles and starts "+
		"to move much more slowly than before.\n");
    tar->catch_msg(QCTNAME(caster) + " mumbles some words of power, "+
		"steps forward, and brushes " + POSSESSIVE(caster) +
		" hand against you. You feel a sudden jolt as your body "+
		"appears to be moving much slower than normal and it seems "+
		"that the rest of the world is moving much more quickly "+
		"than you can bring yourself to\n");
    set_spell_duration(50 + (t * SUCCESSMOD > 600 ? 600 : t * SUCCESSMOD));
}
