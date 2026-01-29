/*
 * Dimensional Rift cantrip for WoHS
 * (summons a creative trashcan)
 *
 * Created by Arman 2019.
 */
 
#pragma strict_types

#include <macros.h>
#include <tasks.h>
#include <stdproperties.h>
#include <flags.h>
#include <ss_types.h>
#include <files.h>
#include "defs.h"

#include "/d/Genesis/specials/local.h"
inherit SPELL_DIR + "summon";

/*
 * Function:    config_summon_spell
 * Description: Config function for summon spells. Redefine this in your
 *              own shadow spells to override the defaults.
 * Arguments:   Same as config_spell
 * Returns:     Same as config spell
 */
public void
config_summon_spell()
{
    set_spell_name("reskafar");
    set_spell_desc("Dimensional Rift - summon a rift in the fabric of space and time");

    set_spell_element(SS_ELEMENT_AIR, 60);
    set_spell_form(SS_FORM_CONJURATION, 60);

    set_ability_stats(STAT_WEIGHTING);

    set_spell_class(SPELL_CLASS_1);
    set_spell_task(TASK_SIMPLE);

    set_summon_file(SOHM_SPELL_OBJS + "reskafar_rift");   
    set_spell_object(SOHM_SPELL_OBJS + "reskafar_obj");
}

public string *
query_summon_ingredients(object caster)
{
    return ({ "brown slime" });
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
    return SOHM_MANAGER->query_memorised_spell(player,"reskafar_memorised");
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

        caster_message = "You close your eyes and begin chanting as you attempt " +
              "to make small tear in the fabric of space and time.\n";
        watcher_message = QCTNAME(caster) + " closes " + caster->query_possessive() + 
              " eyes and begins chanting.\n";
        
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
    
    if (!IS_MEMBER(caster))
    {
        caster->catch_tell("You are not a Wizard of High Sorcery!\n");
        return 0;
    }
    
    if (SOHM_MANAGER->is_casting_banned(caster))
    {
        caster->catch_tell("You have been banned from casting "
            + "spells for breaking the rules.\n");
        return 0;
    }
  
    return 1;
}