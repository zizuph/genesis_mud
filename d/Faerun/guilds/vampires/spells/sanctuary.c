/*
 * 
 *  A regular teleport to sanctuary spell. Nerull 2021.
 */

#include "/d/Genesis/specials/local.h"
inherit SPELL_DIR + "teleport";

#include <macros.h>
#include <files.h>
#include <tasks.h>
#include <ss_types.h>
#include <flags.h>
#include "../guild.h"

/*
 * Function:    config_teleport_spell
 * Description: Config function for teleport spells. Redefine this in your
 *              own teleport spells to override the defaults.
 * Arguments:   Same as config_spell
 * Returns:     Same as config spell
 */
public void
config_teleport_spell()
{
    set_spell_name("sanctuary");
    set_spell_desc(" - Move yourself back to your sanctuary");

    set_ability_stats(STAT_WEIGHTING);
    set_spell_class(SPELL_CLASS_3);
    set_spell_task(TASK_HARD);   
 
    set_spell_element(SS_ELEMENT_AIR, 0);
    set_spell_form(SS_FORM_CONJURATION, 0);
    
    // This is a teleport home - does not require the 2 hour
    // delay for targeted teleport to named destinations.
    set_next_teleport_delay(DEFAULT_TELEPORT_TO_HOME_DELAY);
    
    set_spell_time_factor(3.0); 
}


/*
 * Function name: spell_target_teleport
 * Description:   This is the default targetting functions for the teleport
 *                spell. The spell should return list with a single object.
 *                The object should be the target room. 
 */
public object *
spell_target_teleport(object caster, string str)
{
   string arg;
   
   object env = environment(caster);
   
   string target_room_file;
   
   setuid();
   seteuid(getuid());
   
   target_room_file = "/d/Faerun/guilds/vampires/rooms/coffin";
   object target_room = safely_load_master_file(target_room_file);
   
   return ({ target_room, caster });
}


/*
 * Function:    query_teleport_ingredients
 * Description: This function defines what components are required for
 *              this teleport spell.
 */
public string *
query_teleport_ingredients(object caster)
{
    return ({  });
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
    
    if (player->query_guild_name_lay() == "Vampires of Faerun")
    {
        return 1;
    }
    
    return 0;
}


public int
check_valid_action(object caster, mixed * targets, string arg, 
int execute = 0)
{
    int bloodamount2 = VAMPIRES_MAPPINGS->query_thirst_gauge(caster->query_real_name());     
    
    if (!::check_valid_action(caster, targets, arg, execute))
    {
        return 0;
    }
    
    if (bloodamount2 < SANCTUARY_COST)
    {
        write("The saturation of your blood is too low. You must feed more!\n");
        return 0;        
    }
    
    if (caster->query_ethereal() == 1)
    {
        caster->catch_tell("You are in the ethereal realm. This spell "
        +"doesn't work there.\n");
        
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
    string caster_message, watcher_message;
    
    // Blood-drain
    int bloodamount = VAMPIRES_MAPPINGS->query_thirst_gauge(caster->query_real_name());     
    
    
    
    bloodamount = bloodamount - SANCTUARY_COST;   
    
    if (bloodamount < 1)
    {
        bloodamount = 1;
    }
    
    VAMPIRES_MAPPINGS->set_thirst_gauge(caster->query_name(), bloodamount);

    caster_message = "You concentrate on the powers of the blood!\n";
    
    watcher_message = QCTNAME(caster)
    +" concentrates on something.\n";

    caster->catch_tell(caster_message);
    tell_room(environment(caster), watcher_message, ({ caster }), caster);

    setuid();
    seteuid(getuid());
}




/*
 * Function:    hook_cannot_teleport_caster_in_combat
 * Description: Hook that gets called when trying to teleport while in combat
 *              This can get called both at the beginning and at the end of
 *              the spell casting. The "execute" variable determines whether
 *              it's all the beginning or the end.
 */
public void
hook_cannot_teleport_caster_in_combat(object caster, mixed * targets, string
arg, int execute)
{
    if (!execute)
    {
        caster->catch_tell("You cannot cast Sanctuary while you are in combat.\n");
    }
    else
    {
        caster->catch_tell("You lose concentration of your spell as you are "
        + "distracted by combat.\n");
    } 
}


/*
 * Function:    hook_cannot_teleport_caster_room_not_valid
 * Description: Hook that gets called when the caster's current room is not
valid. It
 *              can be valid for a number of reasons. See check_valid_action
for the
 *              conditions checked.
 */
public void
hook_cannot_teleport_caster_room_not_valid(object caster, mixed * targets,
string arg, int execute,
object caster_room)
{
    caster->catch_tell("The room you are in prevents you from "
    +"casting Sanctuary.\n");
}


/*
 * Function:    hook_cannot_teleport_target_room_not_valid
 * Description: Hook that gets called when the spell's target room is not
valid. It
 *              can be valid for a number of reasons. See check_valid_action
for the
 *              conditions checked.
 */
public void
hook_cannot_teleport_target_room_not_valid(object caster, mixed * targets,
string arg, int execute,
object target_room)
{
    caster->catch_tell("The room you want to reach prevents you "
    +"from casting Sanctuary there.\n");
}


/*
 * Function:    hook_cannot_teleport_same_room
 * Description: Hook that gets called when the user is trying to teleport to
the same
 *              room that they are already in.
 */
public void             
hook_cannot_teleport_same_room(object caster, mixed * targets, 
string arg, int execute)
{
    caster->catch_tell("There's no need to cast Sanctuary. You're already "
    +"there!\n");
}










/* NEW
 * Function:    hook_cannot_teleport_target_not_relaxed
 * Description: Hook that gets called when trying to teleport while in combat
 *              This can get called both at the beginning and at the end of
 *              the spell casting. The "execute" variable determines whether
 *              it's all the beginning or the end.
 */

public void
hook_cannot_teleport_target_not_relaxed(object caster, object target, string arg, int execute)
{
    if (!execute)
    {
        caster->catch_tell("You cannot cast Sanctuary while you are in combat.\n");
    }
    else
    {
        caster->catch_tell("You lose concentration of your spell as you are "
        + "distracted by combat.\n");
    } 
}


/* 
 * Function:    hook_cannot_teleport_target_too_soon
 * Description: Hook that gets called when trying to teleport while having
 *              recently been in combat.
 *              This can get called both at the beginning and at the end of
 *              the spell casting. The "execute" variable determines whether
 *              it's all the beginning or the end.
 */
public void
hook_cannot_teleport_target_too_soon(object caster, mixed * targets, 
string arg, int execute)
{
    caster->catch_tell("You have teleported too recently. You have to "
    + "wait before you can cast Sanctuary.\n");
}


/*
 * Function:    hook_describe_teleport_origin_room
 * Description: This is the hook that describes the action of caster
 *              successfully teleporting out of the origin room.
 */
public void
hook_describe_teleport_origin_room(object caster, mixed* targets, object target_room)
{
    // This is a self teleport, so targets contains only the caster.
    caster->catch_tell("You poof into mist, and travels back to "
    +"your sanctuary!!\nYou feel a slight drain in the saturation in your blood.\n");

    tell_room(target_room, QCTPNAME(caster) 
    + " suddenly poofs into mist and dissipates from view!\n", targets );
}


/*
 * Function:    hook_describe_teleport_target_room
 * Description: This is the hook that describes the action of caster
 *              successfully teleporting into the target room.
 */
public void
hook_describe_teleport_target_room(object caster, mixed* targets, object target_room)
{
    // This is a self teleport, so targets contains only the caster.
    tell_room(target_room, QCTNAME(caster) + " suddenly " 
    +"appears out of nowhere!\n",  targets ); 
}