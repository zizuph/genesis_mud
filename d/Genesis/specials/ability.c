/*
 * /d/Genesis/specials/ability.c
 *
 * Base Ability Module
 *
 * This is the base module that allows specials to be created. One should
 * generally not inherit from this directly, but instead look to either
 * timed_ability.c, or damage.c in the std directory.
 *
 * The ability module is very similar to the spell system created by
 * Shiva. This module was adapted for use by Novo originally in May 2008.
 * Subsequently, during the implementation of the guild recodes, the
 * module cleaned up and further changed to incorporate bug fixes as
 * well as support for cooldown times by Petros.
 *
 * Created May 2008 by Novo
 * Adapted October 2008 by Petros
 *
 * Modified 2019-06-11 by Carnak:
 *  - The function query_success() has been altered to allow modification of
 *    query_tohit based on items hit value. The argument items has been added.
 */
 
/*
 * THIS CODE IS JUST TEMPORARY UNTIL HOOKS HAVE BEEN ADDED TO THE STD/OBJECT
 * FILE SO WE CAN USE PROPER MOVEMENT OF OBJECTS AS AN INDICATOR.
 *
 * Anti bouncing modifications can be found inside functions:
 * validate_ability_move
 * start_ability
 * execute_ability
 * adjust_ability_on_move
 * adjust_ability_on_hunt
 */

#pragma strict_types

#include "defs.h"

inherit HOOKS_LIB;
inherit TARGETTING_LIB;

#include <stdproperties.h>
#include <ss_types.h>
#include <comb_mag.h>
#include <macros.h>
#include <formulas.h>
#include <hooks.h>

#include "/d/Genesis/specials/debugger/debugger_tell.h"

#define LIVE_O_ACTION_ENV           "_live_o_action_env_"
#define PLAYER_M_BOUNCING           "_player_m_bouncing_"

static string
     Ability_name,          /* The name of the special */
     Ability_group;

static int 
     Ability_exp_factor,    /* The general exp factor for this */
     Ability_prep_time,     /* Time for special preparation */
     Ability_cooldown_time, /* Time of cooldown after execution */
     Ability_offensive,     /* True if it is combat initiating */
     Ability_stationary,    /* If the ability requires standing still */
     Ability_hunting,       /* If the ability allows movement when hunting */
     Ability_no_stun,       /* If the ability cannot be done stunned */
     Ability_no_reveal,     /* True if the ability should not reveal the 
                                caster if hidden during prep time */
     Ability_attack_prep,   /* True if an ability should attack during the
                               prep time */
     Ability_vocal,
     Ability_visual,
     Ability_peaceful,
     Ability_confirm_attack,
     Ability_exclusive;     /* When this ability is being run, no other
                               abilities are allowed. */
     
static mixed
     Ability_fail;          /* The message given if the ability fails */

static string *
     Ability_restrictions; /* List of abilities that cannot run at same time */
     
static function
     Ability_resist,            /* The resistance function */
     Ability_target,            /* The targeting function */
     Ability_target_verify;     /* Verify target function */


static void resolve_ability(object actor, mixed * items, 
            mixed * targets, int * resist, mixed * results);

public varargs int config_ability(object caster, object * targets, 
                    string arg);


static mixed * check_required_items(object actor,mixed * targets,
                    string arg,int pretest);

/* Callback hooks 
 * Everything in here is temporary.. new code incoming, hold your horses.
 */


/*
 * Function name: set_ability_allow_hunting
 * Description:   Allow movement during execution, only affects stationary
 *                abilities.
 * Arguments:     1. (int) True if ability is allows hunting
 */
public void
set_ability_allow_hunting(int i)
{
    Ability_hunting = i;
} /* set_ability_allow_hunting */

/*
 * Function name: query_ability_allow_hunting
 * Description:   Returns whether the ability should allow stationary abilities
 *                to move while hunting.
 * Arguments:     none
 * Returns:       0 - Ability does not allow hunting. Person may not move
 *                1 - Ability allows hunting, person may move while hunting.
 */
public int
query_ability_allow_hunting()
{
    return Ability_hunting;
} /* query_ability_allow_hunting */

/* **Temporary**
 * Sets an indicator that you have moved during the execution of this special.
 */
public void
adjust_ability_on_move(object *enemies, object actor)
{
    mapping move;
    
    if (!mappingp(move = actor->query_prop(PLAYER_M_BOUNCING + Ability_name)))
        move = ([]);
    
    if (move["move"])
        return;
    
    move["move"] = 1;
    actor->add_prop(PLAYER_M_BOUNCING + Ability_name, move);
}

/* **Temporary**
 * Sets enemies allowed to hunt with this special
 */
public void
adjust_ability_on_hunt(object enemy, object actor)
{
    mapping hunt;
    
    if (!mappingp(hunt = actor->query_prop(PLAYER_M_BOUNCING + Ability_name)))
        hunt = ([]);
    
    if (!pointerp(hunt["hunt"]))
        hunt["hunt"] = ({});
    
    if (IN_ARRAY(enemy, hunt["hunt"]))
        return;
    
    hunt["hunt"] += ({ enemy });
    actor->add_prop(PLAYER_M_BOUNCING + Ability_name, hunt);
}


/*
 * Function name: add_ability_hooks
 * Description:   Adds callback hooks, which trigger on events. This is called
 *                in start_ability.
 * Arguments:     None
 * Returns:       Nothing
 */
public void
add_ability_hooks(object actor)
{
    actor->add_hook(HOOK_LIVING_HUNTING, &adjust_ability_on_hunt(, actor));
    actor->add_hook(HOOK_LIVING_HUNTED, &adjust_ability_on_move(, actor));
} /* add_ability_hooks */

/*
 * Function name: remove_ability_hooks
 * Description:   Removes the callback hooks. This is called in execute_ability
 *                and abort_ability.
 * Arguments:     None
 * Returns:       Nothing
 */
public void
remove_ability_hooks(object actor)
{
    actor->remove_hook(HOOK_LIVING_HUNTING, this_object());
    actor->remove_hook(HOOK_LIVING_HUNTED, this_object());
} /* remove_ability_hooks */

/* Callback hooks END */

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
 * Function name: set_ability_prep_time
 * Description:   Set the time it takes to prepare the ability
 * Arguments:     1. (int) The time it should take in seconds
 */
public void
set_ability_prep_time(int time)
{
    Ability_prep_time = time;
}

public int
query_ability_prep_time()
{
    return Ability_prep_time;
}

/*
 * Function name: set_ability_cooldown_time
 * Description:   Set the time it takes to prepare the ability
 * Arguments:     1. (int) The time it should take in seconds
 */
public void
set_ability_cooldown_time(int time)
{
    Ability_cooldown_time = time;
}

public int
query_ability_cooldown_time()
{
    return Ability_cooldown_time;
}

/*
 * Function name: set_ability_time
 * Description:   Set the time it takes to prepare the ability
 * Arguments:     1. (int) The time it should take in seconds
 */
public void
set_ability_time(int time)
{
    Ability_prep_time = time;
    Ability_cooldown_time = 0;
    /*
    // Below is how we want to default prep time and cooldown times
    // However, we can't do this until all abilities are converted
    // over.    
    switch (time)
    {
    case 0..5:
        Ability_prep_time = time;
        break;
        
    case 6..10:
        Ability_prep_time = 6;
        break;
    
    case 11..20:
        Ability_prep_time = 8;
        break;
    
    default:
        Ability_prep_time = 10;
    }
    Ability_cooldown_time = time - Ability_prep_time;  
    */
}

public int
query_ability_time()
{
    return query_ability_prep_time() + query_ability_cooldown_time();
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
 * Function:    query_ability_offensive
 * Description: By default, just returns the value specified in
 *              set_ability_offensive. However, this can be
 *              overridden to take into account the targets and
 *              determine whether to be offensive or not.
 */
public varargs int
query_ability_offensive(mixed * targets = 0)
{
    return Ability_offensive;
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
 * Function name: query_ability_stationary
 * Description:   Returns whether the ability should be stationary
 *                (person should not move while executing ability)
 * Arguments:     none
 * Returns:       0 - Ability is not stationary. Person may move
 *                1 - Ability is stationary, person may not move.
 */
public int
query_ability_stationary()
{
    return Ability_stationary;
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
public mixed
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
 * Function name: set_ability_attack_during_prep
 * Description:   Set this to true if the ability should attack 
 *                during the preparation stage
 * Returns:       nothing
 */
public void
set_ability_attack_during_prep(int i)
{
    Ability_attack_prep = i;
}

/*
 * Function name: query_ability_pretarget (deprecated)
 * Description:   This was the old method used to determine whethe someone
 *                would attack during preparation phase. This has been
 *                replaced by using query_ability_attack_during_prep
 *                and set using set_ability_attack_during_prep. DO NOT
 *                use this function unless necessary. It will be removed
 *                once all instances that use it are changed.
 * Returns:       true/false, indicating whether the actor will attack
 *                during the preparation stage
 */
public int
query_ability_pretarget()
{
    return 1;
}

/*
 * Function name: query_ability_attack_during_prep
 * Description:   Ability causes attack during the prep time
 * Returns:       true/false, indicating whether the actor will attack
 *                during the preparation stage
 */
public int
query_ability_attack_during_prep()
{
    // ONCE all abilities stop using query_ability_pretarget, this
    // call to it will be removed.
    if (!query_ability_pretarget())
    {
        return 0;
    }
    
    return Ability_attack_prep;
}

/* 
 * Function name: set_ability_confirm_attack
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
 * Function name: set_ability_group
 * Description:   Set the ability group name. 
 *                If set this will limit exclusivity checks to other
 *                abilities within the same group.
 */
public void
set_ability_group(string group)
{
    Ability_group = group;
}

public string
query_ability_group() 
{
    return Ability_group;
}

/* 
 * Function name: set_ability_exclusive
 * Description:   Specify that when this ability is being run, it must be
 *                exclusive, meaning that if there are any other abilities
 *                running, it cannot start. If it is running, no other
 *                abilities can start.
 * Arguments:     exclusive - boolean indicating whether it is exclusive
 */
public void
set_ability_exclusive(int exclusive)
{
    Ability_exclusive = exclusive;
}

/* 
 * Function name: query_ability_exclusive
 * Description:   Returns whether when this ability is being run, it must be
 *                exclusive, meaning that if there are any other abilities
 *                running, it cannot start. If it is running, no other
 *                abilities can start.
 * Arguments:     none
 * Returns:       0/1 - not exclusive/exclusive
 */
public int
query_ability_exclusive()
{
    return Ability_exclusive;
}

/* 
 * Function name: add_ability_restriction
 * Description:   Restricted abilities are those abilities that cannot be
 *                used when this one is active, and vice versa. A common
 *                use of this is to prevent two similar specials from
 *                being used at the same time.
 * Arguments:     file - The filename of the ability that should
 *                       be restricted
 */
public void
add_ability_restriction(string file)
{
    if (!Ability_restrictions)
    {
        Ability_restrictions = ({ });
    }
    
    if (LOAD_ERR(file))
    {
        return;
    }
    
    if (!IN_ARRAY(ABILITY_LIB + ".c", inherit_list(find_object(file))))
    {
        return;
    }

    Ability_restrictions += ({ file });
}

/* 
 * Function name: query_ability_restrictions
 * Description:   Returns the list of abilities that are considered
 *                restricted, meaning that they cannot be run at the
 *                same time as this ability
 * Arguments:     none
 * Returns:       array of restrictions or 0
 */
public string *
query_ability_restrictions()
{
    return Ability_restrictions;
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

static void 
schedule_ability(object actor,mixed * targets,string arg)
{

}

static void 
ability_msg(object actor,mixed * targets,string arg)
{
    actor->catch_msg("You prepare to " + short() + ".\n");
}

/*
 * Function name: check_valid_action
 * Description:   Perform ability-specific checks. Called from the
 *                can_start_ability and can_execute_ability methods.
 * Arguments:     1. (object) The actor
 *                2. (mixed *) The targets
 *                3. (string) Arguments passed to the command
 *                4. (int) Actual spell execution
 * Returns:       (int) 1 if we can continue, 0 if failure
 */
static int 
check_valid_action(object actor, mixed * targets, 
                   string arg, int execute = 0)
{
    return 1;
}

public varargs string
query_restricted_ability_message(string ability, object actor)
{
    string short_desc;
    
    short_desc = ability->short();
    if (!strlen(short_desc))
    {
        return "You are too focused at the moment to do that.\n";
    }
    
    return ("You are too focused at the moment to " + short_desc + ".\n");    
}

public varargs object *
query_active_abilities(object actor, string ability_group)
{
    string * all_abilities = ({ });
    object * active_abilities = ({ });
    mixed abilities;
    
    foreach (string soul : actor->query_cmdsoul_list())
    {
        abilities = soul->query_ability_map();
        if (abilities && mappingp(abilities))
        {
            all_abilities += m_values(abilities);
        }
    }
    all_abilities -= ({ MASTER_OB(this_object()) });
    
    foreach (string ability: all_abilities)
    {
        object ability_obj;
        ability_obj = find_object(ability);
        if (!objectp(ability_obj) || !ability_obj->query_ability_active(actor))
        {
            continue;
        }
        
        if (ability_obj->query_ability_group() != ability_group)
        {
            continue;
        }
        
        active_abilities += ({ ability_obj });
    }
    
    return active_abilities;
}

public int
query_is_restricted(object actor)
{
    string msg;
    object * active_spells, * active_abilities;
    
    active_abilities = query_active_abilities(actor, query_ability_group());
    if (!sizeof(active_abilities))
    {
        // No other active abilities. We can safely start this ability
        return 0;
    }
    
    // Rule: Spells take precedence over Specials. That means that if
    //       one is in the middle of preparing a special, they can start
    //       a spell, and the currently preparing specials will cancel.
    if (this_object()->query_spell())
    {
        active_spells = filter(active_abilities, &->query_spell());
        // We don't allow spells to be cast when there's another spell being
        // cast. If it's in cooldown, it's alright (eg. encounter/daily/at will
        // spells)
        active_spells = filter(active_spells, &->query_ability_preparing(actor));
        if (sizeof(active_spells))
        {
            // If there are other spells active, then we cannot start
            // this spell.
            msg = active_spells[0]->query_restricted_ability_message(MASTER, actor);
            if (stringp(msg))
            {
                actor->catch_msg(msg);
            }       
            send_debug_message("base_ability", "Already casting a spell "
                + "and cannot start another one.");
            return 1;
        }
        
        // No spells active. For all abilities, we stop them if they are
        // in the preparation mode.
        foreach (object ability : active_abilities)
        {
            send_debug_message("base_ability", "Casting a spell, so "
                + "stopping all other abilities.");
            if (ability->query_ability_preparing(actor))
            {
                ability->stop_ability(actor);
            }
        }
        return 0;
    }
    
    // Now we go through all the abilities and check whether they are
    // active and whether this should be restricted
    foreach (object ability : active_abilities)
    {
        if (!query_ability_exclusive()
            && IN_ARRAY(MASTER_OB(ability), query_ability_restrictions()))
        {     
            msg = ability->query_restricted_ability_message(MASTER, actor);
            if (stringp(msg))
            {
                actor->catch_msg(msg);
            }       
            return 1;
        }
        
        // For exclusive abilities, we only check that it's not
        // preparing. We don't care about cooldowns.
        if (ability->query_ability_preparing(actor))
        {
            if (query_ability_exclusive()
                || ability->query_ability_exclusive())
            {
                msg = ability->query_restricted_ability_message(MASTER, actor);
                if (stringp(msg))
                {
                    actor->catch_msg(msg);
                }       
                return 1;
            }
        }
    }        
    
    return 0;
}

static nomask int
can_start_ability(object actor, mixed * targets, string arg)
{
    int result;
    
    /* Added to handle interrupted abilities */
    if (actor->query_ability_interrupted(this_object()))
    {
        return 0;
    }
    
    result = check_valid_action(actor, targets, arg, 0);
    if (!result)
    {
        return 0;
    }
    
    if (query_is_restricted(actor))
    {
        return 0;
    }
        

    /*
     * Disabling this as an experiment to keep fighter + magic combo
     * viable. 
    if (actor->query_prop(LIVE_I_CONCENTRATE))
    {
        actor->catch_tell("You are too busy concentrating on a spell.\n");
        return 0;
    }
    */
    
    return result;
}

static nomask int
can_execute_ability(object actor, mixed * targets, string arg)
{
    int result;
    
    /* Added to handle interrupted abilities */
    if (actor->query_ability_interrupted(this_object()))
    {
        return 0;
    }
    
    result = check_valid_action(actor, targets, arg, 1);
    if (!result)
    {
        return 0;
    }
    
    if (query_is_restricted(actor))
    {
        return 0;
    }

    /*
    if (actor->query_prop(LIVE_I_CONCENTRATE))
    {
        actor->catch_tell("You are too busy concentrating on a spell.\n");
        return 0;
    }
    */

    return result;
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

/*
 * Function name: set_ability_startloc
 * Description:   Sets the starting location of an ability so that
 *                one can check during the execution whether it has
 *                moved or not.
 * Arguments:     actor - The person executing the ability
 *                room  - the room the person is currently in
 * Returns:       Nothing
 */
public void 
set_ability_startloc(object actor, object room)
{
    actor->add_prop(LIVE_O_ACTION_ENV+Ability_name, room);
}

/*
 * Function name: query_ability_startloc
 * Description:   Checks the property for what the ability start location
 *                is. This is used both for checking stationary abilities
 *                as well as verifying bouncing during a cooldown period.
 * Arguments:     actor - The person executing the ability
 * Returns:       Room that the ability was executed.
 */
public object
query_ability_startloc(object actor)
{
    return actor->query_prop(LIVE_O_ACTION_ENV+Ability_name);
}

/*
 * Function name: validate_ability_stationary
 * Description:   If an ability is set to be stationary, then it can't
 *                work if the player has moved. Because it's not easy
 *                easy to detect movement other than the room that they
 *                are in, we check the room against the room that
 *                was set in set_ability_startloc. 
 * Arguments:     actor - the person executing the ability
 *                room  - the room that the person is in currently
 * Returns:       0 - Person has moved. Ability should abort.
 *                1 - Person has not moved. Ability can continue.
 */
public int 
validate_ability_stationary(object actor, object room)
{
    if (!query_ability_stationary())
    {
        return 1;
    }
    
    if (objectp(room) && 
        query_ability_startloc(actor) != room)
    {
        return 0;
    }
    return 1;
}

/*
 * Function name: validate_ability_move
 * Description:   **Temporary** Validates the movement of the player, if the
 *                player is hunting a target, specials will work as intended.
 *                If bouncing, it will cause the specials to fail. 
 * Arguments:     actor - the person executing the ability
 *                room  - the room that the person is in currently
 * Returns:       0 - Person has moved. Ability should abort.
 *                1 - Person has not moved. Ability can continue.
 */
public status
validate_ability_move(object actor, object *enemies)
{
    mapping move;
    
    if (!Ability_hunting)
        return 1;
    
    if (!mappingp(move = actor->query_prop(PLAYER_M_BOUNCING + Ability_name)))
        return 1;
    
    if (IN_ARRAY("move", m_indexes(move)) && move["move"])
    {
        /* The player has moved, verifying if hunting enemies */
        if (IN_ARRAY("hunt", m_indexes(move)) && sizeof(filter(enemies,
            &operator(>)(,-1) @ &member_array(, move["hunt"]))))
            return 1;
            
        return 0;
    }
    
    return 1;
}

/*
 * Function:    attack_targets
 * Description: Called when using an offensive ability. Does the
 *              actual work of attacking each of the targets. Ensures
 *              that the fight actually begins.
 */
public void
attack_targets(object actor, mixed * targets)
{
    object * target_objects = ({ });
    foreach (mixed target : targets)
    {
        object ob;
        if (objectp(target))
        {
            ob = target;
        }
        if (pointerp(target))
        {
            ob = target[0];
        }
        if (!objectp(ob))
        {
            continue;
        }
        
        target_objects += ({ ob });
    }
    
    if (!sizeof(target_objects))
    {
        return;
    }
    
    // We want to make sure we attack any new targets. Existing
    // targets in the room should not be re-attacked as it may
    // lead to strange behaviors for multi-target attacks
    object * current_enemies = actor->query_enemy(-1);
    object * current_enemies_in_room = ({ });
    foreach (object enemy : current_enemies)
    {
        if (environment(actor) == environment(enemy))
        {
            current_enemies_in_room += ({ enemy });
        }
    }
    
    // We switch attacks if our current enemy is not in the
    // list of targets.
    int bSwitchAttack = 0;
    if (!IN_ARRAY(actor->query_attack(), target_objects))
    {
        bSwitchAttack = 1;
    }
    
    foreach (object ob : target_objects)
    {    
        if (bSwitchAttack || !IN_ARRAY(ob, current_enemies_in_room))
        {
            bSwitchAttack = 0;
            hook_attack_object(ob);
            actor->attack_object(ob);
        }

        if (!IN_ARRAY(actor, ob->query_enemy(-1)))
        {
            ob->attacked_by(actor);
        }            
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
    
    /* Remove the prop if a fresh ability is starting */
    if (mappingp(actor->query_prop(PLAYER_M_BOUNCING + Ability_name)))
        actor->remove_prop(PLAYER_M_BOUNCING + Ability_name);
    
    if (Ability_no_stun && actor->query_prop(LIVE_I_STUNNED))
    {
        hook_stun_fail(this_object());
        return 1;
    }

    if (Ability_no_stun && present("_search_paralyze_", actor))
    {
        hook_search_fail(this_object());
        return 1;
    }
        
    if (!query_ability_no_reveal())
    {
        actor->reveal_me();
    }

    room = environment(actor);

    if (Ability_peaceful && !actor->query_npc())
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

    int bAbilityOffensive = query_ability_offensive(targets);
    if (bAbilityOffensive &&
        (why = RNATTACK(room)))
    {
        hook_room_no_attack_fail(why, room);
        return 1;
    }
    
    if (bAbilityOffensive)
    {
        /* Get all targets that we can hit with our ability */
        targets = filter(targets, &filter_kill_access(actor));

        if (!sizeof(targets))
        {
            return 1;
        }
    }
    
    if (!can_start_ability(actor, targets, arg))
    {
        return 1;
    }
    
    mixed * items=check_required_items(actor,targets,arg,1);
    
    if (!pointerp(items))
    {
        return 1;
    }
    
    if (bAbilityOffensive 
        && query_ability_attack_during_prep())
    {
        attack_targets(actor, targets);
    }

    /* Add callback hooks */
    add_ability_hooks(actor);
    set_ability_startloc(actor,room);
    
    // Notify the player of the ability starting
    ability_msg(actor, targets, arg);

    // Call the ability scheduler, defined in timed_ability
    schedule_ability(actor, targets, arg);
    
    return 0;
}

static int
query_success(object actor, mixed target, mixed *items)
{
    return 0;
}

/*
 * Function name: execute_ability
 * Description:   This function handles the actual casting of the spell.
 * Arguments:     1. (object)   the actor
 *                2. (object *) the targets
 *                3. (string)   arguments to ability invocation
 * Returns:       1 - ability "succeeded", meaning that cooldown should
 *                    take effect.
 *                0 - ability failure, meaning that player should
 *                    immediately be able to use ability again and skip
 *                    the cooldown period.
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

    /* remove the callback hooks */
    remove_ability_hooks(actor);
    
    // Added to enable blocking pvp abilities.
    if (call_self("disable_pvp_abilities", ({ actor })))
    {
        actor->catch_msg("Divine intervention prevents you from performing "
        + "this action.\n");
        return 0;
    }
    
    if (Ability_no_stun && present("_search_paralyze_", actor))
    {
        hook_search_fail(this_object());
        return 0;
    }

    if (!validate_ability_stationary(actor, environment(actor)))
    {
        hook_changed_env();        
        return 0;
    }
    
    /* Verifies if the player has moved during the prep period. */
    if (!validate_ability_move(actor, targets))
    {
        hook_changed_env();
        return 0;
    }

    if (Ability_no_stun && actor->query_prop(LIVE_I_STUNNED))
    {
        hook_stun_fail(this_object());
        return 0;
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

    if (Ability_peaceful && !actor->query_npc()) // npcs can still use abilities for testing purposes
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

    int bAbilityOffensive = query_ability_offensive(targets);
    if (bAbilityOffensive)
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

    if (!can_execute_ability(actor, targets, arg))
    {
        return 1;
    }

    // For spells, this line should return the required components
    // to cast the spell.
    mixed * items = check_required_items(actor, targets, arg, 0);
    
    if (!pointerp(items))
    {
        return 1;
    }

    // Always reveal when executing abilities.
    actor->reveal_me();
    
    if (bAbilityOffensive)
    {
        attack_targets(actor, targets);
    }

    foreach (mixed target : targets)
    {
        mixed result;
    
    /* Check if the spell is successfully cast */
        result = query_success(actor, target, items);

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
    set_ability_attack_during_prep(1);
    set_ability_exclusive(0);
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
    
    targets = target_ability(player, arg);

    if (!sizeof(targets))
    {
        return 1;
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
    setuid();
    seteuid(getuid());

    default_config_ability();
    create_ability();
}
