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

#include "/d/Genesis/specials/local.h"
inherit SPELL_DIR + "teleport";
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

    set_ability_stats(STAT_WEIGHTING);

    set_spell_class(SPELL_CLASS_4);
    set_spell_task(TASK_HARD);

    ::config_teleport_spell();

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

    room = NTEMPLE + "lvl2/dorm";

    if(str && parse_command(str, env, "[to] %s", arg))
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
    return ({ abyss_room, caster});
}

// If teleporting home, avoid the targeted location penalty.
int get_next_teleport_delay(object caster, object destination)
{
    if (!destination)
    {
        return ::get_next_teleport_delay(caster, destination);
    }
    string true_destination = caster->query_prop(POT_TELEPORT_DESTINATION);   
    if (true_destination == (NTEMPLE + "lvl2/dorm"))
    {
        return DEFAULT_TELEPORT_TO_HOME_DELAY;
    }
    return ::get_next_teleport_delay(caster, destination);
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
hook_cannot_teleport_target_not_relaxed(object caster, object target, string arg, int execute)
{
    caster->catch_tell("You have too recently been in combat. You have to "
        + "relax first before you can planeswalk.\n");
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
hook_cannot_teleport_target_too_soon(object caster, object target, string arg, int execute)
{
    caster->catch_tell("You have too recently teleported. You have to "
        + "wait before you can planeswalk.\n");
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
hook_describe_teleport_origin_room(object caster, mixed* targets, object origin_room)
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
hook_describe_teleport_target_room(object caster, mixed* targets, object target_room)
{
    tell_room(target_room, QCTNAME(caster) + " steps through a dark " +
            "portal into the Abyss.\n",  ({ caster }) );
}

/*
 * Function:    resolve_teleport_spell
 * Description: Called at the beginning of resolve_spell in order to perform
 *              spell specific actions.
 * Arguments:   Same as resolve_spell
 */
public void
resolve_teleport_spell(object caster, mixed * targets, int * resist, int result)
{
    if (result)
        caster->adjust_standing(random(8) ?
            RND_RANGE(TO->query_spell_level() * 3, 10) : RND_RANGE(-10, 10));
    else
        caster->adjust_standing(RND_RANGE(-5, 5));
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
 * Function name:   query_ability_hit
 * Description:     Returns the set ability to-hit value.
 * Arguments:       (object) actor
 *                  (mixed) target
 *                  (object *) items
 * Returns:         (int) ability hit value
 */
public int
query_ability_hit(object actor, mixed target, object * items)
{
    if (calling_function() == "query_spell_tohit")
    {
        // harder to cast on when in poor standings
        if (actor->query_skill(PS_STANDING) < -900)
            return convert_task_to_hit(TASK_FORMIDABLE);
    
        if (actor->query_skill(PS_STANDING) < -300) 
            return convert_task_to_hit(TASK_HARD);
    }
    
    return ::query_ability_hit(actor, target, items);
} /* query_ability_hit */

/*
 * Function name: check_required_items
 * Description  : Does some validation to make sure the actor has
 *                all the equipment they need to perform the special.
 * Returns      : items that are required, or 0 if a required item is
 *                missing.
 */
static mixed *
check_required_items(object actor, mixed * targets,string arg, int pretest)
{
    return filter(actor->query_clothing(-1), &is_valid_medallion(actor,));
}

/*
 * Function:    query_spell_power
 * Description: A generic power calculation function that takes into
 *              account skills, stats, and guild strength
 */
public int
query_spell_power()
{
    mixed *items = check_required_items(this_player(), ({}), "", 0);
    return max(1, query_ability_power(this_player(), ({}), items));
}

/*
 * Function name:   query_ability_item_modifier
 * Description:     
 * Arguments:       1. (object) actor
 *                  2. (mixed *) items - The items used with the ability
 * Returns:         (int) 
 */
public int
query_ability_item_modifier(object caster, mixed *items)
{
    items = filter(items, &is_valid_medallion(caster,));
    
    /* If we don't wear the medallion, there is only a 10% chance
     * the spell will actually go through
     */
    if(!sizeof(items))
    {
        caster->adjust_standing(RND_RANGE(-200, 50));
        if (random(10))
            return 0;
    }
    
    return 100;
} /* query_ability_item_modifier */