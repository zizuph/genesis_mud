/*
 * Earth harm spell for petrified wand.
 *
 * Arman - November 2020
 */

#pragma strict_types

#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>
#include <composite.h>
#include <tasks.h>
#include "/d/Krynn/common/defs.h"

inherit "/d/Genesis/specials/std/spells/harm";

#define PETRIFY_SPELL "/d/Krynn/throtyl/spells/wand_petrify_spell"
#define DEBUG(x)	find_player("arman")->catch_tell(x);

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
    set_spell_name("petrify");
    set_spell_desc("Stone blast - petrify your foe to stone!");

    // Must set this so guild spells cannot be stacked with
    // the wand ability.
    set_ability_exclusive(1);

    set_spell_vocal(1);
    set_spell_visual(1);
    set_spell_stationary(0);
    set_spell_peaceful(0);
    set_spell_offensive(1);

    // Default caid.
    // The caid of the spell is determined in check_valid_action 
    // and is based on the caster's SS_SPELLCRAFT and the
    // SS_ELEMENT_EARTH spell skills, maximum of 75 for max skill
    // in both.
    set_spell_combat_aid(50.0);
    set_spell_task(TASK_ROUTINE);

    // 2.5x the standard cast time for a harm spell 
    set_spell_time_factor(2.5);     

    set_spell_element(SS_ELEMENT_EARTH, 20);
    set_spell_form(SS_FORM_CONJURATION, 20);
}

/*
 * Function:    query_harm_ingredients
 * Description: This function defines what components are required for
 *              this harm spell.
 */
public string *
query_harm_ingredients(object caster)
{ 
    return ({  });
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

    return 1;
}

public int 
check_valid_action(object caster, mixed * targets, string arg, int execute = 0)
{
    mixed conc_prop;
    object conc_ob;

    if (!::check_valid_action(caster, targets, arg, execute))
    {
        return 0;
    }

    if(caster->query_prop(LIVE_I_CONCENTRATE) &&
       MASTER_OB(caster->query_prop(LIVE_I_CONCENTRATE)) != PETRIFY_SPELL)
    {
        // DEBUG("MASTER OB: " +MASTER_OB(caster->query_prop(LIVE_I_CONCENTRATE))+ ".\n");
        caster->catch_tell("You are currently concentrating on casting " +
            "another spell, and cannot activate the petrified stick.\n");
        return 0;
    }

    // To avoid spell stacking, need to check whether a spell has been cast
    // after the wand has been activated. If so, no longer a valid action.

    object * spell_list;
    spell_list = caster->query_spellobjs();

    if (sizeof(spell_list))
    {
        foreach(object preparing_spell: spell_list)
        {
            if(preparing_spell->query_ability_preparing(caster))
            {
                // DEBUG("Spell preparing: " +preparing_spell->query_spell_name()+ ".\n");
                caster->catch_tell("You are currently concentrating on casting " +
                    "another spell, " +preparing_spell->query_spell_name()+ 
                    ", disrupting your attempt to activate the petrified stick.\n");
               tell_room(environment(caster), QCTPNAME(caster)+ " attempt to " +
                    "activate the magic of the petrified stick fails.\n", 
                    ({ caster }), caster);
                return 0;
            }
        }
    }

    int spellcraft, earth_element_skill;
    float caid;

    // The caid of the spell is determined by the caster's SS_SPELLCRAFT
    // and SS_ELEMENT_EARTH spell skills, maximum of 75 for max skill
    // in both.

    spellcraft = caster->query_skill(SS_SPELLCRAFT);
    earth_element_skill = caster->query_skill(SS_ELEMENT_EARTH);

    caid = itof(((spellcraft + earth_element_skill) * 3) / 8);

    set_spell_combat_aid(caid);

    // caster->catch_tell("Caid: " +ftoi(caid)+ ".\n");
    
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

    caster_message = "You raise your petrified stick in preparation.\n";
    watcher_message = QCTNAME(caster) +" raises " +caster->query_possessive()+ 
        " petrified stick in preparation.\n";
        
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
    object corpse_sh;

    // result is in array of:
    //  ({ proc_hurt, hitloc desc, phit, dam, hitloc id })
    if (phurt < 0)
    {
        // Missed! give the miss messages.
        target_message = "A ray of earthly power misses you.\n";
        watcher_message = "A ray of earthly power misses " + 
            QTNAME(target) + ".\n";
    }
    else
    {        
        switch (phurt) // percentage hurt
        {
        case 0:
            target_message = "A ray of earthly power ineffectively strikes your " +
                hitloc_desc+ ", doing no damage.\n";
            watcher_message = "A ray of earthly power ineffectively strikes " + 
                QTNAME(target) + " on the " + hitloc_desc + ", doing no damage.\n"; 
            break;
            
        case 1..5:
            target_message = "A ray of earthly power strikes your " + hitloc_desc
                + ", stinging you slightly.\n";
            watcher_message = "A ray of earthly power strikes " + QTNAME(target)
                + " in the " + hitloc_desc + ", stinging " + target->query_objective()
                + " slightly.\n";
            break;
            
        case 6..10:
            target_message = "A ray of earthly power strikes your " + hitloc_desc + 
                ", causing it to harden slightly.\n";
            watcher_message = "A ray of earthly power strikes " +QTNAME(target) + 
                " in the " + hitloc_desc + ", causing it to harden slightly.\n";
            break;
            
        case 11..15:
            target_message = "A harsh tellurian ray strikes your " + 
                hitloc_desc + " abrading you harshly.\n";
            watcher_message = "A harsh tellurian ray strikes " +
                QTNAME(target) + " in the " + hitloc_desc + ", abrading " +
                target->query_objective()+ " harshly.\n";
            break;
            
        case 26..35:
            target_message = "A harsh tellurian ray blasts " +
                "your " + hitloc_desc + ", scouring you painfully.\n";
            watcher_message = "A harsh tellurian ray blasts into " +
                QTPNAME(target) + " " + hitloc_desc + ", scouring " +
                target->query_objective()+ " painfully.\n";
            break;
            
        case 36..45:
            target_message = "An intense tellurian ray blasts into " +
                "your " + hitloc_desc + ", eroding it horribly.\n";                
            watcher_message = "An intense tellurian ray blasts into " +
                QTPNAME(target) + " " + hitloc_desc + ", eroding it horribly.\n";
            break;
            
        case 46..55:
            target_message = "Your " + hitloc_desc + " is engulfed by a corroding "
                + "tellurian ray, causing severe damage.\n";
            watcher_message = QCTNAME(target) + " is engulfed by a corroding " +
                "tellurian ray, causing severe damage to " + 
                target->query_possessive() + " " +hitloc_desc+ ".\n";
            break;
                    
        case 56..99:
            target_message = "A mighty tellurian ray engulfs you, consuming your " +
                hitloc_desc+ " and causing you grievous injuries.\n";
            watcher_message = "A mighty tellurian ray engulfs " +QTNAME(target) + 
                ", consuming " + target->query_possessive() + " " + hitloc_desc + 
                " and causing " +target->query_objective()+ " grievous injuries.\n";
            break;
            
        default:
            target_message = "A deadly tellurian ray engulfs you, petrifying your " +
                hitloc_desc+ " and causing you fatal injuries!\n";
            watcher_message = "A deadly tellurian ray engulfs " + QTPNAME(target) + 
                " " +hitloc_desc+ " causing fatal injuries!\n";
            break;
        }
    }
        
    caster->catch_msg(watcher_message);
    target->catch_msg(target_message);
    target->tell_watcher(watcher_message, target, ({ caster, target }));

    if (objectp( target ) && (target->query_hp() <= 0) && 
        !target->query_prop(LIVE_I_NO_CORPSE))
    {
        corpse_sh = clone_object("/d/Krynn/throtyl/obj/petrify_corpse_sh");
        corpse_sh->shadow_me(target);
        target->do_die(caster); 
        corpse_sh->remove_shadow();
    }
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
    object target = targets[0];

    caster_message = "You point your petrified stick towards " + QTNAME(target) + 
        " and draw upon the powers of the dwarven Tree of Ancestors. ";
    target_message = QCTNAME(caster)+ " points " + caster->query_possessive() + " " +
        "petrified stick at you. ";

    watcher_message = QCTNAME(caster)+ " points " + caster->query_possessive() + " " +
        "petrified stick at " + QTNAME(target) + ". ";
    
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
