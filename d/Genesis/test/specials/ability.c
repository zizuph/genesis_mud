#pragma strict_types

#include "defs.h"

inherit HOOKS_LIB;
inherit TARGETTING_LIB;

#include <stdproperties.h>
#include <ss_types.h>
#include <comb_mag.h>
#include <macros.h>
#include <formulas.h>

#define LIVE_O_ACTION            "_live_o_action_"
#define LIVE_O_ACTION_ENV        "_live_o_action_env_"

static string
     Ability_name;          /* The name of the special */

static int 
     Ability_exp_factor,    /* The general exp factor for this */
     Ability_time,          /* The time it takes to prepare */
     Ability_offensive,     /* True if it is combat initiating */
     Ability_stationary,    /* If the ability requires standing still */
     Ability_no_stun,       /* If the ability cannot be done stunned */
     Ability_no_reveal,     /* True if the ability should not reveal the 
                                caster if hidden */
     Ability_vocal,
     Ability_visual,
     Ability_peaceful,
     Ability_confirm_attack;
     
static mixed
     Ability_fail;          /* The message given if the ability fails */

static function
     Ability_resist,            /* The resistance function */
     Ability_target,            /* The targeting function */
     Ability_target_verify;     /* Verify target function */


static void resolve_ability(object actor, mixed * items,
            mixed * targets, int *resist, mixed *results);

public varargs int config_ability(object caster, object * targets, 
                    string arg);


static mixed * check_required_items(object actor,mixed * targets,
                    string arg,int pretest);
static void restore_required_items(mixed * items);


/* 
 * Function name: short
 * Description:   Provides a short name for the ability which can be used
 *                in various messages
 */
public string short()
{
    return Ability_name;
}

/*
 * Function name: set_ability_time
 * Description:   Set the time it takes to prepare the ability
 * Arguments:     1. (int) The time it should take in seconds
 */
public void
set_ability_time(int time)
{
    Ability_time = time;
}

public int
query_ability_time()
{
    return Ability_time;
}

/*
 * Function name: set_ability_offensive
 * Description:   Designate the spell as being offensive (one initiating
 *                combat)
 * Arguments:     1. (int) True if the ability is offensive
 */
public void
set_ability_offensive(int offensive)
{
    Ability_offensive = offensive;
}

/*
 * Function name: set_ability_stationary
 * Description:   Designate the spell as being stationary (caster may not
 *                move while concentrating).
 * Arguments:     1. (int) True if ability is stationary
 */
public void
set_ability_stationary(int i)
{
    Ability_stationary = i;
}

/*
 * Function name: set_ability_no_stun
 * Description:   Designate the spell as blocked when stunned
 * Arguments:     1. (int) True if ability is blocked when stunned
 */
public void
set_ability_no_stun(int i)
{
    Ability_no_stun = i;
}


/*
 * Function name: set_ability_fail
 * Description:   Designate a special message to be used when the 
 *                ability fails.
 * Arguments:     1. (function) A function which can be called to obtain 
                                the failure message.
 *                   (string)   A static failure message.
 */
public void
set_ability_fail(mixed fail)
{
    Ability_fail = fail;
}

/*
 * Function name: query_ability_fail
 * Description:   Get a special message to be used when the 
 *                ability fails.
 * Arguments:     1. (function) A function which can be called to obtain 
                                the failure message.
 *                   (string)   A static failure message.
 */
public void
query_ability_fail()
{
    return Ability_fail;
}


/* 
 * Function name: set_ability_no_reveal
 * Description:   Indicate that using the ability will reveal the actor
 * Arguments:     1. (int) If true, don't reveal the actor.
 */
public void
set_ability_no_reveal(int i)
{
    Ability_no_reveal = i;
}

/*
 * Function name: query_ability_no_reveal
 * Description:   Returns a true value if the spell reveals the actor upon
 *                casting.
 * Returns:       true/false, indicating whether the actor is not revealed
 */
public int
query_ability_no_reveal()
{
    return Ability_no_reveal;
}

/* 
 * Function name: set_ability_no_reveal
 * Description:   Indicate that using the ability will ask to confirm
 *                before working on another met player
 * Arguments:     1. (int) If true, ask the player to confirm
 */
public void
set_ability_confirm_attack(int i)
{
    Ability_confirm_attack = i;
}

/*
 * Function name: query_ability_confirm_attack
 * Description:   Returns a true value if the ability will ask the actor
 *                before using the ability on a met person
 * Returns:       true/false, indicating whether the actor is asked
 */
public int
query_ability_confirm_attack()
{
    return Ability_confirm_attack;
}


/* 
 * Function name: set_ability_vocal
 * Description:   Indicate that the spell requires the caster to use his
 *                voice.  Such abilities are not possible when the
 *                LIVE_M_MOUTH_BLOCKED property is true.
 * Arguments:     1. (int) If true, ability requires voice.
 * 
 * TODO:          Classify vocal spells as ACTION_AURAL.
 */
public void
set_ability_vocal(int i)
{
    Ability_vocal = i;
}

/*
 * Function name: set_spell_visual
 * Description:   Indicate that the spell requires the caster to be able to
 *                see in his environment and to see the target, if there is
 *                one.
 * Arguments:     1. (int) If true, spell requires caster to see.
 */
public void
set_ability_visual(int i)
{
    Ability_visual = i;
}

/*
 * Function name: set_ability_peaceful
 * Description:   Indicate that the ability cannot be used in combat.
 * Arguments:     1. (int) If true, abilitycannot be used in combat.
 */
public void
set_ability_peaceful(int i)
{
    Ability_peaceful = i;
}

/* 
 * Function name: set_ability_name
 * Description:   Designate a name for the ability.  This will be used as 
 *                an argument to the "cast" command to cast this spell.
 * Arguments:     1. (string) The name of the spell.  Do not include spaces.
 */
public void
set_ability_name(string name)
{
    Ability_name = name;
}

public string query_ability_name()
{
    return Ability_name;
}

/*
 * Function name: set_ability_resist
 * Description:   Set the function to use to get a target's resistance in %.
 * Arguments:     1. (function) - The function to be used
 */
public void
set_ability_resist(function res)
{
    Ability_resist = res; 
}


/*
 * Function name: set_ability_target
 * Description:   Indicate which function to use to determine the ability's
 *                target. This function should be of the form
 *
 *                     object *func(object, string)
 *
 *                where the first argument is the actor, and the second is
 *                the string argument passed to the command.  The
 *                function returns an array of targets, empty if none were
 *                found.
 *
 * Arguments:     1. (function) The targeting function
 */
public void
set_ability_target(function f)
{
    Ability_target = f;
}

/* Function name: set_ability_target_verify
 * Description:   Indicate which function to use to verify the ability's
 *                target. This function should be of the form
 *
 *                     object *func(object, string)
 *
 *                where the first argument is the actor, and the second is
 *                the string argument passed to the command.  The
 *                function returns an array of targets, empty if none were
 *                found.
 *
 * Arguments:     1. (function) The verify function
 */
public void
set_ability_target_verify(function f)
{
    Ability_target_verify = f;
}



static void schedule_ability(object actor,mixed * targets,string arg)
{

}

static void ability_msg(object actor,mixed * targets,string arg)
{
    write("You prepare to "+short()+".\n");
}

/*
 * Function name: check_valid_action
 * Description:   Perform ability-specific checks
 * Arguments:     1. (object) The actor
 *                2. (mixed *) The targets
 *                3. (string) Arguments passed to the command
 *                4. (int) Actual spell execution
 * Returns:       (int) 1 if we can continue, 0 if failure
 */
static int check_valid_action(object actor,mixed * targets,string arg,int 
                                execute = 0)
{
    return 1;
}


/*
 * Function name: target_spell
 * Description:   Find the target(s) for spell invocation.
 * Arguments:     1. (object) The caster
 *                2. (string) Arguments passed to the "cast" command
 * Returns:       (object *) The targets found.
 */
public object *
target_ability(object actor, string arg)
{
    if (Ability_target)
    {
        return Ability_target(actor, arg);
    }

    return ({});
}

/*
 * Function name: query_spell_pretarget
 * Description:   Indicates whether this ability should acquire targets 
 *                before invoking.
 * Returns:       true (1) - All abilities are pretargeted by default.
 */
public int
query_ability_pretarget()
{
    return 1;
}


/*
 * Function name: filter_kill_access
 * Description:   This function is called to determine which target the
 *                player is able to attack (in the case of an offensive special)
 * Arguments:     1. (object) The player
 *                2. (object) The target
 *                3. (int) If true, don't write failure messages
 * Returns:       True if ok, otherwise false
 */
varargs public int
filter_kill_access(object player, mixed target, int silent)
{

    object ob;
    if (objectp(target))
    {
        ob=target;
    }
    
    if (pointerp(target))
    {
        ob=target[0];
    }
    
    if (!ob)
    {
        return 0;
    }
    
    if (ob == player)
    {
        return 0;
    }
    
    if (!living(ob) || ob->query_ghost() || ob == player)
    {
        return 0;
    }

    if (!present(ob, environment(player)))
    {
        return 0;
    }

    if (NPATTACK(ob))
    {
        if (!silent)
        {
            hook_no_attack_fail(ob);
        }

        return 0;
    }

    if (!F_DARE_ATTACK(player, ob) && (player->query_attack() != ob))
    {
        if (!silent)
        {
            hook_dont_dare_attack_fail(ob);
        }

        return 0;
    }

    /*** confirm attack on introduced person ***/
    if ((!player->query_npc()) && query_ability_confirm_attack() &&
        (player->query_met(ob)) &&
        (player->query_prop(LIVE_O_LAST_KILL) != ob) &&
        (member_array(ob, player->query_enemy(-1)) == -1))
    {
        player->add_prop(LIVE_O_LAST_KILL, ob);
        if (!silent)
        {
            hook_confirm_attack(ob,this_object());
        }
        return 0;
    }
    
    if (member_array(ob,player->query_team_others())>=0)
    {
        if (!silent)
        {
            hook_no_attack_teammate(ob);
        }
        return 0;
    }
    return 1;
}


public int check_ability_pending(object actor,object room)
{
    if (actor->query_prop(LIVE_O_ACTION+Ability_name)==this_object())
    {
        hook_already_active(this_object());
        return 1;
    }
        
    if (objectp(room) && 
            actor->query_prop(LIVE_O_ACTION_ENV+Ability_name) != room)
    {
        if (Ability_stationary)
        {
            hook_changed_env();
            return 1;
        }
    }
    return 0;
}

public int set_ability_pending(object actor,object room,int set)
{
    if (set)
    {
        actor->add_prop(LIVE_O_ACTION+Ability_name, this_object());
        actor->add_prop(LIVE_O_ACTION_ENV+Ability_name, room);
    }
    else
    {
        actor->remove_prop(LIVE_O_ACTION+Ability_name);
    }
        
}



/*
 * Function name: start_ability
 * Description:   Start on the ability
 * Arguments:     1. (object)   The caster
 *                2. (mixed *) The targets
 *                3. (string)   The arguments passed to the command
 * Returns:       0 - Concentration begun
 *                1 - Concentration not begun; ability aborted.
 */
public nomask int
start_ability(object actor, mixed * targets, string arg)
{
    object room, *combatants;
    mixed why;
    int reduce;
    
    mixed * vtargets = targets;
 
    if (Ability_no_stun && actor->query_prop(LIVE_I_STUNNED))
    {
        hook_stun_fail(this_object());
        return 1;
    }


    if (check_ability_pending(actor,0))
    {
        return 1;
    }

    if (!Ability_no_reveal)
    {
        actor->reveal_me();
    }

    room = environment(actor);

    if (Ability_peaceful)
    {
        if (sizeof(combatants = (filter(all_inventory(environment(actor)),
            &operator(==)(actor) @ &->query_attack()) |
            ({ actor->query_attack() })) - ({ 0 })))
        {
            hook_combat_fail(combatants,this_object());
            return 1;
        }
    }

    if (Ability_vocal)
    {
        if (why = actor->query_prop(LIVE_M_MOUTH_BLOCKED))
        {
            hook_cannot_speak_fail(stringp(why) ? why : 0);
            return 1;
        }

        /* Check for under water? */
    }

    if (Ability_visual)
    {
        if (!CAN_SEE_IN_ROOM(actor))
        {
            hook_cannot_see_fail();
            return 1;
        }
    }

    if (Ability_offensive &&
        (why = RNATTACK(room)))
    {
        hook_room_no_attack_fail(why, room);
        return 1;
    }
    
    if (Ability_offensive && query_ability_pretarget())
    {
        /* Get all targets that we can hit with our ability */
        targets = filter(targets, &filter_kill_access(actor));

        if (!sizeof(targets))
        {
            return 1;
        }
    }
    
    if (!check_valid_action(actor,targets,arg))
    {
        return 1;
    }
    
    mixed * items=check_required_items(actor,targets,arg,1);
    
    if (!pointerp(items))
    {
        return 1;
    }
    
    if (Ability_offensive && query_ability_pretarget())
    {

        foreach (mixed target : targets)
        {
            object ob;
            if (objectp(target))
            {
                ob=target;
            }
            if (pointerp(target))
            {
                ob=target[0];
            }
            if (!objectp(ob))
            {
                continue;
            }
            
            if(actor->query_attack() != ob)
            {
	            hook_attack_object(ob);
	            actor->attack_object(ob);
	        }

            if (member_array(actor,ob->query_enemy(-1))==-1)
            {
                ob->attacked_by(actor);
            }
            
        }

    }

    restore_required_items(items);

    set_ability_pending(actor,room,1);
        
    ability_msg(actor, targets, arg);

    schedule_ability(actor, targets, arg);
    
    return 0;
}

static int
query_success(object actor,mixed target)
{
    return 0;
}


/*
 * Function name: cast_spell
 * Description:   This function handles the actual casting of the spell.
 * Arguments:     1. (object)   the actor
 *                2. (object *) the targets
 *                3. (string)   arguments to spell invocation
 * Returns:       1 - ability success
 *                0 - ability failure, default fail message
 *                string - ability failure, use string for fail message
 */
nomask public mixed
execute_ability(object actor, mixed * targets, string arg)
{
    mixed * results=({ }), why;
    int delay, *resist;
    object target, *all_ingrs, *combatants, *vtargets;
    function f;
    
    mixed * oldtargets = targets;

    if (!actor)
    {
        return 0;
    }

    set_ability_pending(actor,0,0);
        
    if (check_ability_pending(actor,environment(actor)))
    {
        return 0;
    }

    if (Ability_no_stun && actor->query_prop(LIVE_I_STUNNED))
    {
        hook_stun_fail(this_object());
        return 1;
    }
    
    if (!query_ability_pretarget())
    {
        targets = target_ability(actor, arg);
        if (!targets)
        {
            return 0;
        }
    }
    else
    {
        // Per agreement by Balance team on August 29, 2008
        // Specials will attack the currently engaged enem(ies)
        //   rather than continuing to attack the originally
        //   targeted enem(ies).
        if (Ability_offensive)
        {
            if (sizeof(targets) == 1)
            {
                targets = ({ actor->query_attack() });
            }
            else if (sizeof(targets) > 1)
            {
                // Target all the enemies. The verification
                // function should filter out those that are
                // not in the same room.
                targets = actor->query_enemy(-1);
            }
        }
    }        

    if (Ability_target_verify)
    {
        vtargets = Ability_target_verify(actor, targets, arg);
    }
    else
    {
        vtargets = targets - ({ 0 });
    }

    if ((sizeof(targets) > 0) && (sizeof(vtargets) == 0))
    {
        hook_targets_gone(targets);
        return 0;
    }


    targets = vtargets;

    if (Ability_peaceful)
    {
        if (sizeof(combatants = (filter(all_inventory(environment(actor)),
            &operator(==)(actor) @ &->query_attack()) |
            ({ actor->query_attack() })) - ({ 0 })))
        {
            hook_combat_fail(combatants,this_object());
            return 0;
        }
    }

    if (Ability_vocal)
    {
        if (why = actor->query_prop(LIVE_M_MOUTH_BLOCKED))
        {
            hook_cannot_speak_fail(stringp(why) ? why : 0);
            return 0;
        }

        /* Check for under water? */
    }

    if (Ability_visual)
    {
        if (!CAN_SEE_IN_ROOM(actor))
        {
            hook_cannot_see_fail();
            return 0;
        }
    }

    if (Ability_offensive)
    {
        /* Get all targets that we can hit with our ability */
        targets = filter(targets, &filter_kill_access(actor));

        if (!sizeof(targets))
        {
            if (sizeof(oldtargets))
            {
                hook_targets_gone(oldtargets);
            }
            return 0;
        }
    }

    if (!check_valid_action(actor,targets,arg,1))
    {
        return 1;
    }

    mixed * items=check_required_items(actor,targets,arg,1);
    
    if (!pointerp(items))
    {
        return 1;
    }

    foreach (mixed target : targets)
    {
        mixed result;
    
    /* Check if the spell is successfully cast */
        result = query_success(actor, target);

        results+=({ result });
    }


    if (!Ability_resist)
    {
        resist = allocate(sizeof(targets));
    }
    else
    {
        resist = map(targets, 
            &Ability_resist(actor, , Ability_name ));
    }

    resolve_ability(actor, items, targets, resist, results);

    return 1;
}


/*
 * Function name: make_spell_effect_object
 * Description:   Create, default configure, and move spell effect objects
 *                to the targets.
 * Arguments:     1. (object)   The spell effect object
 *                   (string)   The filename of the spell effect (to be cloned)
 *                   (function) A function that returns a spell effect
 *                2. (object)   The caster
 *                3. (object)   The target
 *                   (object *) An array of targets
 *                4. (int)      Resistance value for single target
 *                   (int *)    Resistance values corresponding to each target
 *                5. (int)      The casting success, as given by
 *                              query_casting_success()
 * Returns:       (object *) An array of spell effect objects, one element for
 *                           each target
 *                (object)   A single spell effect object if target was
 *                           specified as a single object.
 */
public mixed
make_ability_effect_object(mixed obj, object actor,
    mixed targets, mixed resist, int result)
{
    int i;
    object effect, *obs;
    function f;
    object *target_arr;
    int *resist_arr;

    target_arr = (pointerp(targets) ? targets : ({ targets }));
    resist_arr = (pointerp(resist)  ? resist  : ({ resist }));
    i = sizeof(target_arr);
    obs = allocate(i);

    setuid();
    seteuid(getuid());
    while (i--)
    {
        if (functionp(obj))
        {
            f = obj;
            effect = f(actor, targets);
        }
        else if (stringp(obj))
        {
            effect = clone_object(obj);
        }
        else
        {
            effect = obj;
        }

        obs[i] = effect;

        effect->set_effect_name(query_ability_name());
        effect->set_effect_caster(actor);
        effect->set_effect_target(target_arr[i]);

        if (!effect->setup_effect())
        {
            // Should we destroy the spell effect object?
            obs[i] = 0;
        }
    }

    if (pointerp(targets))
    {
        return obs;
    }

    return obs[0];
}


static void
restore_required_items(mixed *items)
{
}

static void resolve_ability(object actor, mixed * items,
            mixed * targets, int *resist, mixed *results)
{
}


/*
 * Function name: check_required_items
 * Description  : Does some validation to make sure the actor has
 *                all the equipment they need to perform the special.
 * Returns      : items that are required, or 0 if a required item is
 *                missing.
 */
static mixed * check_required_items(object actor,
                    mixed * targets,string arg,int pretest)
{
    return ({ });
}

/*
 * Function name: default_config_spell
 * Description:   Set the default values for the variables
 */
public void
default_config_ability()
{
    set_ability_time(15);
    set_ability_offensive(0);
    set_ability_stationary(0);
    set_ability_fail(0);
    set_ability_no_reveal(0);
    set_ability_no_stun(1);
    set_ability_vocal(0);
    set_ability_visual(1);
    set_ability_peaceful(0);
    set_ability_confirm_attack(1);
    set_ability_target_verify(verify_present);
}

/* 
 * Function name: config_ability
 * Description:   (Re)Configure this ability for this specific casting 
 *                attempt. This can be used to redefine certain parameters 
 *                such as mana cost, casting time, etc. on a per-casting 
 *                basis.  It can also be used to trigger an instant spell 
 *                failure (no components/mana consumed).
 *                N/B - These abilities are often used with only a SINGLE
 *                MASTER - changing this for one player could affect all
 *                other players!
 *
 *
 * Arguments:     1. (object)   The actor
 *                2. (object *) The targets
 *                3. (string)   The arguments passed to the command
 * Returns:       0 - Configuration successful.
 *                1 - Configuration not successful.  Ability aborted.
 *
 */
public varargs int
config_ability(object actor, object *targets, string arg)
{
    return 0;
}


public int do_ability(string arg)
{
    object player = this_player();
    object * targets = ({});
    
    if (check_ability_pending(player,0))
    {
        return 1;
    }

    if (query_ability_pretarget())
    {
        targets = target_ability(player, arg);
    
        if (!sizeof(targets))
        {
            return 1;
        }
    }

    if (this_object()->do_ability_setup(player, targets, arg))
    {
        return 1;
    }

    start_ability(player, targets, arg);
    return 1;
}

/*
 * Function name: create_ability
 * Description:   Configure this spell.
 *
 * Note:          If you need to reset various spell settings on a per-casting
 *                basis (vary casting time based on the level of the caster,
 *                for instance), use config_spell().
 */
public void
create_ability()
{
    // This is for backward compatibility.
    config_ability(0);
}

private nomask void
create()
{
    default_config_ability();
    create_ability();
}
