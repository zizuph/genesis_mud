/* 
 * pmirage (blink) object for PoT - Arman
 */

#pragma strict_types
#pragma save_binary

#include "/d/Ansalon/common/defs.h"
#include "../../guild.h"
#include <stdproperties.h>
#include <macros.h>
#include <wa_types.h>
#include <ss_types.h>
#include <tasks.h>
#include <composite.h>

inherit "/d/Genesis/specials/std/spells/obj/blink_obj";

/*
 * Function:    create_spell_object
 * Description: Override this to customize properties for the spell object
 */
public void 
create_spell_object()
{
    set_name("_pot_pmirage_object_");
    set_short("pmirage spell object");    
    set_long("This is the standard pmirage spell's object. It provides " +
         "an aura that causes enemies to be distracted and let the " +
         "caster fall behind a friendly team member.\n");
    add_prop(OBJ_S_WIZINFO, "This is a spell object " +
                            "created by the pmirage spell.\n");
    set_spell_effect_desc("aura of temptation");
    
    set_dispel_time(1800);   
}

/* 
 * Function:     is_valid_blink_target
 * Description:  Should return whether the person is a teammate and
 *               they're currently present and available to be blinked
 *               behind.
 * Arguments:    object teammate    -  the teammate to blink behind
 *               object player      -  the person blinking
 * Returns:      1 if player can blink behind teammate, 0 otherwise
 */ 
public int
is_valid_blink_target(object teammate, object player)
{
    if (!objectp(player) || !objectp(teammate))
    {
        return 0;
    }
    // Condition: Check that the teammate is in player's team.
    object * teammates = player->query_team_others();
    if (!pointerp(teammates)
        || sizeof(teammates) == 0
        || !IN_ARRAY(teammate, teammates))
    {
        return 0;
    }
    // Condition: Check that the teammate is actually in the same
    //            room.
    if (environment(teammate) != environment(player))
    {
        return 0;
    }

    // When not aspected to the Dark Lady, you can only blink
    // behind Dragonarmy or Templar members.
    if(!player->query_prop(DARK_LADY_ASPECT))
    {
       if(teammate->query_guild_member("Dragonarmy") ||
          teammate->query_guild_member("Templars of Takhisis"))
       {
         return 1;
       }
       
       return 0;
     } 
    
    return 1;
}    

/*
 * Function:    hook_spell_effect_started
 * Description: Override this to customize the message when this spell effect
 *              is added to th target.
 */
public void
hook_spell_effect_started()
{
    object target = query_effect_target();
    if (objectp(target))
    {
        target->catch_tell("The Dark Queen blesses you with an aura radiating " +
            "the gifts of the Temptress, distracting your foes with delusions " +
            "of grandeur and primal lusts.\n");
        tell_room(environment(target), QCTNAME(target) + " radiates an aura " +
            "that distracts your senses, filling your mind with images of " +
            "of grandeur, temptation, and primal lusts.\n", ({ target }));
    }    
}

/*
 * Function:    hook_spell_effect_ended
 * Description: Override this to customize the message when this spell effect
 *              is dispelled.
 */
public void
hook_spell_effect_ended()
{
    object target = query_effect_target();

    if(target->query_ghost())
        return;

    if (objectp(target))
    {
        target->catch_tell("Your aura of temptation dissipates.\n");
        tell_room(environment(target), QCTNAME(target) + " no longer "
            + "radiates an aura of temptation.\n", ({ target }));
    }
}

/*
 * Function:    query_blink_subloc_description
 * Description: When someone examines a person with this spell effect,
 *              they will see whatever is returned by this function.
 */
public string
query_blink_subloc_description(object on, object for_obj)
{
    if (for_obj == on)
        return  "You are surrounded by the blessings of the Temptress, providing " +
                "a distracting aura of delusions and primal lusts.\n";
    else
        return capitalize(on->query_pronoun()) + " is surrounded by an aura that " +
            "distracts your senses, filling your mind with images of " +
            "temptation and primal lusts.\n";
}

/*
 * Function:    hook_describe_blink_action
 * Description: When someone successfully blinks behind someone else,
 *              they will see the messages described in this function.
 * Arguments:   object player    - the person who is blinking
 *              object friend    - the person who is going to be tanking
 *              object * enemies - the list of enemies that will attack the
 *                                 friend instead.
 */
public void
hook_describe_blink_action(object player, object friend, object * enemies)
{
    player->catch_msg("Delusions of grandeur and lustful images distract your " +
                      "foes momentarily, allowing you to step behind "
                      + QTNAME(friend) + ". Your enemies are forced "
                      + "to engage " + friend->query_objective()+ "!\n");
    enemies->catch_msg("Your mind is suddenly filled with dark images of " +
                     "conquest and carnal desires dredged from the darkest " +
                     "parts of your soul! " + QCTNAME(player) + " takes " +
                     "advantage of your momentary distraction, moving from " +
                     "the fore of the battle behind " +QTNAME(friend)+ ".\n");
    friend->catch_msg("Images of conquest and carnal desires dredged from " +
                     "the darkest corners of the mind distract " +
                     COMPOSITE_LIVE(enemies)+ ", allowing " +QTNAME(player)+
                     " to step out of the fore of the battle behind you!\n");
                          
    tell_room(environment(player), "Images of conquest and carnal desires " +
                     "dredged from the darkest corners of the mind distract " +
                     COMPOSITE_LIVE(enemies)+ ", allowing " +QTNAME(player)+
                     " to step out of the fore of the battle behind " +
                     QTNAME(friend)+ ".\n", ({ player, friend, enemies }) );
}

public void
hook_describe_blink_no_attack_room(object player, object friend, object * enemies)
{
}

/*
 * Function:    hook_spell_effect_warn_fading
 * Description: Override this to customize the message for when
 *              the effect has only a minute left.
 */
public void
hook_spell_effect_warn_fading()
{
    object target = query_effect_target();
    
    if (objectp(target))
    {
        target->catch_tell("You sense your aura of temptation starting to dissipate.\n");
    }
}
/* 
 * Function:    hook_spell_effect_not_maintained
 * Description: Override this to describe the effect when the caster
 *              cannot maintain the effect.
 */
public void
hook_spell_effect_not_maintained()
{
    object caster = query_effect_caster();
    
    if (objectp(caster))
    {
        caster->catch_tell("You are mentally unable to maintain "
            + "your aura of temptation.\n");
    }    
}