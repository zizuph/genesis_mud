/*
 * Detonate spell for School of High Magic - Arman 2016
 */

#pragma strict_types

#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>
#include <composite.h>
#include <tasks.h>
#include "defs.h"
#include "/d/Krynn/common/defs.h"
#include CLOCKH

inherit "/d/Genesis/specials/std/spells/harm";

#include  "/d/Krynn/guilds/wohs/wohs_moon_benefit.h";

/*
 * Function:    config_harm_spell
 * Description: Config function for harm spells. Redefine this in your
 *              own harm spells to override the defaults.
 * Arguments:   Same as config_spell
 * Returns:     Same as config spell
 */
public void
config_harm_spell()
{
    set_ability_group(GUILD_NAME);
    set_spell_name("virednith");
    set_spell_desc("Detonate - a targeted explosion of fire");

    set_spell_vocal(1);
    set_spell_visual(1);
    set_spell_stationary(0);
    set_spell_peaceful(0);
    set_spell_offensive(1);

    // 'normal' combat aid for this spell is 140.0
    // Night of the Eye maximum is 196 caid, modified
    // through query_spell_combat_aid_modifier() below
    // set_spell_combat_aid(140.0);

    set_spell_combat_aid(196.0);
    set_spell_task(TASK_HARD);

    // 3 times the standard cast time for a harm spell 
    set_spell_time_factor(3.0);     

    set_spell_element(SS_ELEMENT_FIRE, 50);
    set_spell_form(SS_FORM_CONJURATION, 60);
}

/*
 * Function:    query_harm_ingredients
 * Description: This function defines what components are required for
 *              this harm spell.
 */
public string *
query_harm_ingredients(object caster)
{
    // One potion charge, any gem shard and the  
    // requirement to be wielding a staff or holding a wand. 
    return ({ "shard", "_ixenner_charge" });
}

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
    
    setuid();
    seteuid(getuid());
    return SOHM_MANAGER->query_memorised_spell(player,"virednith_memorised");
}

/*
 * Function:    query_spell_combat_aid_modifier
 * Description: Value between 1.0 and 100.0 that will modify
 *              the maximum combat aid granted by this spell.
 */
public float
query_spell_combat_aid_modifier()
{

/*  Moon phase bonuses:
 *  Night of the Eye (all three moons full): 40% bonus (196 caid)
 *  
 *  Maximum benefit (25%): full (175 caid)
 *  partial benefit (10%): waxing/waning gibbous (154 caid)
 *  no benefit: waxing/waning half (140.0 caid)
 *  partial penalty (-10%): waning/waxing crescent (126 caid)
 *  Full penalty (-25%): new (105 caid)
 *  
 *  See ~guilds/wohs/doc/WoHS.txt for specifics. 
 */

    // Modify combat aid depending on phase of the magic moons
    string moon_bonus = SOHM_MANAGER->query_wohs_moon_phase_aid(TP);
    float caid_mod, moon_mod;

    if(!moon_bonus)
       moon_bonus = "none";
    if(TP->query_wohs_alignment_penalty())
       moon_bonus = "penalty";

    switch(moon_bonus)
    {
        case "night of the eye":
          moon_mod = 1.0;
          break;
        case "maximum":
          moon_mod = 0.893;
          break;
        case "partial":
          moon_mod = 0.786;
          break;
        case "none":
          moon_mod = 0.715;
          break;
        case "partial_penalty":
          moon_mod = 0.643;
          break;
        case "penalty":
          moon_mod = 0.536;
          break;
     }

     // If a team member has the Stellar Alignment spell being 
     // maintained, the moon penalty is nullified.
     if(check_stellar_alignment_benefit(TP) && (moon_mod < 0.715))
     {
          DEBUG("Stellar check called for detonate.");
          moon_mod = 0.715;  
     } 

     caid_mod = 100.0 * moon_mod;
     // DEBUG("Caid_mod: " +ftoi(caid_mod)+ ", moon bonus: "+moon_bonus+ ".");

     return caid_mod;
}


int
filter_tool(object obj)
{
      if (obj->id("wand"))
        return 1;
      else if (obj->id("staff"))
        return 1;
      else 
        return 0;
}

public int 
check_valid_action(object caster, mixed * targets, string arg, int execute = 0)
{
    if (!::check_valid_action(caster, targets, arg, execute))
    {
        return 0;
    }

    if(SOHM_MANAGER->too_many_spells_memorised(caster))
    {
        caster->catch_tell("You have more spells memorised than you are capable of " +
            "mentally handling. You need to balance your memorised spell list before " +
            "you can cast spells again.\n");
        return 0;
    }

    if (!caster->query_weapon(-1) && !caster->query_tool(-1))
    {
        caster->catch_tell("You need to be wielding a staff or holding a wand " +
              "to cast detonate.\n");
        return 0;
    }

    object *weapon;


    /* Filter out non-staffs */
    if(caster->query_tool(-1))
      weapon = filter(caster->query_tool(-1), filter_tool);  

    if(!sizeof(weapon))
    {
        caster->catch_tell("You aren't wielding a staff or holding a wand " +
              "to cast detonate.\n");
	return 0;
    }

    /*  Can't cast spell if using defensive spells   */

    if(caster->query_prop("_sohm_stoneskin_effect"))
    {
        caster->catch_tell("Your stoneskin spell interferes with your ability " +
              "to cast detonate.\n");
	return 0; 
    }

    if(caster->query_prop("_sohm_magic_shield_effect"))
    {
        caster->catch_tell("Your magic shield spell interferes with your ability " +
              "to cast detonate.\n");
	return 0; 
    }

    if(caster->query_prop("_sohm_blur_effect"))
    {
        caster->catch_tell("Your blur spell interferes with your ability " +
              "to cast detonate.\n");
	return 0; 
    }

    if(caster->query_prop("_wohs_advanced_magic_shield_effect"))
    {
        caster->catch_tell("Your greater magic shield spell interferes with your ability " +
              "to cast the detonate spell.\n");
	return 0; 
    }

    if(caster->query_prop("_sohm_portents_and_omens_effect"))
    {
        caster->catch_tell("Your portents and omens spell interferes with your ability " +
              "to cast the detonate spell.\n");
	return 0; 
    }

    object * effects = caster->query_prop("_live_o_maintained_effects");
    string caster_name = caster->query_real_name();

    foreach (object effect : effects)
    {
        if (objectp(effect))
        {
           if (environment(effect)->query_prop("_sohm_retributive_ward_effect") == caster_name)
           {
                caster->catch_tell("The retributive ward you are maintaining interferes " +
                                   "with your ability to cast the detonate spell.\n");
                return 0;
           }
        }
    }
    
    return 1;
}

// HOOKS TO BE DEFINED

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
    object *wep;
    /* Filter out non-staffs and wands */
    wep = filter(caster->query_tool(-1), filter_tool);

        caster_message = "You raise your " +wep[0]->short()+ " menacingly and begin " +
            "chanting powerful words of conjuration.\n";
        watcher_message = QCTNAME(caster) +" raises " +caster->query_possessive()+ " " 
            +wep[0]->short()+ " menacingly and begins chanting powerful words of magic.\n";
        
    caster->catch_tell(caster_message);
    tell_room(environment(caster), watcher_message, ({ caster }), caster);
    
    setuid();
    seteuid(getuid());
}

/*
 * Function name: desc_harm_damage
 * Description:   Write out some text describing the damage done.  This can
 *                be redefined for custom messages.
 * Arguments:     object caster - the caster
 *                object target - the target
 *                mixed *result - return value from harm's hit_me.
 */
public void
desc_harm_damage(object caster, object target, mixed *result)
{
    string caster_message, target_message, watcher_message;
    int phurt = result[0];
    string hitloc_desc = result[1];
    string air_desc;

    if(environment(target)->query_prop(ROOM_UNDER_WATER))
      air_desc = "water";
    else if(environment(target)->query_prop(ROOM_I_TYPE) == ROOM_UNDER_WATER)
      air_desc = "water";
    else
      air_desc = "air";

    // result is in array of:
    //  ({ proc_hurt, hitloc desc, phit, dam, hitloc id })
    if (phurt < 0)
    {
        // Missed! give the miss messages.
        target_message = "The " +air_desc+ " detonates harmlessly around you.\n";
        watcher_message = "The " +air_desc+ " detonates harmlessly around " + QTNAME(target) + ".\n";
    }
    else
    {        
        switch (phurt) // percentage hurt
        {
        case 0:
            target_message = "The " +air_desc+ " surrounding you suddenly detonates, " +
            "warming your " +hitloc_desc+ " and doing no damage.\n";
            watcher_message = "The " +air_desc+ " surrounding " + QTNAME(target)
                + " suddenly detonates, warming " +HIS(target)+ " " + hitloc_desc + 
                ", doing no damage.\n"; 
            break;
            
        case 1..5:
            target_message = "The " +air_desc+ " surrounding you suddenly detonates, " +
                "singeing your " +hitloc_desc+ " slightly.\n";
            watcher_message = "The " +air_desc+ " surrounding " + QTNAME(target)
                + " suddenly detonates, singeing " +HIS(target)+ " " + hitloc_desc + 
                " slightly.\n"; 
            break;
            
        case 6..10:
            target_message = "The " +air_desc+ " surrounding you suddenly detonates, " +
                "mildly scorching your " +hitloc_desc+ ".\n";
            watcher_message = "The " +air_desc+ " surrounding " + QTNAME(target)
                + " suddenly detonates, mildly scorching " +HIS(target)+ " " + hitloc_desc + 
                ".\n";
            break;
            
        case 11..25:
            target_message = "The " +air_desc+ " surrounding you suddenly detonates, " +
                "causing burning wounds to your " +hitloc_desc+ ".\n";
            watcher_message = "The " +air_desc+ " surrounding " + QTNAME(target)
                + " suddenly detonates, causing burning wounds to " +HIS(target)+ " "+ 
                hitloc_desc + ".\n";
            break;
            
        case 26..35:
            target_message = "The " +air_desc+ " surrounding you detonates violently, " +
                "seriously burning your " +hitloc_desc+ ".\n";
            watcher_message = "The " +air_desc+ " surrounding " + QTNAME(target)
                + " detonates violently, seriously burning " +HIS(target)+ " " + 
                hitloc_desc + ".\n";
            break;
            
        case 36..45:
            target_message = "The " +air_desc+ " surrounding you detonates violently into " +
                "flame, broiling your " +hitloc_desc+ " painfully.\n";
            watcher_message = "The " +air_desc+ " surrounding " + QTNAME(target)
                + " detonates violently into flame, broiling " +HIS(target)+ " " + 
                hitloc_desc + " painfully.\n";
            break;
            
        case 46..55:
            target_message = "The " +air_desc+ " detonates violently, engulfing you in " +
                "a raging fire and causing severe damage to your " +hitloc_desc+ ".\n";
            watcher_message = "The " +air_desc+ " surrounding " + QTNAME(target)
                + " detonates violently, engulfing " +HIM(target)+ " in a raging fire and " +
                "causing " +HIS(target)+ " " +hitloc_desc + " severe damage.\n";
            break;
                    
        case 56..85:
            target_message = "The " +air_desc+ " detonates violently, engulfing you in " +
                "a raging fire and melting your " +hitloc_desc+ ", causing grievous " +
                "injuries.\n";
            watcher_message = "The " +air_desc+ " surrounding " + QTNAME(target)
                + " detonates violently, engulfing " +HIM(target)+ " in a raging fire and " +
                "melting " +HIS(target)+ " " +hitloc_desc + ", causing grievous injuries.\n";
            break;
            
        default:
            target_message = "The " +air_desc+ " detonates violently, engulfing you in " +
                "a deadly hellfire! Your " +hitloc_desc+ " explodes in flame, causing multiple " +
                "fatal injuries!\n";
            watcher_message = "The " +air_desc+ " surrounding " + QTNAME(target)
                + " detonates violently, engulfing " +HIM(target)+ " in a deadly hellfire! " +
                capitalize(HIS(target))+ " " +hitloc_desc + " explodes in flame, causing multiple " +
                "fatal injuries!\n";
            break;
        }
    }
        
    caster->catch_msg(watcher_message);
    target->catch_msg(target_message);
    target->tell_watcher(watcher_message, target, ({ caster, target }));

    int c_aid = ftoi(query_spell_combat_aid());
    // DEBUG("Detonate combat aid: " + c_aid + ", phurt: " +phurt);

}

/*
 * Function name: desc_harm_cast
 * Description:   Describe casting of the spell, not including damage messages.
 *                This can be redefined for custom messages.
 * Arguments:     object caster - the caster
 *                object target - the target
 */
public void
desc_harm_cast(object caster, object * targets)
{
    string caster_message, target_message, watcher_message;
    object target;
   
    target = targets[0];
    object *wep;
    /* Filter out non-staffs and wands */
    wep = filter(caster->query_tool(-1), filter_tool);

        caster_message = "You point your " +wep[0]->short()+ " at " + QTNAME(target) + 
            " and call out 'virednith!' ";
        target_message = QCTNAME(caster)+ " points " + caster->query_possessive() + " " +
            wep[0]->short()+ " at you and calls out a word of power. ";

        watcher_message = QCTNAME(caster)+ " points " + caster->query_possessive() + " " +
            wep[0]->short()+ " at " + QTNAME(target) + " and calls out a word of power. ";
    
    caster->catch_msg(caster_message);
    target->catch_msg(target_message);
    caster->tell_watcher(watcher_message, targets, ({ caster }) + targets);    
}

/*
 * Function:    resolve_harm_spell
 * Description: Called at the beginning of resolve_spell in order to perform
 *              spell specific actions.
 * Arguments:   Same as resolve_spell
 */
public void
resolve_harm_spell(object caster, object *targets, int *resist, int result)
{
}

/*
 * Function name: hook_no_ingredients_fail
 * Description:   Return the message that should be printed when the caster
 *                doesn't have the right ingredients
 * Returns:       The message to print.
 */
public void
hook_no_ingredients_fail(mixed * ingredients_needed)
{
   write("You need a gem shard and to have quaffed an ixenner potion to be " +
           "able to cast detonate.\n");
}
