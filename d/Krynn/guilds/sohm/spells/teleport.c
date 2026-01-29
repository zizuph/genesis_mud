/*
 * Teleport for School of High Magic
 *
 * Coded by Arman 2016.
 * 
 */
 
#pragma strict_types

#include <macros.h>
#include <files.h>
#include <tasks.h>
#include <ss_types.h>
#include <flags.h>
#include "defs.h"
#include "/d/Krynn/common/defs.h"

#include "/d/Genesis/specials/local.h"
inherit SPELL_DIR + "teleport";

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
    set_spell_name("arcanossalur");
    set_spell_desc("Teleport - magically transport to another location");

    set_spell_class(SPELL_CLASS_4);
    set_spell_task(TASK_HARD);  

    set_ability_stats(STAT_WEIGHTING);
  
    set_spell_element(SS_ELEMENT_AIR, 50);
    set_spell_form(SS_FORM_CONJURATION, 60);

    // 2.0 times the standard cast time for a teleport spell 
    set_spell_time_factor(2.0); 
    
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

   string  target_room_file;
   mapping locations = SOHM_MANAGER->query_teleport_locations(caster);

   if (!stringp(str))
   {
        caster->catch_tell("Where do you wish to teleport to?\n");
        return ({ });
   }


   if(parse_command(str, env, "[to] %s", arg))
   {
      if (member_array(lower_case(arg), m_indexes(locations)) < 0)
      {
          write("You haven't set a location to teleport to by that name.\n");
          return ({ });
      }
   }

   setuid();
   seteuid(getuid());

   target_room_file = locations[lower_case(arg)];
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
    return ({ "breadroot", "pearl" });
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
    return SOHM_MANAGER->query_memorised_spell(player,"arcanossalur_memorised");
}

public int 
check_valid_action(object caster, mixed * targets, string arg, int execute = 0)
{
    if (!::check_valid_action(caster, targets, arg, execute))
    {
        return 0;
    }

    if(SOHM_MANAGER->too_many_spells_memorised(caster))
    {
        caster->catch_tell("You have more spells memorised than you are capable of " +
            "mentally handling. You need to balance your memorised spell list before " +
            "you can cast spells again.\n");
        return 0;
    }

    if(caster->query_prop("_sohm_teleport_timer"))
    {
        int timer = caster->query_prop("_sohm_teleport_timer");

        caster->catch_tell("You cannot cast another teleport spell " +
           "for another " +timer+ " minutes.\n");
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

        caster_message = "You close your eyes and whisper the words of magic " +
           "'arcan ossalur' as you prepare to teleport yourself across " +
           "the realms.\n";
        watcher_message = QCTNAME(caster)+" closes "+caster->query_possessive()+ 
           " eyes and whispers words of magic.\n";
        
    caster->catch_tell(caster_message);
    tell_room(environment(caster), watcher_message, ({ caster }), caster);
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
        caster->catch_tell("You cannot teleport while you are in combat.\n");
    }
    else
    {
        caster->catch_tell("You lose concentration of your spell as you are "
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
        + "relax first before you can teleport.\n");
}

/*
 * Function:    hook_cannot_teleport_target_too_soon
 * Description: Hook that gets called when trying to teleport while having
 *              recently teleported.
 *              This can get called both at the beginning and at the end of
 *              the spell casting. The "execute" variable determines whether
 *              it's all the beginning or the end.
 */
public void
hook_cannot_teleport_target_too_soon(object caster, object target, string arg, int execute)
{
    caster->catch_tell("You have too recently teleported. You have to "
        + "wait before you can teleport again.\n");
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
    caster->catch_tell("The room you are in prevents you from teleporting.\n");
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
    caster->catch_tell("The room you want to reach prevents you from teleporting there.\n");
}
 
/*
 * Function:    hook_cannot_teleport_same_room
 * Description: Hook that gets called when the user is trying to teleport to the same
 *              room that they are already in.
 */
public void             
hook_cannot_teleport_same_room(object caster, mixed * targets, string arg, int execute)
{
    caster->catch_tell("There's no need to teleport. You're already there!\n");
}

/*
 * Function:    hook_describe_teleport_origin_room
 * Description: This is the hook that describes the action of caster
 *              successfully teleporting out of the origin room.
 */
public void
hook_describe_teleport_origin_room(object caster, mixed* targets, object origin_room) 
{
    caster->catch_tell("Your eyes snap open as you complete the spell "
        + "and teleport away.\n");
    tell_room(origin_room, QCTPNAME(caster) + " eyes snap open. "
        +capitalize(HE(caster))+ " shimmers briefly and vanishes.\n", 
        ({ caster }) );
}

/*
 * Function:    hook_describe_teleport_target_room
 * Description: This is the hook that describes the action of caster
 *              successfully teleporting into the target room.
 */
public void
hook_describe_teleport_target_room(object caster, mixed* targets, object target_room)
{
    int arcane_skill = caster->query_skill(SOHM_GUILD_SKILL);

    /*
      While there is a global teleport delay, we will not apply this WoHS timer.
    
    if(arcane_skill < 90)
    {
       int timer = max(1, 90 - arcane_skill);
       object teleport_timer = clone_object(SOHM_SPELL_OBJS + "teleport_timer");

       caster->add_prop("_sohm_teleport_timer", timer);

       setuid();
       seteuid(getuid());
       
       teleport_timer->set_teleport_timer(caster, timer);
       teleport_timer->move(caster, 1);
    }
    */

    tell_room(target_room, QCTNAME(caster) + " appears suddenly " +
          "out of thin air.\n",  ({ caster }) ); 
}