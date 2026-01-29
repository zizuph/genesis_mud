/*
 * Curse (illfortunate) spell for SoHM
 *
 * Chikohk created by Arman, 2016
 * 
 * Base spell created by Navarre, September 2009
 * Modified by Petros, July 2016
 */
 
#pragma strict_types

#include <ss_types.h>
#include <macros.h>
#include <tasks.h>
#include <composite.h>
#include "defs.h"
#include "/d/Krynn/common/defs.h"

#include "/d/Genesis/specials/local.h"
inherit SPELL_DIR + "illfortunate";

#include "sohm_spell_functions.h"

#define ACTIVE_CURSE "_sohm_minor_curse_active"

/*
 * Function:    config_illfortunate_spell
 * Description: Config function for illfortunate spell. Redefine this in your
 *              own illfortunate spells to override the defaults.
 */
public void
config_illfortunate_spell()
{
    set_spell_name("chikohk");
    set_spell_desc("Curse - curse someone with uncertainty in battle");

    set_spell_element(SS_ELEMENT_AIR, 30);
    set_spell_form(SS_FORM_ENCHANTMENT, 30);

    set_ability_stats(STAT_WEIGHTING);

    set_spell_class(SPELL_CLASS_2);
    set_spell_task(TASK_EASY);    

    set_spell_combat_aid(25);

    // 1 herb per cast effects that last < 30 seconds
    set_spell_component_factor(COMPONENT_AID_HIGH);

    // Set the effect shadow
    set_shadow_filename(SOHM_SPELL_OBJS + "curse_sh");

}

/*
 * Function: query_illfortunate_ingredients
 * Description: This function defines the components to use for this spell.
 * Arguments: The caster of this spell
 */
public string*
query_illfortunate_ingredients(object caster)
{
    return ({ "myrtleberry" });
}

public int 
check_valid_action(object caster, mixed * targets, string arg, int execute = 0)
{
    if (!::check_valid_action(caster, targets, arg, execute))
    {
        return 0;
    }

    if(query_maintained_defensive_caid_spells(caster, "minor") > 2)
    {
	caster->catch_tell("You can only maintain three minor spells " +
           "that provide combat utility at any time.\n");
	return 0; 
    }

    object tar = targets[0];
    if(tar->query_has_sohm_curse_shadow())
    {
        caster->catch_tell("A curse of uncertainty has already been cast " +
            "upon " +COMPOSITE_LIVE(targets)+ ".\n");
        return 0;
    }
        
    return 1;
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
    return SOHM_MANAGER->query_memorised_spell(player,"chikohk_memorised");
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

        caster_message = "You raise your hands in the air and invoke a word " +
            "of a power, 'chikohk!'\n";
        watcher_message = QCTNAME(caster) + " raises " +HIS(caster)+ " hands " +
            "in the air and invokes a dire word of power.\n";
        
    caster->catch_tell(caster_message);
    tell_room(environment(caster), watcher_message, ({ caster }), caster);

    setuid();
    seteuid(getuid());    
}

/*
 * Function:    hook_describe_cast_illfortunate
 * Description: Function that gets called to display the caster casting the
 *              spell towards his intended targets.
 */
public void
hook_describe_cast_illfortunate(object caster, object* targets)
{
    caster->catch_tell("You invoke a curse upon " +COMPOSITE_LIVE(targets) + 
                       ".\n");
    caster->tell_watcher(QCTNAME(caster) + " invokes a curse.\n", ({ }) );
}
/*
 * Function:    hook_already_has_spell_object
 * Description: Function that gets called to tell the caster that the spell is
 *              already in effect on the target and cannot be stacked.
 */
public void
hook_already_has_spell_object(object caster, object target) 
{
    caster->catch_msg(QCTNAME(target) + " is already cursed!\n");
}
/*
 * Function:    hook_curse_resisted
 * Description: Function that gets called to tell that the spell did
 *              not succeed against the targets.
 */
public void
hook_illfortunate_resisted(object caster, object* targets)
{
    caster->catch_msg("You sense that " + COMPOSITE_LIVE(targets) + " is " +
                      "unaffected by your spell.\n");
    targets->catch_msg("You resist an attempt by " + QTNAME(caster) +
                       "to curse you.\n");
    caster->tell_watcher(QCTPNAME(caster) + " invocation of a curse was " +
                         "resisted by " + COMPOSITE_LIVE(targets) + ".\n",
                         ({ caster }) + targets); 
}
