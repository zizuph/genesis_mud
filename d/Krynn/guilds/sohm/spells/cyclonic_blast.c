/*
 * Cyclonic blast spell for Wizards of High Sorcery - Arman 2020
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
    set_spell_name("suacodrevab");
    set_spell_desc("Cyclonic blast - a targeted torrent of wind");

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

    set_spell_element(SS_ELEMENT_AIR, 50);
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
    return ({ "shard", "_shochraos_charge" });
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
    return SOHM_MANAGER->query_memorised_spell(player,"suacodrevab_memorised");
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
              "to cast cyclonic blast.\n");
        return 0;
    }

    object *weapon;

    /* Filter out non-staffs */
    if(caster->query_tool(-1))
      weapon = filter(caster->query_tool(-1), filter_tool);  

    if(!sizeof(weapon))
    {
        caster->catch_tell("You aren't wielding a staff or holding a wand " +
              "to cast cyclonic blast.\n");
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

        caster_message = "You raise your " +wep[0]->short()+ " menacingly and begin " +
            "chanting powerful words of magic.\n";
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
        target_message = "It twists past your " +hitloc_desc+ " and " +
            "dissipates harmlessly.\n";
        watcher_message = "It twists past " + QTPNAME(target) + " " +
            hitloc_desc+ " and dissipates harmlessly.\n";
    }
    else
    {        
        switch (phurt) // percentage hurt
        {
        case 0:
            target_message = "It spins in to your " +hitloc_desc+ " before " +
                "dissipating and doing no real damage to you.\n";
            watcher_message = "It spins in to " + QTPNAME(target)
                + hitloc_desc + " before dissipating and doing no real damage.\n"; 
            break;
            
        case 1..5:
            target_message = "It spins in to your " +hitloc_desc+ ", " +
                "forcing you back slightly.\n";
            watcher_message = "It spins in to " + QTPNAME(target) + " " + hitloc_desc + 
                ", forcing " +HIM(target)+ " back slightly.\n"; 
            break;
            
        case 6..10:
            target_message = "It spins in to your " +hitloc_desc+ ", " +
                "bruising you.\n";
            watcher_message = "It spins in to " + QTPNAME(target) + " " + hitloc_desc + 
                ", bruising " +HIM(target)+ ".\n"; 
            break;
            
        case 11..25:
            target_message = "It coils through the " +air_desc+ " " +
                "and strikes your " +hitloc_desc+ " with force, battering you.\n";
            watcher_message = "It coils through the " +air_desc+ " and strikes " 
                + QTNAME(target) + " with force, battering " +HIS(target)+ " "+ 
                hitloc_desc + ".\n";
            break;
            
        case 26..35:
            target_message = "It coils through the " +air_desc+ " " +
                "and blasts your " +hitloc_desc+ " with great force, injuring you.\n";
            watcher_message = "It coils through the " +air_desc+ " and blasts " 
                + QTNAME(target) + " with great force, injuring " +HIS(target)+ " "+ 
                hitloc_desc + ".\n";
            break;
            
        case 36..45:
            target_message = "It coils around your " +
                hitloc_desc+ ", scouring you painfully.\n";
            watcher_message = "It coils around " + QTPNAME(target)+ " "
                + hitloc_desc + ", scouring " +HIM(target)+ " painfully.\n";
            break;
            
        case 46..55:
            target_message = "It coils around your " +
                hitloc_desc+ ", crushing you violently.\n";
            watcher_message = "It coils around " + QTPNAME(target)+ " "
                + hitloc_desc + ", crushing " +HIM(target)+ " violently.\n";
            break;
                    
        case 56..85:
            target_message = "It engulfs you completely and violently " +
                "flays you with extreme force, causing grievous injuries.\n";
            watcher_message = "It engulfs " + QTNAME(target)+ " completely and violently "
                + "flays " +HIM(target)+ " with extreme force, causing grievous "
                + "injuries.\n";
            break;
            
        default:
            target_message = "It engulfs you completely, warping your body " +
                "with supernatural force and causing fatal injuries.\n";
            watcher_message = "It engulfs " + QTNAME(target)+ " completely, warping "
                +HIS(target)+ " body with supernatural force and causing fatal "
                + "injuries.\n";
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
    string caster_message, target_message, watcher_message, air_desc;
    object target;
   
    target = targets[0];
    object *wep;
    /* Filter out non-staffs and wands */
    wep = filter(caster->query_tool(-1), filter_tool);

    if(environment(target)->query_prop(ROOM_UNDER_WATER))
      air_desc = "cuts through the water";
    else if(environment(target)->query_prop(ROOM_I_TYPE) == ROOM_UNDER_WATER)
      air_desc = "cuts through the water";
    else
      air_desc = "roars";

        caster_message = "You point your " +wep[0]->short()+ " at " + QTNAME(target) + 
            " while rapidly spinning it, conjuring a twisting torrent of wind that " +
            air_desc+ " towards " +HIM(target)+ ". ";
        target_message = QCTNAME(caster)+ " points " + caster->query_possessive() + " " +
            wep[0]->short()+ " at you while rapidly spinning it, conjuring a twisting " +
            "torrent of wind that " +air_desc+ " towards you! ";

        watcher_message = QCTNAME(caster)+ " points " + caster->query_possessive() + " " +
            wep[0]->short()+ " at " + QTNAME(target) + " while rapidly spinning it, " +
            "conjuring a twisting torrent of wind that " +air_desc+ " towards " +
            HIM(target)+ ". ";
    
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
   string missing = "You are missing ";
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
           if(ingredient == "_shochraos_charge")
           {
               if (!objectp(ing = present("_shochraos_charge", this_player())))
               {
                   missing += "shochraos charges";
                   n++;
               }
           }
       }
   }

   write("You need a gem shard and to have quaffed an shochraos potion to be " +
           "able to cast cyclonic blast. " +missing+ ".\n");
}
