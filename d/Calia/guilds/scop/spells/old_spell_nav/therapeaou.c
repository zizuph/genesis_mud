 
/*
 * therapeaou.c
 *
 * Therapeaou (Cure Wounds) spell for the Spirit Circle of Psuchae
 * This is the heal spell for the guild.
 *
 * Copyright (C): Jaacar, July 30th, 2003
 *
 * Balance Review Done By Shiva - September 2003
 *
 * Various changes, Bishop April 2004.
 */
 
#pragma strict_types
#pragma save_binary

inherit "/d/Genesis/newmagic/spells/heal.c";

#include <ss_types.h>
#include <options.h>
#include <tasks.h>
#include <macros.h>
#include <composite.h>
#include <cmdparse.h>

#include "defs.h"
#include SPIRIT_HEADER

object comp;

string
query_spell_level()
{
    return "Master";
}

/*
    Use the custom targeting function here to introduce the gem possibly
    surviving a casting of the spell. Otherwise this is identical to 
    spell_target_one_present_living from newmagic/targeting.c.
    
*/
public object *
special_target_one_present_living(object caster, string str)
{
    object *oblist;
    
    object *gems = filter(deep_inventory(caster), &operator(==)("pearl") @ 
        &->query_gem_name());

    if (!sizeof(gems))
    {
        caster->catch_tell("You need a white pearl in order to successfully" +
            " cast this spell!\n");
        return ({ });
    }
    
    comp = gems[0];
        
    if (!strlen(str))
    {
        return ({ caster });
    }

    parse_command(str, ({}), "[at] / [on] [the] %s", str);
    oblist = PARSE_THIS(str, "%l");

    if (!sizeof(oblist))
    {
	if ((str == "me") || (str == "myself") || 
            (str == caster->query_real_name()))
	{
	    return ({ caster });
	}

	caster->catch_tell("There is no " + str + " here.\n");
	return ({});
    }

    if (sizeof(oblist) > 1)
    {
        caster->catch_tell("You will have to be more specific!  You can only " +
            "select one target.\n");
        return ({});
    }


        
    return oblist;
}




/*
 * Function name: config_spell
 * Description:   configure the spell
 * Arguments:     object caster   - the caster
 *                object *targets - array of spell targets found
 *                string argument - arguments to the spell invocation
 * Returns:       1/0 - spell configured/not configured (cannot be cast)
 */

public varargs int
config_spell(object caster, object *targets, string argument)
{
    set_spell_name("therapeaou");
    set_spell_desc("Cure Wounds");
    set_spell_time(3);
    set_spell_mana(100);
    set_spell_vocal(0);
    set_spell_visual(0);
    set_spell_ingredients(({}));
    set_spell_task(TASK_ROUTINE - caster->query_casting_bonus());
    set_spell_element(SS_ELEMENT_LIFE, 40);
    set_spell_form(SS_FORM_ENCHANTMENT, 40);
    add_element_resistance(SS_ELEMENT_LIFE, MAGIC_I_RES_LIFE);
    set_spell_target(special_target_one_present_living);
    set_spell_target_verify(spell_verify_present);
    if (caster->query_intoxicated())
    {
        caster->catch_msg("You cannot use Psuchae's gifts while intoxicated!\n");
        return 1;
    }
    if (caster->query_alignment() < 0)
    {
        caster->catch_msg("You cannot use Psuchae's gifts while you are not "+
            "good aligned.\n");
        return 1;
    }
    ::config_spell(caster, targets, argument);
    return 0;
}

/*
 * Function name: concentrate_msg
 * Description:   Give messages indicating that spell concentration has begun
 * Arguments:     1. (object)   The caster
 *                2. (object *) The targets
 *                3. (string)   The arguments passed to the "cast" command
 */

public void
concentrate_msg(object caster, object *targets, string arg)
{

    caster->catch_tell("You mentally call upon Psuchae for power.\n");
    say(QCTNAME(caster) + " appears to concentrate deeply.\n");
}

/*
 * Function name: desc_heal
 * Description:   Describe the spell casting and effect.
 *                This can be redefined for custom messages.
 * Arguments:     object caster - the caster
 *                object *targets - the targets
 *                int *heal - Healing in hps for each target
 */
public void
desc_heal(object caster, object *targets, int *heal)
{
    int i, index;
    string who;

    if ((index = member_array(caster, targets)) >= 0)
    {
        who = COMPOSITE_WORDS (map(targets - ({ caster }),
            &->query_the_name(caster)) + ({ "yourself" }));
    }
    else
    {
        who = FO_COMPOSITE_ALL_LIVE(targets, caster);
    }
    

    caster->catch_tell("You aid " + who + " with your healing powers.\n");

    for (i = 0; i < sizeof(targets); i++)
    {
        if ((heal[i] < 1) ||
            (targets[i]->query_hp() >= targets[i]->query_max_hp()))
        {
	    targets[i]->catch_tell("A pleasant warmth briefly overcomes " +
                "you and quickly fades.\n");
	    }
	    else
	    {
	        targets[i]->catch_tell("A pleasant warmth briefly overcomes " +
                "you as you feel your injuries healing.\n");
	    }
    }
}

/*
 * Function name: resolve_spell
 * Description:   Complete the casting of the spell
 * Arguments:     object caster   - the caster
 *                object *targets - an array of targets
 *                int *resist     - resistance percentages corresponding to
 *                                  each target
 *                int result      - how well the spell was cast
 */
public void
resolve_spell(object caster, object *targets, int *resist, int result)
{
    int i, guild_stat, wisdom, base, old_val, new_val;
    int *heal = allocate(sizeof(targets));
    
    guild_stat = caster->query_stat(SS_LAYMAN);
    wisdom = caster->query_stat(SS_WIS);

    base = 2*guild_stat + wisdom + caster->query_casting_bonus();
    base = MAX(base, 100);
    base = base + random(base)/2 + random(base)/2;

    if (base > 600)
    {
        //Diminishing returns over 600. 
        base = 600 + (base - 600)/3;
    }

    if ((random(1000) == 0))       // critical heal as per Shiva's idea
        base +=random(600);

    set_heal_amount(base);

    old_val = caster->query_skill(SS_SPELLS_CASTED);
    new_val = MIN(CASTED_LIMIT, (old_val + 4));
    caster->set_skill(SS_SPELLS_CASTED, new_val);

    if (caster->query_wiz_level())
    {
        caster->catch_tell("Amount = "+base+".\n");
    }    

    for (i = 0; i < sizeof(heal); i++)
    {
        if (targets[0] == caster)
        {
            //Don't resist your own spell:
            heal[i] = query_heal_amount(caster, targets[i]);
        }
        else
        {
            heal[i] = (100 - resist[i]) *
                query_heal_amount(caster, targets[i]) / 100;
        }
        targets[i]->heal_hp(heal[i]);
    }


    desc_heal(caster, targets, heal);

    setuid();
    seteuid(getuid());
    write_file(SPIRIT_LOGS + "therapeaou_heal_log", ctime(time()) + ": " + 
        caster->query_name() + " cast therapeaou, healing " + base + " hp.\n");    
    
    if (random(100) >= 90)
    {
            caster->catch_tell("You sacrificed a white pearl.\n");
            comp->set_heap_size(comp->num_heap() - 1);
    }       
}

