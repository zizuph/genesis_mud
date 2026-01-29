/*
 * Chain lightning AoE harm spell for WoHS - Arman 2016
 */

#pragma strict_types

#include <ss_types.h>
#include <macros.h>
#include <composite.h>
#include <tasks.h>
#include "/d/Krynn/guilds/wohs/defs.h"
#include "/d/Krynn/common/defs.h"
#include CLOCKH

#include "/d/Genesis/specials/local.h"
inherit SPELL_DIR + "massharm";

#include  "/d/Krynn/guilds/wohs/wohs_moon_benefit.h";

/*
 * Function:    config_massharm_spell
 * Description: Config function for harm spells. Redefine this in your
 *              own harm spells to override the defaults.
 * Arguments:   Same as config_spell
 * Returns:     Same as config spell
 */
public void
config_massharm_spell()
{
    set_spell_name("ganimshochraos");
    set_spell_desc("chain lightning - a lightning bolt that arcs between enemies");

    // 'normal' combat aid for this spell is 130.0
    // Night of the Eye maximum is 182 caid, modified
    // through query_spell_combat_aid_modifier() below
    // set_spell_combat_aid(130.0);

    set_spell_combat_aid(182.0);

    set_ability_stats(STAT_WEIGHTING);

    // Low component requirement with potion charges
    set_spell_component_factor(COMPONENT_AID_LOW);

    set_spell_class(SPELL_CLASS_4);
    set_spell_task(TASK_EXACTING);

    // For testing checking the impact of a 3x time factor
    set_spell_time_factor(3.0);

    /* Limit spell targets */
    set_spell_target_limit(3);
  
    set_spell_element(SS_ELEMENT_AIR, 50);
    set_spell_form(SS_FORM_CONJURATION, 60);

    set_spell_resist(spell_resist_electricity);
}

/*
 * Function:    query_harm_ingredients
 * Description: This function defines what components are required for
 *              this harm spell.
 */
public string *
query_massharm_ingredients(object caster)
{ 
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
    return WOHS_MANAGER->query_memorised_spell(player,"ganimshochraos_memorised");
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
 *  Night of the Eye (all three moons full): 40% bonus (182 caid)
 *  
 *  Maximum benefit (25%): full (162.5 caid)
 *  partial benefit (10%): waxing/waning gibbous (143 caid)
 *  no benefit: waxing/waning half (130.0 caid)
 *  partial penalty (-10%): waning/waxing crescent (117 caid)
 *  Full penalty (-25%): new (97.5 caid)
 *  
 *  See ~guilds/wohs/doc/WoHS.txt for specifics. 
 */

    // Modify combat aid depending on phase of the magic moons
    string moon_bonus = WOHS_MANAGER->query_wohs_moon_phase_aid(TP);
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

    if(WOHS_MANAGER->too_many_spells_memorised(caster))
    {
        caster->catch_tell("You have more spells memorised than you are capable of " +
            "mentally handling. You need to balance your memorised spell list before " +
            "you can cast spells again.\n");
        return 0;
    }

    if (!caster->query_weapon(-1) && !caster->query_tool(-1))
    {
        caster->catch_tell("You need to be wielding a staff or holding a wand " +
              "to cast chain lightning.\n");
        return 0;
    }

    object *weapon;

    /* Filter out non-staffs */
    if(caster->query_tool(-1))
      weapon = filter(caster->query_tool(-1), filter_tool);  

    if(!sizeof(weapon))
    {
        caster->catch_tell("You aren't wielding a staff or holding a wand " +
              "to cast chain lightning.\n");
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

        caster_message = "You raise your hand and begin tracing powerful runes of magic " +
            "in the air, charging it with electrical energy.\n";
        watcher_message = QCTNAME(caster) +" raises "+ caster->query_objective()+
             " hand and begins tracing powerful runes of magic in the air, charging " +
             "it with electrical energy.\n";
        
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

    // result is in array of:
    //  ({ proc_hurt, hitloc desc, phit, dam, hitloc id })
    if (phurt < 0)
    {
        // Missed! give the miss messages.
        target_message = "The lightning bolt arcs harmlessly past you.\n";
        watcher_message = "The lightning bolt arcs harmlessly past " +
        QTNAME(target) + ".\n";
    }
    else
    {        
        switch (phurt) // percentage hurt
        {
        case 0:
            target_message = "The bolt of lightning tickles your "
                + hitloc_desc + ", doing no damage.\n";
            watcher_message = QCTNAME(target) + " is tickled on the "
                +hitloc_desc+ " by the bolt of lightning, doing no damage.\n"; 
            break;
            
        case 1..5:
            target_message = "The lightning bolt strikes your " + hitloc_desc
                + ", shocking you slightly.\n";
            watcher_message = QCTNAME(target)+ " is slightly shocked on the " +
                hitloc_desc + ".\n";
            break;
            
        case 6..10:
            target_message = "The lightning bolt strikes your " + hitloc_desc + 
                " causing mild electrical burns.\n";
            watcher_message = QCTNAME(target) + " is struck with mild electrical " +
                "burns to the " + hitloc_desc + ".\n";
            break;
            
        case 11..15:
            target_message = "The lightning bolt strikes your " + hitloc_desc + 
                " causing burning wounds.\n";
            watcher_message = QCTNAME(target) + " is struck by the lightning bolt " +
                "on the " + hitloc_desc + ", causing burning wounds.\n";
            break;
            
        case 16..25:
            target_message = "The lightning bolt strikes your " + hitloc_desc + 
                ", seriously burning you.\n";
            watcher_message = QCTNAME(target) + " is seriously burnt on the " +
                hitloc_desc + " by the lightning bolt.\n";
            break;
            
        case 26..35:
            target_message = "Your " + hitloc_desc + " is blasted by the lightning bolt "
                + ", electrocuting you painfully.\n";
            watcher_message = QCTNAME(target) + " is blasted by the lightning bolt, " +
                "electrocuting " +target->query_possessive()+ " " +hitloc_desc+ " painfully.\n";
            break;
            
        case 36..50:
            target_message = "Your " + hitloc_desc + " is blasted by the lightning bolt, "
                + "causing severe damage.\n";
            watcher_message = QCTNAME(target) + " is blasted by the powerful lightning bolt, " +
                "causing severe damage to " +target->query_possessive()+ " " +hitloc_desc+ ".\n";
            break;
                    
        case 51..70:
            target_message = "The powerful lightning bolt explodes into you, ripping through " +
                "your " +hitloc_desc + " and causing you grievous injuries.\n";
            watcher_message = "The powerful lightning bolt arcs into "
                + QTPNAME(target) + " " + hitloc_desc + ", causing " +
                target->query_objective()+ " grievous injuries.\n";
            break;
            
        default:
            target_message = "The mighty bolt of lightning roars violently into you " +
                "with deadly force, exploding apart your " +hitloc_desc + 
                 " and causing multiple fatal injuries.\n";
            watcher_message = "The mighty bolt of lightning arcs violently into "
                + QTNAME(target) + " with deadly force, exploding apart " + target->query_possessive()
                + " " + hitloc_desc + " and causing multiple fatal injuries.\n";
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

    string go_plural;

    if(sizeof(targets) > 1)
      go_plural = "them";
    else
      go_plural = HIM(targets[0]);

        caster_message = "As restrained energy crackles around you ominously, you point "+
            "your hand with fingers splayed in the direction of " + COMPOSITE_LIVE(targets) + 
            ". Calling out 'ganim shochraos!', you release an arcing bolt of lightning " +
            "into "+go_plural+"!\n";
        target_message = QCTNAME(caster)+ " chants words of power and points " 
            + caster->query_possessive() + " hand with fingers splayed in your " +
            "direction. A bolt of lightning arcs from " +HIS(caster)+ " hand " +
            "towards you!\n";

        watcher_message = QCTNAME(caster)+ " chants words of power and points " + 
            caster->query_possessive() + " hand with fingers splayed towards " + 
            COMPOSITE_LIVE(targets) + ", releasing a bolt of lightning into "+go_plural+"!\n";
    
    caster->catch_msg(caster_message);
    targets->catch_msg(target_message);
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
           "able to cast chain lightning. " +missing+ ".\n");
}

public void
hook_no_present_targets(object actor, string str)
{
    actor->catch_msg("You must first be in combat before you can call on "
    + "this spell!\n");   
}

/* Had to mask the below function from spell_targetting.c 

public object *
spell_target_present_enemies(object actor, string str)
{
    object *enemies = (object *)actor->query_enemy(-1) &
        all_inventory(environment(actor));

    if (!sizeof(enemies))
    {
        actor->catch_msg("You must first be in combat before you can call on " +
           "this spell!\n");
        return ({});
    }

    return enemies;
}
*/
