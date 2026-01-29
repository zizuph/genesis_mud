/*
 *  Destroys a magical item to learn its properties.
 *
 *  Nerull 2017
 * 
 * Updated to inherit from /d/Genesis/specials/new/magic/
 * Arman (AoB) December 2021
 *
*/

#include <ss_types.h>
#include <composite.h>
#include <cmdparse.h>
#include <macros.h>
#include <tasks.h>
#include <composite.h>
#include "../guild.h"

#include "/d/Genesis/specials/local.h"
inherit SPELL_DIR + "identify";

/*
 * Function:    config_identify_spell
 * Description: Config function for identify spells. Redefine this in your
 *              own identify spells to override the defaults.
 */

public void
config_identify_spell()
{
    set_spell_name("kahera");
    set_spell_desc("Destroys a magical item to learn its properties");
    set_spell_desc(" - Disenchant: Destroys a magical item to learn its magical secrets");
    set_spell_element(SS_ELEMENT_AIR, 30);
    set_spell_form(SS_FORM_ENCHANTMENT, 30);
    set_spell_task(TASK_ROUTINE);

    set_ability_stats(STAT_WEIGHTING);
    set_spell_class(SPELL_CLASS_2);
}


/*
 * Function:    resolve_identify_spell
 * Description: Called at the beginning of resolve_spell in order to perform
 *              spell specific actions.
 * Arguments:   Same as resolve_spell
 */
public void
resolve_identify_spell(object caster, mixed * targets, int * resist, int
result)
{
}


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
    
    // Testing access
    if (present("_nerullian_object_", this_player()))
    {
        return 1;
    }
    
    // If we are testing spells regardless of rank and selection.
    if (SPELLTESTING == 1)
    {
        return 1;
    }

    if (WARLOCK_MASTER->is_lay_warlock(this_player()->query_name()))
    {
        if (WARLOCK_MAPPINGS->query_desecration_power(this_player()->query_name()) >= FULL_WARLOCK_UNLOCK)
        {
            if (WARLOCK_MASTER->is_patr1_warlock(this_player()->query_name())
            || WARLOCK_MASTER->is_patr2_warlock(this_player()->query_name())
            || WARLOCK_MASTER->is_patr3_warlock(this_player()->query_name()))
            {
                return 1;
            }
        }
    }
    
    if (WARLOCK_MASTER->is_occ_warlock(this_player()->query_name()))
    {
        if (WARLOCK_MAPPINGS->query_desecration_power(this_player()->query_name()) >= FULL_WARLOCK_UNLOCK)
        {
            if (WARLOCK_MASTER->is_patr1_warlock(this_player()->query_name())
            || WARLOCK_MASTER->is_patr2_warlock(this_player()->query_name())
            || WARLOCK_MASTER->is_patr3_warlock(this_player()->query_name()))
            {
                return 1;
            }
        }
    }

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
    
    object target = targets[0];
    
    if (IS_LIVING_OBJECT(target))
    {
        caster->catch_tell("You can only use this spell on magical items, not " +
           "living creatures.\n");
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

    caster_message = "As you surreptitiously whisper the long "
    +"forgotten words, the sounds reverberates in increasing "
    +"intensity, only to fade as you draw arcane powers from the "
    +"shadows!\n";
    
    watcher_message = "A chorus of eerie whispers permeate the area in "
    +"increasing intensity, only to fade again as "+QCTNAME(caster)
    +" turns inwards.\n";

    caster->catch_tell(caster_message);
    tell_room(environment(caster), watcher_message, ({ caster }), caster);

    setuid();
    seteuid(getuid());
}


/*
 * Function:    hook_identify_sucess
 * Description: Mask this function to change the description of when
 *              the object is successfully identified.
 */
public void
hook_identify_success(object caster, object target, string id_message, int
result)
{
    if (!objectp(caster) || !objectp(target))
    {
        return;
    }
    
    if (target->query_prop(OBJ_I_IS_MAGIC_ARMOUR) ||
        target->query_prop(OBJ_I_IS_MAGIC_WEAPON))
    {
        tell_room(environment(caster), QCTNAME(caster) + " channels powerful "
        +"energies into the "+target->query_short()+"!\nThe "
        +target->query_short()+" is destroyed!\n", caster);
        
        caster->catch_tell("You channel powerful energies "
        +"into the "+target->query_short() + "!\n");
        
        caster->catch_tell(id_message);
        
        caster->catch_tell("The "+target->query_short() + " is destroyed entirely "
        +"in the process!\n");
            
        target->remove_object();
        
        return;
    }
    
    tell_room(environment(caster), QCTNAME(caster) + " channels powerful "
    +"energies into the "+target->query_short()+"!\nThe "
    +target->query_short()+" is destroyed!\n", caster);
    
    caster->catch_tell("You channel powerful energies "
    +"into the "+target->query_short() + "!\n");
    
    caster->catch_tell("This item did not contain any magical "
    +"energies, so Kahera fizzles.\n");
    
    return;
}


/*
 * Function:    query_identify_ingredients
 * Description: This function defines what components are required for
 *              this identify spell.
 */
public string *
query_identify_ingredients(object caster)
{
    // If we are testing spells, no components
    if (SPELLTESTING_NOCOMPS == 1)
    {
        return ({ });
    }
    
    // Using the worth of the component as a charge since it's
    // consumed in the process.
    return ({ });
    
    //return ({ "_desecrate_charge" });
}


