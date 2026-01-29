/*
 * pHeal
 */

#pragma strict_types

inherit "/d/Genesis/specials/std/spells/heal";

#include "../defs.h"
#include <wa_types.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <files.h>
#include <composite.h>
#include "/d/Krynn/common/defs.h"

#include <macros.h>
#include <tasks.h>

#include "../oots_god_descs.h"

/*
 * Function:    config_heal_spell
 * Description: Config function for heal spells. Redefine this in your
 *              own heal spells to override the defaults.
 */
public void
config_heal_spell(void)
{
    set_ability_group(GUILD_NAME);
    set_spell_name("oheal");
    set_spell_desc("Healing hands - a prayer of healing");

    set_spell_element(SS_ELEMENT_LIFE, 20);
    set_spell_form(SS_FORM_TRANSMUTATION, 20);
    set_spell_fail("Your prayer of healing is unheard.\n");

    set_spell_task(TASK_ROUTINE);
    // 1.8 times the standard cast time for a heal spell 
    set_spell_time_factor(1.8);  

    set_spell_vocal(1);
    set_spell_visual(1);
    set_spell_stationary(1);
    set_spell_peaceful(0);
    set_spell_offensive(0);
    set_spell_combat_aid(50.0);
}

/*
 * Function:    query_spell_can_be_learned
 * Description: Place restrictions on whether this spell can be used
 *              by the guild member.
 */
public int
query_spell_can_be_learned(object player)
{
    if (!objectp(player))
    {
        return 0;
    }
    
    if (player->query_npc())
    {
        // npcs can always learn the spell.
        return 1;
    }

    // Level 2 (Convert) spell
    if(OOTS_LEVEL(player) < 2)
    {
        return 0;
    }

    return 1;
}

/*
 * Function:    query_heal_ingredients
 * Description: This function defines what components are required for
 *              this heal spell.
 */
public string *
query_heal_ingredients(object caster)
{
    return ({  });
}

/*
 * Function:    query_spell_ingredients_description
 * Description: Returns a string description of the ingredients. Can be used 
 *              in messages to casters about what is actually required
 *              for this spell.
 */
public string
query_spell_ingredients_description()
{
    return "no prayer components";
}

/*
 * Function:    query_spell_combat_aid_modifier
 * Description: Value between 1.0 and 100.0 that will modify
 *              the maximum combat aid granted by this spell.
 */
public float
query_spell_combat_aid_modifier()
{
    // If the player has defensive spells on, we reduce the
    // total combat aid provided by this spell.

    float caid_mod, align_mod;
    int caster_align = TP->query_alignment();

    if(caster_align < 1000)
    {
        align_mod = itof(caster_align) / 1000.0;
    }
    else
    {
        align_mod = 1.0;
    }

    // heal less effective if cleric is focusing on maintaining bless
    // or protect AND the unique god blessing
    if("/d/Krynn/guilds/OotS/spells/obless"->has_spell_object(TP) ||
       "/d/Krynn/guilds/OotS/spells/oprotect"->has_spell_object(TP))
    {
        if("/d/Krynn/guilds/OotS/spells/omend"->has_spell_object(TP) ||
           "/d/Krynn/guilds/OotS/spells/oheroism"->has_spell_object(TP))
        {
            caid_mod = 100.0 * (35.0 / 50.0) * align_mod;
        }   
        else
        {
            caid_mod = 100.0 * align_mod;    
        } 
    }
    else
    {
        caid_mod = 100.0 * align_mod;    
    }

// DEBUG("Caid_mod: " +ftoi(caid_mod)+ " align_mod: " +ftoi(align_mod * 10.0));
    
    return caid_mod;
}

public int 
check_valid_action(object caster, mixed * targets, string arg, int execute = 0)
{
    if (!::check_valid_action(caster, targets, arg, execute))
        return 0;

    if (caster->query_alignment() < 600)
    {
        caster->catch_tell("Your recent behaviours and actions do not " +
           "align with the teachings of " +oots_god_name(caster)+ 
           ". Your prayer goes unanswered.\n");
        return 0;
    }

    // harder to cast on evil aligned, except undead who get burnt
    if (targets[0]->query_prop(LIVE_I_UNDEAD))
	set_spell_task(TASK_ROUTINE);
    else if (targets[0]->query_alignment() < -100)
	set_spell_task(TASK_HARD);
    else
	set_spell_task(TASK_ROUTINE);

    int c_aid = ftoi(query_spell_combat_aid());     

    // DEBUG("Heal combat aid: " + c_aid);

    return 1;
}

/*
 * Function:    resolve_heal_spell
 * Description: Called at the beginning of resolve_spell in order to perform 
 *              spell specific actions.
 * Arguments:   Same as resolve_spell
 */
public void
resolve_heal_spell(object caster, object *targets, int *resist, int result)
{
    int c_aid = ftoi(query_spell_combat_aid());
    // DEBUG("Heal combat aid: " + c_aid);
}

/*
 * Function name: hook_describe_heal_cast
 * Description:   Describe casting of the spell. This takes place before the
 *                actual healing happens.
 *                This can be redefined for custom messages.
 * Arguments:     object caster   - the caster
 *                object * target - the target(s)
 */
public void
hook_describe_heal_cast(object caster, object *targets)
{
  // deliberately kept blank. Healing message covered under concentrate_msg
}

/*
 * Function name: concentrate_msg
 * Description:   Give messages indicating that spell concentration has begun
 * Arguments:     1. (object)   The caster
 *                2. (mixed *) The targets
 *                3. (string)   The arguments passed to the "cast" command
 */
public void
concentrate_msg(object caster, mixed * targets, string arg)
{
    string caster_message, watcher_message;
    object target = targets[0];

    if(target->query_prop(LIVE_I_UNDEAD))
    {
        caster_message = "You raise your medallion of faith and call upon " 
              + oots_god_name(caster) + " for righteous aid in smiting" 
              +" the unliving!\n";
        watcher_message = QCTNAME(caster) + " raises " +HIS(caster)+ 
              " medallion of faith and calls upon the " +
              oots_god_desc(caster)+ " " +oots_god_name(caster)+
              " to smite the unliving!\n";
    }
    else
    {
        caster_message = "You whisper a prayer, supplicating " +
              oots_god_name(caster)+ " for the blessing of divine healing.\n";
        watcher_message = QCTNAME(caster) + " whispers a prayer to the "
              +oots_god_desc(caster)+ " " +oots_god_name(caster)+".\n";
    }
        
    caster->catch_tell(caster_message);
    tell_room(environment(caster), watcher_message, ({ caster }), caster);

    setuid();
    seteuid(getuid());  
}


/*
 * Function name: hook_describe_heal_result
 * Description:   Describe the results of the spell upon its targets. This
 *                happens after the healing has happened.
 *                This can be redefined for custom messages.
 * Arguments:     object caster   - the caster
 *                object * target - the target(s)
 *                int * heal_amts - the amounts healed
 */
public void
hook_describe_heal_result(object caster, object *targets, int * heal_amounts)
{
    object tar = targets[0];
    int heal = heal_amounts[0];
    string heal_desc;

    switch(heal)
    {
       case 0..50:
         heal_desc = " slightly";
         break;
       case 51..150:
         heal_desc = " somewhat";
         break;
       case 151..250:
         heal_desc = "";
         break;
       case 251..450:
         heal_desc = " greatly";
         break;
       case 451..750:
         heal_desc = " miraculously";
         break;
       default:
         heal_desc = "";
         break;
    }

    // casting on evil aligned targets results in a standing adjustment.

    if (tar->query_alignment() < -100)
    {
	caster->catch_tell("You find it more difficult healing someone " +
	    "dark of heart.\n");
    }

    if (tar == caster)
    {
	caster->catch_tell("You feel the blessings of " +
            oots_god_name(caster)+ " wash over you and new health " +
            "infuse your body, your wounds" + heal_desc+ " healed.\n");
	tell_room(environment(caster), QCTNAME(caster) + " straightens " +
            "up, looking" +heal_desc+ " more hale.\n", targets);
    }
    else
    {
	caster->catch_tell("You place your hands on " +
	    tar->query_the_name(caster) + ", and " + HE(tar) +
	    " shivers as " + HIS(tar) + " wounds are" +heal_desc+ " healed.\n");
	tar->catch_tell(caster->query_The_name(tar) + " places " +
	    HIS(caster) + " hands on you, and you shiver as your " +
	    "wounds are" +heal_desc+ " healed.\n");
	tell_room(environment(caster), QCTNAME(caster) + " places " +
	    HIS(caster) + " hands on " + QTNAME(tar) + ", and " +
	    HE(tar) + " shivers as " + HIS(tar) + " wounds are" +heal_desc+ " healed.\n",
	    ({ caster, tar }), caster);
    }

    // experience for healing is 20% of heal value to a max of 300xp
    int heal_xp = min(300, (heal / 5));
    // int guild_xp = caster->query_skill(OOTS_GUILD_XP);
    // caster->set_skill(OOTS_GUILD_XP, guild_xp + heal_xp);
    OOTS_ADD_EXP(caster, heal_xp);

    // DEBUG("Heal amount: " +heal+ ", heal xp: " +heal_xp+ ".");
}


/*
 * Function name: hook_describe_harm_result
 * Description:   Describe the results of the spell upon its targets. This
 *                happens after the healing has happened.
 *                This can be redefined for custom messages.
 * Arguments:     object caster   - the caster
 *                object * target - the target(s)
 *                int * harm_amounts - the amounts healed
 */
public void
hook_describe_harm_result(object caster, object *targets, int * harm_amounts)
{
    object tar = targets[0];
    int harm = harm_amounts[0];
    string harm_desc;

    switch(harm)
    {
       case 0..50:
         harm_desc = " lightly";
         break;
       case 51..150:
         harm_desc = "";
         break;
       case 151..250:
         harm_desc = " painfully";
         break;
       case 251..450:
         harm_desc = " badly";
         break;
       case 451..750:
         harm_desc = " almost to ash";
         break;
       default:
         harm_desc = "";
         break;
    }

    if (tar == caster)
    {
	caster->catch_tell("You convulse in pain as divine energies shoot "+
	    "through your body.\n");
	tell_room(environment(caster), QCTNAME(caster) + " convulses as if "+
	    "in some kind of pain.\n", targets);
    }
    else
    {
	caster->catch_tell("Your medallion of faith blazes with purifying " +
            "azure light, burning " +tar->query_the_name(caster) 
            + harm_desc +".\n");
	tar->catch_tell(caster->query_The_possessive_name(tar) + " medallion " +
	    "of faith blazes with purifying azure light, burning you" +
	    harm_desc +".\n");
	tell_room(environment(caster), QCTPNAME(caster) + " medallion of " +
	    "faith blazes with purifying azure light, burning " + QTNAME(tar) 
            + harm_desc +".\n",
	    ({ caster, tar }), caster);
    }

    // experience for harming undead is 10% of heal value to a max of 300xp
    int harm_xp = min(300, (harm / 10));
    // int guild_xp = caster->query_skill(OOTS_GUILD_XP);
    // caster->set_skill(OOTS_GUILD_XP, guild_xp + harm_xp);
    OOTS_ADD_EXP(caster, harm_xp);

    // DEBUG("Harm amount: " +harm+ ", harm xp: " +harm_xp+ ".");
}

public int
is_valid_medallion(object caster, object obj)
{
    if (!objectp(obj) || !obj->id("oots_guild_object"))
    {
        return 0;
    }
    
    return 1;
}

/*
 * Function name: query_casting_success
 * Description:   Determine if a spell is successfully cast
 * Returns:       The result as an integer indicating success or
 *                failure (0 indicating failure, positive integer
 *                indicating % success)
 */
static int
query_casting_success(object caster)
{
    object * med = filter(all_inventory(TP), &is_valid_medallion(caster,));

    int ret = ::query_casting_success(caster);

    /* If we don't wear the medallion, there is only a 10% chance
     * the spell will actually go through
     */
    if(!med[0]->query_worn())
    {
        if (random(10))
            return 0;
    }
        
    return ret;
}