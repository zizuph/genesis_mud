/*
 * Mass harm spell.
 *
 */

#include "/d/Genesis/specials/local.h"
inherit SPELL_DIR + "massharm";

#include <macros.h>
#include <tasks.h>
#include <stdproperties.h>
#include <flags.h>
#include <ss_types.h>
#include <files.h>
#include <composite.h>
#include "../guild.h"

#define HIM(x)        ((x)->query_objective())

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
    set_spell_name("swarm");
    set_spell_desc(" - Batter an enemy team with a swarm of bats");

    set_ability_stats(STAT_WEIGHTING);
    set_spell_class(SPELL_CLASS_4);

    set_spell_combat_aid(50.0);
    set_spell_task(TASK_DIFFICULT);

    set_spell_time_factor(3.0);
  
    /* Limit spell targets */
    set_spell_target_limit(3);
    
    set_spell_element(SS_ELEMENT_AIR, 50);
    set_spell_form(SS_FORM_CONJURATION, 50);
}


/*
 * Function:    query_harm_ingredients
 * Description: This function defines what components are required for
 *              this harm spell.
 */
public string *
query_massharm_ingredients(object caster)
{ 
    return ({  });
}


/*
* Function:    query_spell_can_be_learned
* Description: Place restrictions on whether this spell can be used
*              by the guild member.
*/
public int
query_spell_can_be_learned(object player)
{
    setuid();
    seteuid(getuid());

    if (!objectp(player))
    {
        return 0;
    }

    if (player->query_npc())
    {
        // npcs can always learn the spell.
        return 1;
    }
    
    if (VAMPIRES_MAPPINGS->query_vampire_ability_occ_4(this_player()->query_name()) > 0)
    {
         return 1;
    }
    
    /*if (VAMPIRES_MAPPINGS->query_vampire_ability_occ_4(this_player()->query_name()) == 2)
    {
         return 1;
    }*/

    return 0;
}


public int
check_valid_action(object caster, mixed * targets, string arg, 
int execute = 0)
{
    if (!::check_valid_action(caster, targets, arg, execute))
    {
        return 0;
    }
    
    if (!present("_vampire_powers_unlock_ob", caster))
    {
        caster->catch_tell("You are too weak! You "
        +"need to rise from a coffin in order to use this gift.\n");
        
        return 0;
    }
    
    int check = VAMPIRES_MAPPINGS->query_thirst_gauge(caster->query_real_name());
    
    if (check < ABILITY_THRESHOLD)
    {
        caster->catch_tell("The thirst is too overwhelming for you to "
        +"concentrate. Aquire more blood!\n");
        
        return 0;
    }
    
    if (caster->query_ethereal() == 1)
    {
        caster->catch_tell("You are in the ethereal realm. This spell "
        +"doesn't work there.\n");
        
        return 0;
    }
       
    if ((present("_elusiveness_object", caster)) && (present("_amplify_object", caster)))
    {
        caster->catch_tell("You already are under the "
        +"effect of elusiveness and amplify!\n");

        return 0;
    }
    
    if ((present("_resilience_object", caster)) && (present("_amplify_object", caster)))
    {
        caster->catch_tell("You already are under the "
        +"effect of resilience and amplify!\n");

        return 0;
    }
    
    if ((present("_celerity_object", caster)) && (present("_amplify_object", caster)))
    {
        caster->catch_tell("You already are under the "
        +"effect of celerity and amplify spell!\n");

        return 0;
    }
    
    if ((present("_protect_life_object", caster)) && (present("_amplify_object", caster)))
    {
        caster->catch_tell("You already are under the "
        +"effect of lifeward and amplify!\n");

        return 0;
    }
    
    return 1;
}


/*
 * Function:    query_spell_combat_aid_modifier
 * Description: Value between 1.0 and 100.0 that will modify
 *              the maximum combat aid granted by this spell.
 */
public float
query_spell_combat_aid_modifier()
{
     return 100.0;
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
    
    caster_message = "You concentrate on the powers of the blood!\n";
    
    watcher_message = QCTNAME(caster)
    +" concentrates on something.\n";
        
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
    
    setuid();
    seteuid(getuid());

    if (phurt < 0)
    {
        // Missed! give the miss messages.
        target_message = "A huge swarm of bats suddenly flies in "
        +"and just brushes over your head before disappearing again.\n";
        
        watcher_message = "A huge swarm of bats suddenly flies in "
        +" and just brushes over " +QTNAME(target) + "'s head before "
        +"disappearing again.\n";
    }
    else
    {        
        switch (phurt) // percentage hurt
        {
            case 0..99:

            target_message = "A black shadow appears out of nowhere, "
            +"writhing and churning as though a wave of life. Larger and "
            +"larger it grows, rushing toward you find yourself engulfed in a "
            +"sea of shrieking, biting and clawing bats! They are in your "
            +"hair, screeching in your ears, flapping against your skin and "
            +"cutting your flesh with sharp claws! You are "
            +"gripped with panic while bleeding from everywhere!\n";

            watcher_message = "A legion of bats writhes and churns, growing in size "
            +"until it completely engulfs "+QCTNAME(target)+" in a tumult of shrieks "
            +", flapping, biting and claws cutting flesh!\n"; 
            break;
            
            default:
            target_message = "A black shadow appears out of nowhere, "
            +"writhing and churning as though a wave of life. Larger and "
            +"larger it grows, rushing toward you find yourself engulfed in a "
            +"sea of shrieking, biting and clawing bats! They are in your "
            +"hair, screeching in your ears, flapping against your skin and "
            +"cutting your flesh with sharp claws! You are "
            +"gripped with panic while bleeding from everywhere!\n";

            watcher_message = "A legion of bats writhes and churns, growing in size "
            +"until it completely engulfs "+QCTNAME(target)+" in a tumult of shrieks "
            +", flapping, biting and claws cutting flesh!\n"; 
           
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

    caster_message = "You glance furiously at " 
    + COMPOSITE_LIVE(targets)+"!\n";
        
    target_message = QCTNAME(caster)+ " glances furiously at you!\n";

    watcher_message = QCTNAME(caster)+ " glances furiously at " 
    + COMPOSITE_LIVE(targets) + "!\n";
    
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
   write("You lack the preparation to cast this spell.\n");
}

public void
hook_no_present_targets(object actor, string str)
{
    actor->catch_msg("You must first be in combat before you can call on "
    + "this spell!\n");   
}
