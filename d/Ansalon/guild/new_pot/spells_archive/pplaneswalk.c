/*
 * pTeleport
 *
 * updated by Arman October 2016
 */

#pragma strict_types

#include "/d/Ansalon/common/defs.h"
#include <macros.h>
#include <tasks.h> 
#include <filter_funs.h>
#include <stdproperties.h>
#include <ss_types.h>
#include <composite.h>
#include <wa_types.h>

#include "../guild.h"
#include "../spells.h"

inherit "/d/Genesis/specials/std/spells/teleport";
inherit GUILDDIRSPELL + "common";

#define PP_DEBUG(x)	find_player("arman")->catch_tell("#pot_teleport# " + (x) + "\n")
#define POT_TELEPORT_DESTINATION "_pot_teleport_destination_prop"
 
/*
 * Function name:   safely_load_master_file
 * Description:     This safely loads the master file if it hasn't already
 *                  been loaded. Otherwise, it just returns the existing
 *                  master file. If the file is not loadable, then it
 *                  simply returns 0
 * Argument:        (string) filename - Filename of the file to load
 * Returns:         (object) : Loaded master file
 */
public object
safely_load_master_file(string filename)
{
    object master_obj;
    if (!objectp(master_obj = find_object(filename)))
    {
        LOAD_ERR(filename);
        master_obj = find_object(filename);
    }
    
    return master_obj;
} /* safely_load_master_file */

/* Function name: query_spell_level
 * Description:   Internally used by the standing system
 * Returns:       int - the spell level
 */
int
query_spell_level()
{
    return 13;
}

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

    set_spell_name("pplaneswalk");
    set_spell_desc("Step into another plane to speed up travel");

    set_spell_element(SS_ELEMENT_LIFE, 45);
    set_spell_form(SS_FORM_DIVINATION, 30);
    set_spell_task(TASK_ROUTINE);

    // Can teleport to the Abyss from darkness
    set_spell_visual(0);
   
}

/*
 * Function name: concentrate_msg
 * Description:   Give messages indicating that spell concentration has begun
 * Arguments:     1. (object)   The caster
 *                2. (mixed *)  The targets
 *                3. (string)   The arguments passed to the "cast" command
 */

public void
concentrate_msg(object caster, mixed *targets, string arg)
{
    caster->catch_tell("You clutch your black medallion and " +
	"pray to the Queen of Darkness.\n");

    tell_room(environment(caster), QCTNAME(caster) + " clutches " +
	caster->query_possessive() + " medallion and prays to the "+
	"Queen of Darkness.\n", ({ caster }), caster);
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
    string  arg, room;
    object  abyss_room, dest_room, env = environment(caster);
    string  target_room_file = GUILDDIRSPELL + "obj/abyss";

   if (!stringp(str))
   {
        caster->catch_tell("Where do you wish to planeswalk to?\n");
        return ({ });
   }

   if(parse_command(str, env, "[to] %s", arg))
   {
        // PP_DEBUG("cast to move");

        room = GUILD_ADMIN->query_planeswalk_loc(caster->query_real_name(),
            lower_case(arg));

        if (!room)
        {
            write("You haven't set a location to planeswalk to by that name.\n");
            return ({ });
        }
    }

    setuid();
    seteuid(getuid());
    
    if (!objectp(dest_room = safely_load_master_file(room)) ||
        !objectp(abyss_room = safely_load_master_file(target_room_file)))
        return ({});
    
    abyss_room->set_planeswalk_loc(caster, dest_room);

    //PP_DEBUG("cloned Abyss");
    caster->add_prop(POT_TELEPORT_DESTINATION, room);
    return ({ abyss_room });
}

/*
 * Function:    query_teleport_ingredients
 * Description: This function defines what components are required for
 *              this teleport spell.
 */
public string *
query_teleport_ingredients(object caster)
{
    return ({ "amanita", "elidross" });
}
 
/*
 * Function:    check_valid_action
 * Description: Checks conditions to see whether this spell can be cast.
 */
public int 
check_valid_action(object caster, mixed * targets, string arg, int execute)
{
    int result = ::check_valid_action(caster, targets, arg, execute);
    if (!result)
    {
        return result;
    }
    
    // Players cannot teleport if any of the following conditions are true
    // 1. Player is currently in combat (query_attack)
    // 2. Player was recently in combat (query_relaxed_from_combat)
    // 3. The target room is invalid
    // 4. Caster or target room is not a teleport room (ROOM_M_NO_TELEPORT)
    // 5. Caster room is not a teleport from room (ROOM_M_NO_TELEPORT_FROM)
    // 6. Target room is not a teleport to room (ROOM_M_NO_TELEPORT_TO)
    // 7. Caster or target room has a no-magic prop set (OBJ_I_NO_MAGIC)
    if (objectp(caster->query_attack()))
    {
        hook_cannot_teleport_caster_in_combat(caster, targets, arg, execute);
        return 0;
    }
    if(!caster->query_relaxed_from_combat())
    {
        hook_cannot_teleport_caster_not_relaxed(caster, targets, arg, execute);
        return 0;   
    }
    
    object target_room;   
    if (!sizeof(targets) 
        || !objectp(target_room = targets[0])
        || target_room->query_prop(ROOM_M_NO_TELEPORT) 
        || target_room->query_prop(ROOM_M_NO_TELEPORT_TO)
        || target_room->query_prop(OBJ_I_NO_MAGIC))
    {
        hook_cannot_teleport_target_room_not_valid(caster, targets, arg, execute, target_room);
        return 0;
    }
    object caster_room = environment(caster);
    if (objectp(caster_room)
        && (caster_room->query_prop(ROOM_M_NO_TELEPORT)
           || caster_room->query_prop(ROOM_M_NO_TELEPORT_FROM)
           || caster_room->query_prop(OBJ_I_NO_MAGIC)))
    {
        hook_cannot_teleport_caster_room_not_valid(caster, targets, arg, execute, caster_room);
        return 0;
    }
    if (target_room == caster_room)
    {
        hook_cannot_teleport_same_room(caster, targets, arg, execute); 
        return 0;
    }

    // harder to cast on when in poor standings
    if (caster->query_skill(PS_STANDING) < -900)
	set_spell_task(TASK_FORMIDABLE);
    else if (caster->query_skill(PS_STANDING) < -300) 
	set_spell_task(TASK_HARD);
    
    return result;    
}

/*
 * Function:    hook_cannot_teleport_caster_in_combat
 * Description: Hook that gets called when trying to teleport while in combat.
 *              This can get called both at the beginning and at the end of
 *              the spell casting. The "execute" variable determines whether
 *              it's all the beginning or the end.
 */
public void
hook_cannot_teleport_caster_in_combat(object caster, mixed * targets, string arg, int execute)
{
    if (!execute)
    {
        caster->catch_tell("You cannot planewalk while you are in combat.\n");
    }
    else
    {
        caster->catch_tell("You lose your concentration of your prayer as you are "
            + "distracted by combat.\n");
    } 
}
/*
 * Function:    hook_cannot_teleport_caster_not_relaxed
 * Description: Hook that gets called when trying to teleport while having
 *              recently been in combat.
 *              This can get called both at the beginning and at the end of
 *              the spell casting. The "execute" variable determines whether
 *              it's all the beginning or the end.
 */
public void
hook_cannot_teleport_caster_not_relaxed(object caster, mixed * targets, string arg, int execute)
{
    caster->catch_tell("You have too recently been in combat. You have to "
        + "relax first before you can planeswalk.\n");
}

/*
 * Function:    hook_cannot_teleport_caster_room_not_valid
 * Description: Hook that gets called when the caster's current room is not valid. It
 *              can be valid for a number of reasons. See check_valid_action for the
 *              conditions checked.
 */
public void
hook_cannot_teleport_caster_room_not_valid(object caster, mixed * targets, string arg, int execute,
object caster_room)
{
    caster->catch_tell("There is no way to open a portal to another plane from here.\n");
}

/*
 * Function:    hook_cannot_teleport_target_room_not_valid
 * Description: Hook that gets called when the spell's target room is not valid. It
 *              can be valid for a number of reasons. See check_valid_action for the
 *              conditions checked.
 */
public void
hook_cannot_teleport_target_room_not_valid(object caster, mixed * targets, string arg, int execute,
object target_room)
{
    caster->catch_tell("The room you want to reach prevents you from planeswalking there.\n");
}
 
/*
 * Function:    hook_cannot_teleport_same_room
 * Description: Hook that gets called when the user is trying to teleport to the same
 *              room that they are already in.
 */
public void             
hook_cannot_teleport_same_room(object caster, mixed * targets, string arg, int execute)
{
    caster->catch_tell("There's no need to planewalk. You're already there!\n");
}

/*
 * Function:    hook_describe_teleport_origin_room
 * Description: This is the hook that describes the action of caster
 *              successfully teleporting out of the origin room.
 */
public void
hook_describe_teleport_origin_room(object caster, object origin_room)
{
    caster->catch_tell("You trace a doorway before you, whisper a " +
            "prayer and summon a portal which you step through. Suddenly " +
            "you find yourself in a strange place.\n");
    tell_room(origin_room, QCTNAME(caster) + " traces a " +
            "shape before " + HIM(caster) + " resembling a doorway. " +
            "A dark portal opens, and then snaps shut into nothingness " +
            "as " +HE(caster)+ " steps through.\n", ({ caster }) );
}

/*
 * Function:    hook_describe_teleport_target_room
 * Description: This is the hook that describes the action of caster
 *              successfully teleporting into the target room.
 */
public void
hook_describe_teleport_target_room(object caster, object target_room)
{
    tell_room(target_room, QCTNAME(caster) + " steps through a dark " +
            "portal into the Abyss.\n",  ({ caster }) );
}

public int
is_valid_medallion(object caster, object obj)
{
    if (!objectp(obj) || !obj->id(MEDALLION_ID))
    {
        return 0;
    }
    
    return 1;
}

/*
 * Function name: query_casting_success
 * Description:   Determine if a spell is successfully cast
 * Returns:       The result as an integer indicating success or
 *                failure (0 indicating failure, positive integer
 *                indicating % success)
 */
static int
query_casting_success(object caster)
{
    object * med = filter(all_inventory(TP), &is_valid_medallion(caster,));

    int ret = ::query_casting_success(caster);

    /* If we don't wear the medallion, there is only a 10% chance
     * the spell will actually go through
     */
    if(!med[0]->query_worn())
    {
        caster->adjust_standing(RND_RANGE(-200, 50));
        if (random(10))
            return 0;
    }
    if (ret)
        caster->adjust_standing(random(8) ?
            RND_RANGE(TO->query_spell_level() * 3, 10) : RND_RANGE(-10, 10));
    else
        caster->adjust_standing(RND_RANGE(-5, 5));
        
    return ret;
}