/*
 * Lifeward - Resist Magical Attacks
 * By Nerull, June 2021
 */

#include "/d/Genesis/specials/local.h"
inherit SPELL_DIR + "resistance";

#include <ss_types.h>
#include <composite.h>
#include <cmdparse.h>
#include <macros.h>
#include <tasks.h>
#include <composite.h>
#include "../guild.h"






/*
* Function:    config_shadow_spell
* Description: Config function for shadow spells. Redefine this in your
*              own shadow spells to override the defaults.
* Arguments:   Same as config_spell
* Returns:     Same as config spell
*/
public void
config_resistance_spell()
{
    set_spell_name("lifeward");
    set_spell_desc(" - Resist magic from the element of life");

    set_spell_element(SS_ELEMENT_DEATH, 50);
    set_spell_form(SS_FORM_ABJURATION, 50);
    set_spell_task(TASK_DIFFICULT);

    set_ability_stats(STAT_WEIGHTING);
    set_spell_class(SPELL_CLASS_3);
    
    set_spell_target(spell_target_caster);

    set_spell_object(VAMPIRES_SPELLOB_DIR + "lifeward_obj");
}


/*
* Function:    query_resistance_ingredients
* Description: This function defines what components are required for
*              this resistance spell.
*/
public string *
query_resistance_ingredients(object caster)
{
    return ({ });
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
    
    if (VAMPIRES_MAPPINGS->query_vampire_ability_occ_3(this_player()->query_name()) == 3)
    {
         return 1;
    }
    
    if (VAMPIRES_MAPPINGS->query_vampire_ability_occ_3(this_player()->query_name()) == 1)
    {
         return 1;
    }

    return 0;
}


public int
check_valid_action(object caster, mixed * targets, string arg, 
int execute = 0)
{
    int a = 0;
    
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
    
    if (present("_elusiveness_object", caster))
    {
        caster->catch_tell("You already are under the "
        +"effect of the elusiveness spell!\n");

        return 0;
    }
    
    if (present("_resilience_object", caster))
    {
        caster->catch_tell("You already are under the "
        +"effect of the resilience spell!\n");

        return 0;
    }
    
    if (present("_celerity_object", caster))
    {
        caster->catch_tell("You already are under the "
        +"effect of celerity!\n");

        return 0;
    }
     
    int resist_value = 30;                
    
    add_resistance(MAGIC_I_RES_LIFE, resist_value); 
    
    return 1;
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
    
    // Blood-drain
    int bloodamount = VAMPIRES_MAPPINGS->query_thirst_gauge(caster->query_real_name());     
    bloodamount = bloodamount - LIFEWARD_COST;   
    VAMPIRES_MAPPINGS->set_thirst_gauge(caster->query_name(), bloodamount);

    caster_message = "You concentrate on the restorative "
    +"properties of blood, that it gives both life "
    +"and unlife. Deeper and stronger you bend your "
    +"thoughts until, suddenly, you feel enhanced "
    +"with protection from the element of life.\n";
    
    watcher_message = QCTNAME(caster)
    +" concentrates on something.\n";

    caster->catch_tell(caster_message);
    tell_room(environment(caster), watcher_message, ({ caster }), caster);

    setuid();
    seteuid(getuid());
}


/*
* Function:    hook_describe_cast_resistance
* Description: Function that gets called to display the caster casting the
*              spell towards his intended targets.
*/
public void
hook_describe_cast_resistance(object caster, object * targets)
{
    caster->catch_tell("You cast Lifeward on yourself.\n");
}