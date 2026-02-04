/*
 *
 *  Delve
 *
 *  For spell effect description, see doc/delve.txt
 *
 *  Created May 2008, by Novo
 *  Modifications:
 *    October 2009 - Changed argument list for config_spell since base
 *                   spell.c was changed. - Petros
 */

#pragma strict_types

#include "../guild.h"

inherit SPELL_DIR+"blood_spell";

#include <ss_types.h>
#include <tasks.h>
#include <stdproperties.h>
#include <composite.h>
#include <filter_funs.h>
#include <macros.h>

#define HIT_DESC       ({ \
    "This barely qualifies as a weapon.", \
    "This might serve as a weapon, though not well at all.", \
    "It will require some luck to land a blow with this weapon.", \
    "This weapon could land a blow or two.", \
    "This weapon gives you an average chance of hitting your target.", \
    "This is an able weapon, apt to strike its target.", \
    "This weapon is more likely to strike than to miss its target.", \
    "It would require a lot of skill to avoid being struck by this " + \
    "weapon.", \
    "With this weapon, you are almost guaranteed to strike.", \
    "This weapons strikes true, and would never miss its mark.", \
    })

#define PEN_DESC       ({ \
    "This weapon couldn’t hurt a fly.", \
    "This weapon might just cause a bruise or a little pinprick.", \
    "It would take a lucky hit for this weapon to sting.", \
    "With this weapon, you could hurt somebody.",\
    "This weapon deals average damage.",\
    "This weapon would likely hurt your target.",\
    "This weapon is a hard-hitter.",\
    "This weapon would seriously wound your target.", \
    "This is a deadly weapon.", \
    "This weapon is absolutely lethal, capable of killing with a single "+\
    "blow.", \
    })

#define ARM_DESC ({ \
    "This barely qualifies as a piece of armour.", \
    "This piece of armour offers minimal protection.", \
    "This piece of armour just might ward off the odd blow.", \
    "This will do as a piece of armour.", \
    "This is a decent piece of armour.", \
    "This is a fine piece of armour.", \
    "This piece of armour would protect you very well.", \
    "This piece of armour offers full protection.", \
    "This piece of armour is a stronghold in itself.", \
    "This piece of armour renders your virtually invulnerable.", \
    })

public void
config_spell()
{
    ::config_spell();

    set_spell_name("delve");
    set_spell_desc("Identify magical properties.");
    set_spell_target(spell_target_one_present_non_living);

    set_spell_time(10);
    set_spell_mana(32);
    set_spell_task(TASK_ROUTINE);
    set_spell_element(SS_ELEMENT_AIR, 40);
    set_spell_form(SS_FORM_DIVINATION, 40);

    set_blood_cost(10);

    set_min_guild_stat(100);
    
    set_spell_resist(spell_resist_identify);
    set_ability_target_verify(spell_verify_present);
    set_spell_peaceful(1);
    set_spell_stationary(1);
    set_spell_vocal(1);
}

/*
 * Function name: cut_sig_fig
 * Description:   Will reduce the number given to a new number with two
 *                significant numbers.
 * Arguments:     fig - the number to correct.
 * Returns:       the number with two significant numbers
 */
public int
cut_sig_fig(int fig)
{
    int fac;
    fac = 1;

    while(fig > 100)
    {
        fac = fac * 10;
        fig = fig / 10;
    }
    return fig * fac;
}


public void appraise_property(int val,string * names,int skill)
{

    skill = 1000 / (skill + 1);
    skill = random(skill);
    val = cut_sig_fig(val+ (skill % 2 ? -skill % 70 : skill) *
        val / 100);
    write(GET_NUM_DESC(val,60,names)+"\n");

}


/*
 * Function name: get_id_info
 * Description:   Return a string describing the magical properties
 *                of an item
 * Arguments:     object target - the item to identify
 *                int max_level - the level of info you want 
 *                (see MAGIC_AM_ID_INFO)
 * Returns:       the description
 */
public string
get_id_info(object target, int max_level)
{
    
    if (target->query_prop(MAGIC_AM_MAGIC) ||
        target->query_prop(OBJ_I_IS_MAGIC_ARMOUR) ||
        target->query_prop(OBJ_I_IS_MAGIC_WEAPON))
    {
        return "This artifact is imbued with magical properties.\n";
    }
    return "";    
    
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
    caster->catch_tell("You bite your finger and spread some blood " + 
    "over "+ FO_COMPOSITE_ALL_DEAD(targets, caster) + 
    ", your senses delving its inner secrets.\n");

    object *
    who = FILTER_CAN_SEE_IN_ROOM(FILTER_IS_SEEN(caster,
            all_inventory(environment(caster)) - ({ caster })));

    who->catch_msg(QCTNAME(caster) + " bites "+POSS(caster)+  " finger " +
    "and spreads a bit of blood along " + 
       FO_COMPOSITE_ALL_DEAD(targets, caster) + ".\n");

    string msg;
    object target = targets[0];

    result = result * (100 - resist[0]) / 100;

    msg = get_id_info(target, result);

    if (strlen(msg))
    {
        caster->catch_tell(msg);
    }
    else
    {
        caster->catch_tell("You fail to divine any magical properties.\n");
    }
    
    int skill=caster->query_skill(SS_APPR_OBJ)+result;

    target->appraise_object(skill);
    
    if (target->check_weapon())
    {
        appraise_property(target->query_hit(),HIT_DESC,skill);
        appraise_property(target->query_pen(),PEN_DESC,skill);
    }
    if (target->check_armour())
    {
        appraise_property(target->query_ac(),ARM_DESC,skill);
    }

}


/*
 * Function name: check_valid_action
 * Description:   Perform ability-specific checks
 * Arguments:     1. (object) The actor
 *                2. (mixed *) The targets
 *                3. (string) Arguments passed to the command
 *                4. (int) Actual spell execution
 * Returns:       (int) 1 if we can continue, 0 if failure
 */
static int check_valid_action(object actor,mixed * targets,string arg,int 
                                execute = 0)
{
    if (actor->query_bloodguard() && !actor->query_master())
    {
        actor->catch_tell("Without a master, your connection to the "+
        "gift is too weak to perform this.\n");
        return 0;
    }
    return ::check_valid_action(actor,targets,arg,execute);
}

