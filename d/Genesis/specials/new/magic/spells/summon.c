/*
 * General Summoning Spell
 * 
 * This is a generic summoning spell that should be used as the basis for all
 * summoning spells under the Genesis Magic system created in 2009.
 *
 * Created by Petros, March 2010
 * Adapted to generic summoning, May 2011
 */
 
#pragma strict_types

#include <macros.h>
#include <tasks.h>
#include <stdproperties.h>
#include <flags.h>
#include "defs.h"

inherit SPELL_DIR + "centralized_spell";
#include "centralized_spell_restrictions.h"

// Global Variables
public string   summon_file = "/std/messenger";
public int      summon_into_inventory = 1;

// Prototypes
public void         resolve_summon_spell(object caster, mixed * targets, int * resist, int result, mapping input);
public string *     query_summon_ingredients(object caster);
public void         set_summon_file(string file);
public void         set_summon_into_inventory(int bIntoInventory);

/*
 * Function:    config_summon_spell
 * Description: Config function for summon spells. Redefine this in your
 *              own summon spells to override the defaults.
 * Arguments:   Same as config_spell
 * Returns:     Same as config spell
 */
public void
config_summon_spell()
{
    // The default summon spell simply summons a messenger into the inventory of the caster
    set_summon_file("/std/messenger");
    set_summon_into_inventory(1);
    
    // Set the effect object filename
    set_spell_object(SPELL_OBJ_DIR + "summon_obj");
}

private nomask void
config_required_parameters()
{
    // Place required parameters here.
    set_spell_stationary(1); // can't summon a monster on the move
    set_spell_peaceful(1); // can't summon a monster in battle
}

/*
 * Function:    set_summon_file
 * Description: Use this to set a custom summoned object to be cloned
 *              when the spell is successfully cast.
 */
public void
set_summon_file(string file)
{
    summon_file = file;
}

/* 
 * Function:    query_messenger_file
 * Description: Returns the messenger file that should be cloned
 *              when this spell is successfully cast.
 */
public string
query_summon_file()
{
    if (!strlen(summon_file))
    {
        // Default to the standard messenger
        return "/std/messenger";
    }
    
    return summon_file;
}

/*
 * Function:    set_summon_into_inventory
 * Description: Set whether the summoned npc that is summoned goes into
 *              the inventory by default, or if it goes into the environment
 * Arguments:   bIntoInventory - If 0, then summon into environment. Otherwise
 *                               summon it into the inventory.
 */
public void         
set_summon_into_inventory(int bIntoInventory)
{
    summon_into_inventory = bIntoInventory;
}

/*
 * Function:    query_summon_into_inventory
 * Description: Returns whether the npc that is summoned goes into
 *              the inventory of the caster.
 */
public int
query_summon_into_inventory()
{
    return summon_into_inventory;
}

public nomask void
config_spell()
{
    ::config_spell();

    set_spell_name("summon");
    set_spell_desc("Summon monster");

    set_spell_vocal(1);
    set_spell_visual(1);
    set_spell_stationary(1);
    set_spell_peaceful(1);
    set_spell_offensive(0);
    
    set_spell_mana(30);
    set_spell_task(TASK_ROUTINE);
    set_spell_time(4);
    set_spell_target(spell_target_caster);
    set_spell_ingredients(query_summon_ingredients);

    set_spell_fail("You fail in your efforts to invoke the spell.\n");
    
    // We set defaults for the spell element and form here. 
    // Each spell should customize these to their specific guild
    // skills.
    set_spell_element(SS_ELEMENT_LIFE, 10);
    set_spell_form(SS_FORM_CONJURATION, 15);
        
    // Call the specific configuration that is to be masked.
    config_summon_spell();
    
    // Call this after the config_summon_spell to ensure that
    // required parameters aren't overridden
    config_required_parameters();
}

/*
 * Function name: resolve_spell
 * Description:   Complete the casting of the spell
 * Arguments:     object caster   - the caster
 *                mixed *targets - an array of targets
 *                int *resist     - resistance percentages corresponding to
 *                                  each target
 *                int result      - how well the spell was cast
 */
public nomask void
resolve_spell(object caster, mixed * targets, int * resist, int result)
{
    mapping input = ([ ]);
    resolve_summon_spell(caster, targets, resist, result, input);

    // The spell object is created and moved to the target. It will
    // do all the descriptions in the spell object.
    input["summon_file"] = query_summon_file();
    input["summon_into_inventory"] = query_summon_into_inventory();
    make_spell_object(query_spell_object(), caster, targets, resist, result, input);
}

// HOOKS TO BE DEFINED

/*
 * Function:    resolve_summon_spell
 * Description: Called at the beginning of resolve_spell in order to perform
 *              spell specific actions.
 * Arguments:   Same as resolve_spell
 */
public void
resolve_summon_spell(object caster, mixed * targets, int * resist, int result, mapping input)
{
}

/*
 * Function:    query_summon_ingredients
 * Description: This function defines what components are required for
 *              this summon spell.
 */
public string *
query_summon_ingredients(object caster)
{
    return ({ });
}

