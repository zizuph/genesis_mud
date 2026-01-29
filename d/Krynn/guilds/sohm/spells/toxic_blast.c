/*
 * Toxic Blast spell for WoHS - Arman 2020
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

#include "/d/Genesis/specials/local.h"
inherit SPELL_DIR + "harm";

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
    set_spell_name("hexlithdrevab");
    set_spell_desc("Doom Blast - a toxic blast of virulent gases");

    // 'normal' combat aid for this spell is 170.0
    // Night of the Eye maximum is 238 caid, modified
    // through query_spell_combat_aid_modifier() below
    // set_spell_combat_aid(170.0);

    set_spell_combat_aid(238.0);

    set_ability_stats(STAT_WEIGHTING);

    // Low component requirement with potion charges
    set_spell_component_factor(COMPONENT_AID_LOW);

    set_spell_class(SPELL_CLASS_4);
    set_spell_task(TASK_DIFFICULT);

    // 3 times the standard cast time for a harm spell 
    set_spell_time_factor(3.0);     

    set_spell_element(SS_ELEMENT_WATER, 50);
    set_spell_form(SS_FORM_CONJURATION, 60);

    set_spell_resist(spell_resist_poison);
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
    return ({ "shard", "_hexlith_charge" });
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
    return SOHM_MANAGER->query_memorised_spell(player,"hexlithdrevab_memorised");
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
 *  Night of the Eye (all three moons full): 40% bonus (238 caid)
 *  
 *  Maximum benefit (25%): full (212 caid)
 *  partial benefit (10%): waxing/waning gibbous (187 caid)
 *  no benefit: waxing/waning half (170.0 caid)
 *  partial penalty (-10%): waning/waxing crescent (153 caid)
 *  Full penalty (-25%): new (127 caid)
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
          moon_mod = 0.715;  
 
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
      else if (obj->query_magic_spellpower())
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
              "to cast eruption.\n");
        return 0;
    }

    object *weapon;

    /* Filter out non-staffs */
    if(caster->query_tool(-1))
      weapon = filter(caster->query_tool(-1), filter_tool);  

    if(!sizeof(weapon))
    {
        caster->catch_tell("You aren't wielding a staff or holding a wand " +
              "to cast eruption.\n");
	return 0;
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

        caster_message = "You raise your " +wep[0]->short()+ " and begin " +
            "chanting powerful words of conjuration that will tear a rift in " +
            "the fabric of space to the Lords of Doom.\n";
        watcher_message = QCTNAME(caster) +" raises " +caster->query_possessive()+ " " 
            +wep[0]->short()+ " and begins chanting powerful words of magic.\n";
        
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
    string ground_desc;

    if(environment(target)->query_prop(ROOM_I_INSIDE))
      ground_desc = "floor";
    else if(environment(target)->query_prop(ROOM_IN_WATER))
      ground_desc = "water";
    else if(environment(target)->query_prop(ROOM_I_TYPE) == ROOM_IN_WATER)
      ground_desc = "water";
    else if(environment(target)->query_prop(ROOM_UNDER_WATER))
      ground_desc = "watery depths";
    else if(environment(target)->query_prop(ROOM_I_TYPE) == ROOM_UNDER_WATER)
      ground_desc = "watery depths";
    else if(environment(target)->query_prop(ROOM_BEACH))
      ground_desc = "beach";
    else if(environment(target)->query_prop(ROOM_I_TYPE) == ROOM_BEACH)
      ground_desc = "beach";
    else if(environment(target)->query_prop(ROOM_IN_AIR))
      ground_desc = "air";
    else if(environment(target)->query_prop(ROOM_I_TYPE) == ROOM_IN_AIR)
      ground_desc = "air";
    else
      ground_desc = "ground";

    // result is in array of:
    //  ({ proc_hurt, hitloc desc, phit, dam, hitloc id })
    if (phurt < 0)
    {
        // Missed! give the miss messages.
        target_message = "A maisma of toxic fumes harmlessly surround you.\n";
        watcher_message = "A maisma of toxic fumes harmlessly surround " + 
            QTNAME(target) + ".\n";
    }
    else
    {        
        switch (phurt) // percentage hurt
        {
        case 0:
            target_message = "A maisma of toxic gases strikes your " +hitloc_desc+ 
                ", doing no damage.\n";
            watcher_message = "A maisma of toxic gases strikes " + QTNAME(target)
                + " on the " + hitloc_desc + ", doing no damage.\n"; 
            break;
            
        case 1..5:
            target_message = "A maisma of toxic gases strikes your " + hitloc_desc
                + ", stinging you slightly.\n";
            watcher_message = "A maisma of toxic gases strikes " + QTNAME(target)
                + " in the " + hitloc_desc + ", stinging " + target->query_objective()
                + " slightly.\n";
            break;
            
        case 6..10:
            target_message = "A maisma of toxic gases strikes your " + hitloc_desc + 
                " mildly blighting you.\n";
            watcher_message = "A maisma of toxic gases strikes " +QTNAME(target) + 
                " in the " + hitloc_desc + ", mildly blighting " 
                +target->query_objective()+ ".\n";
            break;
            
        case 11..25:
            target_message = "A violent blast of dark toxic gases strikes your " + 
                hitloc_desc + " scourging you harshly.\n";
            watcher_message = "A violent blast of dark toxic gases strikes " +
                QTNAME(target) + " in the " + hitloc_desc + ", scourging " +
                target->query_objective()+ " harshly.\n";
            break;
            
        case 26..35:
            target_message = "A writhing column of poisonous gases blasts into " +
                "your " + hitloc_desc + ", harming you painfully.\n";
            watcher_message = "A writhing column of poisonous gases blasts into " +
                QTPNAME(target) + " " + hitloc_desc + ", harming " +
                target->query_objective()+ " painfully.\n";
            break;
            
        case 36..45:
            target_message = "A virulent column of poisonous gases blasts into " +
                "your " + hitloc_desc + ", shriveling it horribly.\n";                
            watcher_message = "A virulent column of poisonous gases blasts into " +
                QTPNAME(target) + " " + hitloc_desc + ", shriveling it horribly.\n";
            break;
            
        case 46..55:
            target_message = "Your " + hitloc_desc + " is engulfed by a mighty eruption of "
                + "black poisonous gases that explodes out of the " +ground_desc+ 
                ", causing severe damage.\n";
            watcher_message = QCTNAME(target) + " is engulfed by a mighty eruption of black " +
                "poisonous gases that explodes out of the " +ground_desc+ ", causing severe " +
                "damage to " + target->query_possessive() + " " +hitloc_desc+ ".\n";
            break;
                    
        case 56..85:
            target_message = "A mighty column of roiling poisonous gases erupts into you " +
                "from out of the " +ground_desc+ ", withering your " +hitloc_desc+ 
                " and causing you grievous injuries.\n";
            watcher_message = "A mighty column of roiling poisonous gases erupts into " + 
                QTNAME(target) + " from out of the "+ground_desc+ ", withering " + 
                target->query_possessive() + " " + hitloc_desc + " and causing " +
                target->query_objective()+ " grievous injuries.\n";
            break;
            
        default:
            target_message = "A raging explosion of noxious gases erupts from out of the "
                +ground_desc+ " and fatally engulfs you!\n";
            watcher_message = "A raging explosion of noxious gases erupts from out of the "+
                ground_desc+ " and fatally engulfs "+ QTNAME(target) + "!\n";
            break;
        }
    }
        
    caster->catch_msg(watcher_message);
    target->catch_msg(target_message);
    target->tell_watcher(watcher_message, target, ({ caster, target }));
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
            " and call out 'hexlith drevab!' ";
        target_message = QCTNAME(caster)+ " points " + caster->query_possessive() + " " +
            wep[0]->short()+ " at you and calls out words of power. ";

        watcher_message = QCTNAME(caster)+ " points " + caster->query_possessive() + " " +
            wep[0]->short()+ " at " + QTNAME(target) + " and calls out words of power. ";
    
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
{   string missing = "You are missing ";
   int n = 0;
   object ing;

   foreach(mixed ingredient : ingredients_needed)
   {
       if(stringp(ingredient))
       {
           if(n)
               missing += " and ";
           if(ingredient == "shard")
           {
               if (!objectp(ing = present("shard", this_player())))
               {
                   missing += "a shard component";
                   n++;
               }
           }
           if(ingredient == "_hexlith_charge")
           {
               if (!objectp(ing = present("_hexlith_charge", this_player())))
               {
                   missing += "hexlith charges";
                   n++;
               }
           }
       }
   }

    write("You need a gem shard and to have quaffed a hexlith potion " +
          "to be able to cast doom blast. " +missing+ ".\n");
}
