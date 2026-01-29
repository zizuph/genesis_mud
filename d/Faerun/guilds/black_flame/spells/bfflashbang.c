/*
 *
 */
 
#include "/d/Genesis/specials/local.h"
inherit SPELL_DIR + "blind";

#include <ss_types.h>
#include <macros.h>
#include <composite.h>
#include <tasks.h>
#include "../guild.h"


/*
 * Function:    config_blind_spell
 * Description: Config function for blind spells. Redefine this in your
 *              own blind spells to override the defaults.
 * Arguments:   Same as config_spell
 * Returns:     Same as config spell
 */
public void
config_blind_spell()
{
    set_spell_name("flashbang");
    set_spell_desc(" - Blind all creatures sensitive to light");
    set_ability_stats(STAT_WEIGHTING);
    set_spell_class(SPELL_CLASS_3);
    set_spell_task(TASK_HARD);    
    set_spell_element(SS_ELEMENT_FIRE, 50);
    set_spell_form(SS_FORM_CONJURATION, 50);
 
    // 2.0 times the standard cast time for a harm spell 
    set_spell_time_factor(2.0); 
    set_spell_combat_aid(50.0); 
    
    set_spell_target(spell_target_present_enemies);
    set_spell_ingredients(query_blind_ingredients);
    set_spell_object(BF_SPELLOB_DIR + "flashbang_blind_obj");
        
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
	
	if (player->query_guild_level_lay() >= GIFT_6)
    {
         return 1;
    }
    
	return 0;
}


/*
 * Function:    query_spell_combat_aid_modifier
 * Description: Value between 1.0 and 100.0 that will modify
 *              the maximum combat aid granted by this spell.
 */
public float
query_spell_combat_aid_modifier()
{
    float total_combat_aid = 0.0;   

    if ((present("_frenzy_object", this_player())))
    {
        // Frenzy counts for 30 caid.
        total_combat_aid = 20.0;
		
        return (total_combat_aid / 50.0) * 100.0;
        
    }
   
    total_combat_aid = 50.0;
	
    return (total_combat_aid / 50.0) * 100.0;
}


/*
 * Function name : resolve_spell_resisted
 * Description   : The spell was resisted, this hook allows for writing
specific methods.
 * Arguments     : object caster - The caster of the spell.
 *               : object target - The target of the spell.
 *               : int resist    - The resist value.
 *               : int result    - How well the spell was cast.
 */
public void
resolve_spell_resisted(object caster, object target, int resist, int result)
{
    caster->catch_msg(QCTNAME(target)+" resisted your spell.\n");
}


public int 
check_valid_action(object caster, mixed * targets, string arg, int execute = 0)
{
    if (!::check_valid_action(caster, targets, arg, execute))
    {
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
    string caster_message, caster_name, watcher_message;
    
    caster_name = capitalize(caster->query_real_name());
	
    caster_message = "You invoke the power of Kossuth!\n";
		
    watcher_message = QCTNAME(caster)
    +" invokes the power of Kossuth!\n";
        
    caster->catch_tell(caster_message);
	
    tell_room(environment(caster), watcher_message, 
    	({ caster }), caster);
    
    setuid();
    seteuid(getuid());
}


public void
hook_describe_blind(object caster, mixed * targets, int result)
{
    string caster_message, target_message, watcher_message;
    string caster_name; 
    string go_plural;
    
    caster_name = capitalize(caster->query_real_name());
	
    if(sizeof(targets) > 1)
      go_plural = "them";
    else
      go_plural = targets[0]->query_objective();
      
    caster_message= "You invoke the power of Kossuth! with a "
	+"snap of your fingers. A vortex of "+
		      "bright blinding fire suddenly appear and rushes towards "+
		      COMPOSITE_LIVE(targets) +"\n";
			  
    target_message = QCTNAME(caster) + " snaps " + 
    		  caster->query_possessive() +
			  " fingers. A vortex of bright blinding fire "
			  +"suddenly appear out of nowhere and rushes towards you!\n";
			  
    watcher_message = QCTNAME(caster) + " snaps " + 
    		  caster->query_possessive() +
			  " fingers. A vortex of bright blinding fire "
			  +"suddenly appear out of nowhere and rushes towards " 
			  + COMPOSITE_LIVE(targets)+".\n";
	
	caster->catch_msg(caster_message);
	
    targets->catch_msg(target_message);
	
    caster->tell_watcher(watcher_message, targets, 
    	({ caster }) + targets);
}


/*
 * Function:    query_blind_ingredients
 * Description: This function defines what components are required for
 *              this blind spell.
 */
public string *
query_blind_ingredients(object caster)
{
    return ({ "_flashbang_charge" });
}


/* Had to mask the below function from spell_targetting.c */
public object *
spell_target_present_enemies(object actor, string str)
{
    object *enemies = (object *)actor->query_enemy(-1) &
        all_inventory(environment(actor));
		
    if (!sizeof(enemies))
    {
        actor->catch_msg("You must be engaged in combat for "
		+"this spell!\n");
		   
        return ({});
    }
	
    return enemies;
}