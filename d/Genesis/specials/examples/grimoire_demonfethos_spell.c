/*
 * Demonfethos - tutorial protection from demons spell 
 */

#pragma strict_types

#include "/d/Genesis/specials/local.h"
inherit SPELL_DIR + "stoneskin";

#include <wa_types.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <files.h>
#include <composite.h>

#include <macros.h>
#include <tasks.h>

/*
 * Function:    config_stoneskin_spell
 * Description: Config function for stoneskin spells. Redefine this in your
 *              own stoneskin spells to override the defaults.
 * Arguments:   Same as config_spell
 * Returns:     Same as config spell
 */

public void
config_stoneskin_spell()
{
    set_spell_name("demonfethos");
    set_spell_desc("A shield of magical protection from demons");

    set_spell_task(TASK_ROUTINE);
    set_spell_element(SS_ELEMENT_AIR,  0);
    set_spell_form(SS_FORM_ABJURATION, 0);

    set_spell_combat_aid(10.0);
    set_spell_fail("You fail in your efforts to summon a shield of protection.\n");

    // Can only cast demonfethos on themself
    set_spell_target(spell_target_caster);

    // Spell effect object
    set_spell_object("/d/Genesis/specials/examples/grimoire_demonfethos_obj");

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

    return 1;
}

/*
 * Function:    query_stoneskin_ingredients
 * Description: This function defines what components are required for
 *              this stoneskin spell.
 */
public string *
query_stoneskin_ingredients(object caster)
{
    return ({ "stiltberry" });
}

void
hook_use_ingredients(object *ingrs)
{
    write("The gleaming silver berry blackens, then crumbles to dust.\n");

}

/*
 * Function:    query_spell_ingredients_description
 * Description: Returns a string description of the ingredients. Can be used
 *              in messages to casters about what is actually required
 *              for this spell.
 */
public string
query_spell_ingredients_description()
{
    return "stiltberry";
}


public int 
check_valid_action(object caster, mixed * targets, string arg, int execute = 0)
{
    if (!::check_valid_action(caster, targets, arg, execute))
        return 0;

    if(caster->query_skill(SS_SPELLCRAFT) < 15)
    {
       caster->catch_tell("You need to be trained in spellcraft to at least " +
           "confident amateur to cast this spell.\n");
       return 0;
     }

    return 1;
}

public void
hook_already_has_spell_object(object caster, object target)
{
    write("You already have summoned magical shield protecting you from demons.\n");
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
    write("You are missing an ingredient to invoke the protection from demons! You " +
        "require a gleaming silver berry known as 'stiltberry' to cast this spell.\n");
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

        caster_message = "You begin reciting from the leather-bound grimoire"
            + " magical words of protection, 'Demonfethos!'\n";
        watcher_message = QCTNAME(caster) + " begins reciting from a leather-"
            +"bound grimoire magical words of protection.\n";
        
    caster->catch_tell(caster_message);
    tell_room(environment(caster), watcher_message, ({ caster }), caster);

    setuid();
    seteuid(getuid());  
}

/*
 * Function name: list_spells
 * Description:   This function is called to list the spells from
 *                the player soul when the command "prayers" is used. 
 */
public void
list_spells()
{
    string ingredients_description = query_spell_ingredients_description();
    if (!strlen(ingredients_description))
    {
        ingredients_description = "stiltberry";
    }
    write(sprintf("%-15s %s (%s)\n", query_spell_name(), ::query_spell_desc(),
        ingredients_description));
}
