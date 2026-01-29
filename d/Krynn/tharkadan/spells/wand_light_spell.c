/*
 * A version of the SoHM light spell for the magic light wand
 *
 * Coded by Arman 2017.
 */
 
#pragma strict_types

#include <macros.h>
#include <tasks.h>
#include <stdproperties.h>
#include <flags.h>
#include <ss_types.h>
#include <files.h>
#include "/d/Krynn/guilds/sohm/defs.h"

inherit "/d/Genesis/specials/std/spells/light";

/*
 * Function:    config_light_spell
 * Description: Config function for light spells. Redefine this in your
 *              own light spells to override the defaults.
 * Arguments:   Same as config_spell
 * Returns:     Same as config spell
 */
public void
config_light_spell()
{
    set_spell_name("shirak");
    set_spell_desc("Light - a spell of illumination");

    // We set defaults for the spell element and form here. 
    // Each spell should customize these to their specific guild
    // skills.
    set_spell_element(SS_ELEMENT_FIRE,  0);
    set_spell_form(SS_FORM_TRANSMUTATION, 0);
    set_spell_task(TASK_ROUTINE);

    set_spell_vocal(1);
    set_spell_visual(0);
    set_spell_stationary(0);
    set_spell_peaceful(0);
    set_spell_offensive(0);
    set_spell_can_be_renewed(1);
   
    set_spell_object(SOHM_SPELL_OBJS + "light_obj");
}



/*
 * Function:    query_light_ingredients
 * Description: This function defines what components are required for
 *              this light spell.
 */
public string *
query_light_ingredients(object caster)
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

    return 1;
}

int
filter_tool(object obj)
{
      if (obj->id("wand"))
          return 1;
      else if (obj->id("staff"))
          return 1;
      else if (obj->id("tome"))
          return 1;
      else 
          return 0;
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
    object *wep;
    /* Filter out non-staffs and wands */
    wep = filter(caster->query_tool(-1), filter_tool);

    caster_message = "You raise your "+wep[0]->short()+" and " +
        "whisper the arcane word for illumination, 'Shirak!'\n";
    watcher_message = QCTNAME(caster) + " raises " + 
        caster->query_possessive() +" "+wep[0]->short()+" and " +
        "whispers a word of magic, 'Shirak!'\n";
        
    caster->catch_tell(caster_message);
    tell_room(environment(caster), watcher_message, ({ caster }), caster);

    setuid();
    seteuid(getuid());  
}

public int 
check_valid_action(object caster, mixed * targets, string arg, int execute = 0)
{
    if (!::check_valid_action(caster, targets, arg, execute))
    {
        return 0;
    }

    object *weapon;

    /* Filter out non-staffs */
    if(caster->query_tool(-1))
      weapon = filter(caster->query_tool(-1), filter_tool);  

    if(!sizeof(weapon))
    {
        caster->catch_tell("You aren't holding or wielding the right " +
            "item to do that.\n");
	return 0;
    }
  
    return 1;
}