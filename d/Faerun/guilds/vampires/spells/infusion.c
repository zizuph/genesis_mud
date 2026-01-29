/*
 * Infusion - Restore fatigue
 * By Nerull, 2022
 */

#pragma strict_types

#include "/d/Genesis/specials/local.h"
inherit SPELL_DIR + "refresh";

#include <ss_types.h>
#include <macros.h>
#include <composite.h>
#include <tasks.h>
#include "../guild.h"

/*
 * Function:    config_refresh_spell
 * Description: Config function for refresh spells. Redefine this in your
 *              own refresh spells to override the defaults.
 * Arguments:   Same as config_spell
 * Returns:     Same as config spell
 */
public void
config_refresh_spell()
{
    //set_ability_group(LAY_VAMPIRES_GUILD_NAME);
    set_spell_name("infusion");
    set_spell_desc(" - Refreshing fatigue Through the power of the blood");

    set_spell_element(SS_ELEMENT_DEATH, 10);
    set_spell_form(SS_FORM_ENCHANTMENT, 15);

    set_ability_stats(STAT_WEIGHTING);

    set_spell_class(SPELL_CLASS_1);

    set_spell_task(TASK_EASY);

    set_spell_vocal(1);
    set_spell_visual(1);
    set_spell_stationary(1);
    set_spell_peaceful(0);
    set_spell_offensive(0);
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
    
    if (VAMPIRES_MAPPINGS->query_vampire_ability_occ_3(this_player()->query_name()) > 0)
    {
         return 1;
    }
    
    return 0;
}


/*
 * Function:    query_refresh_ingredients
 * Description: This function defines what components are required for
 *              this refresh spell.
 */
public string *
query_refresh_ingredients(object caster)
{
    return ({  });
}


public int 
check_valid_action(object caster, mixed * targets, string arg, int execute = 0)
{
    if (!::check_valid_action(caster, targets, arg, execute))
        return 0;

    if (!present("_vampire_powers_unlock_ob", caster))
    {
        caster->catch_tell("You are too weak! You "
        +"need to rise from a coffin in order to use this gift.\n");
        
        return 0;
    }
    
    int check = VAMPIRES_MAPPINGS->query_thirst_gauge(caster->query_real_name());
    
    if (caster->query_ethereal() == 1)
    {
        caster->catch_tell("You are in the ethereal realm. This spell "
        +"doesn't work there.\n");
        
        return 0;
    }

    object target = targets[0];
    int fatigue = target->query_fatigue();
    int max_fatigue = target->query_max_fatigue();

    if(fatigue == max_fatigue)
    {
        caster->catch_tell(target->query_The_name(caster) + " is " +
           "extremely alert and not in need of aid.\n");
           
        return 0;
    }
    
    if (!targets[0]->query_prop(LIVE_I_UNDEAD))
    {
        write("This spell has no effect on the living.\n");
        return 0;
    }

    return 1;
}


/*
 * Function:    resolve_refresh_spell
 * Description: Called at the beginning of resolve_spell in order to perform
 *              spell specific actions.
 * Arguments:   Same as resolve_spell
 */
public void
resolve_refresh_spell(object caster, mixed * targets, int * resist, int result)
{
    object target = targets[0];
    int fatigue = target->query_fatigue();
    int max_fatigue = target->query_max_fatigue();
    int fatigue_xp = min(50, (result / 4));

    if(fatigue == max_fatigue)
    {
    //  DEBUG("ofatigue no fatigue to heal, result " +result+ ".");
    }
    else
    {
    //  DEBUG("ofatigue: " +fatigue+ ", result: " +result+ ", xp: " +fatigue_xp+ ".");
        //OOTS_ADD_EXP(caster, fatigue_xp); 
    }

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
    
    // Blood-drain
    int bloodamount = VAMPIRES_MAPPINGS->query_thirst_gauge(caster->query_real_name());     
    bloodamount = bloodamount - INFUSION_COST;   
    VAMPIRES_MAPPINGS->set_thirst_gauge(caster->query_name(), bloodamount);
    
    caster_message = "You concentrate on the restorative "
    +"properties of dark energy.\n";
    
    watcher_message = QCTNAME(caster)
    +" concentrates on something.\n";

    caster->catch_tell(caster_message);
    tell_room(environment(caster), watcher_message, ({ caster }), caster);

    setuid();
    seteuid(getuid());
}


/*
 * Function name: desc_refresh_cast
 * Description:   Describe casting of the spell to cure fatigue.
 *                This can be redefined for custom messages.
 * Arguments:     object caster - the caster
 *                object * targets - the targets 
 *                int amount - the amount refreshed
 */
public void
desc_refresh_cast(object caster, object * targets, int amount)
{
    object tar = targets[0];
    int heal = amount;
    string heal_desc;

    switch(heal)
    {
       case 0..10:
         heal_desc = " slightly";
         break;
       case 11..20:
         heal_desc = " somewhat";
         break;
       case 21..30:
         heal_desc = "";
         break;
       case 31..40:
         heal_desc = " greatly";
         break;
       case 41..100:
         heal_desc = " enormously";
         break;
       default:
         heal_desc = "";
         break;
    }

    if (tar == caster)
    {
        caster->catch_tell("By focusing the power of the blood, your "
        +"fatigue is restored"+heal_desc+ "!\n");   
            
        tell_room(environment(caster),
        QCTNAME(caster)+" appears to be less fatigued!\n", tar);
    }
    else
    {  
        caster->catch_tell("You discreetly channel dark energy into "
        +"the body of "
        +tar->query_the_name(caster)+", who suddenly "
        +"looks less fatigued!\n");
        
        tar->catch_tell("You feel dark energy is channeled into your "
        +"very being from someone. You feel" +heal_desc+ " relieved from "
        +"your taxing burden!\n");
                       
        tell_room(environment(caster), QCTNAME(tar)+" suddenly "
        +"looks"+heal_desc+ " less fatigued.\n", ({ caster, tar }), caster);
    }

    // DEBUG("Refreshed amount: " +heal+ ".");
}


/*
 * Function:    query_spell_power
 * Description: A generic power calculation function that takes into
 *              account skills, stats, and guild strength
 */
public int
query_spell_power()
{
    mixed *items = check_required_items(this_player(), ({}), "", 0);
    return max(1, query_ability_power(this_player(), ({}), items));
}
