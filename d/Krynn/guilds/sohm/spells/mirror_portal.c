/*
 * Cantrip allowing access to the Tower of High Sorcery for WoHS
 *
 * Coded by Arman 2017.
 */
 
#pragma strict_types

#include <macros.h>
#include <tasks.h>
#include <stdproperties.h>
#include <flags.h>
#include <ss_types.h>
#include <composite.h>
#include <files.h>
#include "defs.h"

#include "/d/Genesis/specials/local.h"
inherit SPELL_DIR + "propchange_base";

object * all_mirrors;

/*
 * Function:    config_propchange_spell
 * Description: Config function for propchange spell. Redefine this in your
 *              own propchange spells to override the defaults.
 */

public void
config_propchange_spell()
{
    set_spell_name("dotonobsule");
    set_spell_desc("Mirror portal - a command of activation for magical teleportation mirrors");

    set_spell_element(SS_ELEMENT_WATER,  20);
    set_spell_form(SS_FORM_DIVINATION, 20);

    set_ability_stats(STAT_WEIGHTING);

    set_spell_class(SPELL_CLASS_3);
    set_spell_task(TASK_HARD);

    set_spell_stationary(1);
    set_spell_offensive(0);
    set_spell_can_be_renewed(1);

    // Can only cast on self
    set_spell_target(spell_target_caster);
   
    set_shadow_filename(SOHM_SPELL_OBJS + "mirror_portal_sh");

}

/*
 * Function:    query_propchange_ingredients
 * Description: This function defines what components are required for
 *              this spell.
 */
public string *
query_propchange_ingredients(object caster)
{
    return ({  });
}

/* 
 * Function:    set_input_parameters
 * Description: This function should be overridden by the spell to set
 *              the input parameters that should be passed to the shadow
 *              object.
 */
public void
set_input_parameters(object caster, mixed * targets, int * resist, int result, mapping spell_input)
{
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
    return SOHM_MANAGER->query_memorised_spell(player,"dotonobsule_memorised");
}

public int
is_valid_mirror_for_spell(object caster, object obj)
{
    if (!objectp(obj) || !obj->id("_wohs_mirror_portal"))
    {
        return 0;
    }
    
    return 1;
}

static nomask object *
get_valid_mirrors_for_spell(object caster)
{
    if (!objectp(caster) || !objectp(environment(caster)))
    {
        return ({ });
    }
    return filter(all_inventory(environment(caster)), &is_valid_mirror_for_spell(caster,));    
}

public int 
check_valid_action(object caster, mixed * targets, string arg, int execute = 0)
{
    if (!::check_valid_action(caster, targets, arg, execute))
    {
        return 0;
    }

    all_mirrors = get_valid_mirrors_for_spell(caster);
    if (!sizeof(all_mirrors))
    {
        caster->catch_tell("There are no magical mirrors here you can use as a portal.\n");
        return 0;
    }
  
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
    object target = targets[0];

        caster_message = "You gesture slightly and utter a magical word of command: " +
              "'Doton Obsule!'\n";
        watcher_message = QCTNAME(caster) + " gestures slightly and utters a magical " +
              "word of command.\n";
        
    caster->catch_tell(caster_message);
    tell_room(environment(caster), watcher_message, ({ caster }), caster);

    setuid();
    seteuid(getuid());  
}

/*
 * Function:    hook_describe_cast_propchange
 * Description: Function that gets called to display the caster casting the
 *              spell towards his intended targets.
 */

public void
hook_describe_cast_propchange(object caster, object* targets)
{
    string mirror_desc = all_mirrors[0]->short();
    // caster->catch_msg("The " +mirror_desc+ " activates at your command!\n");
    all_mirrors->activate_magic_mirror(caster);
}

/*
 * Function:    hook_already_has_spell_object
 * Description: Function that gets called to tell the caster that the spell is
 *              already in effect on the target and cannot be stacked.
 */
public void
hook_already_has_spell_object(object caster, object target)
{
    caster->catch_msg("Dispel your existing maintained spell before casting " +
         "mirror portal!\n");
}