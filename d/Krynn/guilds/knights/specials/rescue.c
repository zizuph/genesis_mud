/*
 * /d/Krynn/guilds/knights/specials/rescue.c
 *
 * This is the rescue ability for Knights. It allows them to protect
 * someone who is being attacked and take on attackers themselves.
 *
 * Created by Petros, October 2008
 */
 
#pragma strict_types

#include "../guild.h"

inherit "/d/Genesis/specials/timed_ability";

#include <ss_types.h>
#include <tasks.h>
#include <composite.h>
#include <macros.h>
#include <wa_types.h>
#include <filter_funs.h>
#include <files.h>
#include <formulas.h>
#include <cmdparse.h>

#include "/d/Genesis/specials/debugger/debugger_tell.h"

// Prototypes
public object * query_attacking_enemies(object actor, string str);
public object * target_friend_for_rescue(object actor, string str);

public void config_ability()
{
    ::config_ability();
    set_ability_name("rescue");
    set_ability_offensive(0);
    set_ability_hasted(0);
    set_ability_prep_time(0);
    set_ability_cooldown_time(2);
    set_ability_visual(0);        
    set_ability_target(target_friend_for_rescue);    
}

static void 
ability_msg(object actor, mixed * targets, string arg)
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
    return query_attacking_enemies(actor, arg);
}

public void
display_rescue_messages_for_many(object actor, object friend, object * foes)
{
    string rescue;
    string * rescue2;
    int hp, max;
    
    // Rescue attempt succeeded. We now go through all the foes and redirect
    // the attacks.
    hp = friend->query_hp();
    max = friend->query_max_hp();
        
    if (hp > max * 3 / 5) /* Over 60% health */
    {
    	rescue = "Though "+QTNAME(friend)+" seems to be holding "
    	    + POSSESSIVE(friend) + " own against " + POSSESSIVE(friend) 
    	    + " attackers, you ";
    }
    else if (hp > max * 4 / 10) /* Between 40% and 60% health */
    {
    	rescue = "You see " + QTNAME(friend) + " being forced back a step "
    	    + "by " + POSSESSIVE(friend) + " attackers and ";
    }
    else if (hp > max / 4) /* Between 25% and 40% health */
    {
    	rescue = "Observing " + QTNAME(friend) + " steadily losing ground "
    	    + "to " + POSSESSIVE(friend) + " attackers, you ";
    }
    else if (hp > max / 10) /* Between 10% and 25% health */
    {
    	rescue = "You notice that " + QTNAME(friend) + " is beginning to "
    	    + "to buckle beneath the many attacks of " + POSSESSIVE(friend) 
    	    + " attackers, and ";
    }
    else
    {
        /* Less than 10 % health */
        rescue = "Realizing that " + QTNAME(friend) + " is about to fall before "
            + "the onslaught " + PRONOUN(friend) + "'s receiving at the hands of "
            + POSSESSIVE(friend) + " attackers, you ";
    }        
    
    switch(random(6))
    {
    case 5:
    	rescue2 =
    	    ({ "shout a command to "+QTNAME(friend)+", having "+
    		   OBJECTIVE(friend)+" fall back so that you stand between "+
    		   OBJECTIVE(friend)+" and " + POSSESSIVE(friend) + " attackers.\n",
    		   "You fall back as "+QTNAME(actor)+" shouts a command to "+
    		   "you, leaving "+OBJECTIVE(actor)+" standing between "+
    		   "you and you attackers.\n",
    		   QCTNAME(friend)+" falls back at a command from "+QTNAME(actor)+
    		   ", leaving "+QTNAME(actor)+" standing between "+
    		   OBJECTIVE(friend)+" and " + POSSESSIVE(friend) + " attackers.\n",
    		   QCTNAME(friend)+" falls back at a command from "+QTNAME(actor)+
    		   ", who moves to stand between you and "+QTNAME(friend)+".\n" });
    	break;
    case 4:
    	rescue2 = ({ "run toward " + POSSESSIVE(friend) + " attackers, forcing " +
    			 "them to engage in combat with you, "+
    			 "rather than "+QTNAME(friend)+".\n",
    			 QCTNAME(actor)+" runs toward your attackers" +
    			 ", forcing them to engage in combat "+
    			 "with "+OBJECTIVE(actor)+" rather than you.\n",
    			 QCTNAME(actor)+" runs toward " + POSSESSIVE(friend) + " attackers" +
    			 ", forcing them to engage in combat "+
    			 "with "+OBJECTIVE(actor)+" rather than "+QTNAME(friend)+".\n",
    			 QCTNAME(actor)+" runs toward you, forcing you to engage "+
    			 "in combat with "+OBJECTIVE(actor)+", rather than "+
    			 QTNAME(friend)+".\n" });
    	break;
    case 3:
    	rescue2 =
    	    ({ "shout out a Solamnic battlecry as you charge "+
    		   "forward, drawing the attention of " + POSSESSIVE(friend) 
    		   + " attackers.\n",
    		   QCTNAME(actor)+" draws the attention of your enemies, as "
    		   +PRONOUN(actor)+" charges forward, "+
    		   "shouting out a Solamnic battlecry.\n",
    		   QCTNAME(actor)+" draws the attention of " + POSSESSIVE(friend) 
    		   + " attackers as "+PRONOUN(actor)+" charges forward, shouting "
    		   + "out a Solamnic battlecry.\n",
    		   QCTNAME(actor)+" draws your attention as "+PRONOUN(actor)+
    		   " charges forward, shouting out a Solamnic battlecry.\n" });
    	break;
    case 2:
    	rescue2 =
    	    ({ "maneuver so that " + POSSESSIVE(friend) + " attackers are "+
    		   "forced to fight you, and ignore "+QTNAME(friend)+".\n",
    		   QCTNAME(actor)+" maneuvers so that your attackers are "+
    		   "forced to fight "+OBJECTIVE(actor)+", and ignore you.\n",
    		   QCTNAME(actor)+" maneuvers so that " + POSSESSIVE(friend) 
    		   + " attackers are forced to fight "+OBJECTIVE(actor)
    		   +", and ignore "+ QTNAME(friend)+".\n",
    		   QCTNAME(actor)+" maneuvers so that you are forced to fight "+
    		   "him, and ignore "+QTNAME(friend)+".\n" });
    	break;
    case 1:
    	rescue2 =
    	    ({ "pull "+QTNAME(friend)+" out of harm's way, stepping "+
    		   "forward to take the brunt of the incoming attacks.\n",
    		   "Pulling you out of harm's way, "+QTNAME(actor)+" steps "+
    		   "forward to take the brunt of incoming attacks.\n",
    		   "Pulling "+QTNAME(friend)+" out of harm's way, "+QTNAME(actor)+
    		   " steps forward to take the brunt of the incoming attacks.\n",
    		   "Pulling "+QTNAME(friend)+" out of harm's way, "+QTNAME(actor)+
    		   " steps forward to take the brunt of your attacks.\n" });
    	break;
    default:
    	rescue2 =
    	    ({ "manage to distract " + POSSESSIVE(friend) + " attackers, "+
    		   "enabling "+QTNAME(friend)+" to escape as they turn to "
    		   + "attack you.\n",
    		   "Your attackers turn to attack "+QTNAME(actor)+" as "+
    		   QTNAME(actor)+" distracts them, allowing you to escape.\n",
    		   "Foes turn to attack "+QTNAME(actor)+" as "+
    		   QTNAME(actor) + " distracts them, allowing "+
    		   OBJECTIVE(friend)+" to escape.\n",
    		   "You turn to attack "+QTNAME(actor)+" as "+PRONOUN(actor)+
    		   " distracts you, allowing "+QTNAME(friend)+" to escape.\n" });
    	break;
    } 

    foreach (object foe : foes)
    {
        actor->attack_object(foe);
        foe->attack_object(actor);
        foe->catch_msg(rescue2[3]);
    }       
    actor->catch_msg(rescue + rescue2[0]);
    friend->catch_msg(rescue2[1]);
    say(rescue2[2], ({friend, actor}) + foes);
}

public void
display_rescue_messages_for_one(object actor, object friend, object foe)
{
    string rescue;
    string * rescue2;
    int hp, max;
    
    // Rescue attempt succeeded. We now go through all the foes and redirect
    // the attacks.
    hp = friend->query_hp();
    max = friend->query_max_hp();
        
    if (hp > max * 3 / 5) /* Over 60% health */
    {
    	rescue = "Though "+QTNAME(friend)+" seems to be holding "+
    	    POSSESSIVE(friend)+" own against "+QTNAME(foe)+", you ";
    }
    else if (hp > max * 4 / 10) /* Between 40% and 60% health */
    {
    	rescue = "You see "+QTNAME(foe)+" force "+QTNAME(friend)+
    	    " back a step and ";
    }
    else if (hp > max / 4) /* Between 25% and 40% health */
    {
    	rescue = "Observing "+QTNAME(friend)+" steadily losing ground "+
    	    "to "+QTNAME(foe)+", you ";
    }
    else if (hp > max / 10) /* Between 10% and 25% health */
    {
    	rescue = "You notice that "+QTNAME(friend)+" is beginning to to "+
    	    "buckle beneath "+QTNAME(foe)+"'s attacks, and ";
    }
    else
    {
        /* Less than 10 % health */
        rescue = "Realizing that " + QTNAME(friend) + " is about to fall before "
            + "the onslaught " + PRONOUN(friend) + "'s receiving at the hands of "
            + QTNAME(foe)+", you ";
    }        
    
    switch(random(6))
    {
    case 5:
    	rescue2 =
    	    ({ "shout a command to "+QTNAME(friend)+", having "+
    		   OBJECTIVE(friend)+" fall back so that you stand between "+
    		   OBJECTIVE(friend)+" and "+QTNAME(foe)+".\n",
    		   "You fall back as "+QTNAME(actor)+" shouts a command to "+
    		   "you, leaving "+OBJECTIVE(actor)+" standing between "+
    		   "you and "+QTNAME(foe)+".\n",
    		   QCTNAME(friend)+" falls back at a command from "+QTNAME(actor)+
    		   ", leaving "+QTNAME(actor)+" standing between "+
    		   OBJECTIVE(friend)+" and "+QTNAME(foe)+".\n",
    		   QCTNAME(friend)+" falls back at a command from "+QTNAME(actor)+
    		   ", who moves to stand between you and "+QTNAME(friend)+".\n" });
    	break;
    case 4:
    	rescue2 = ({ "run toward " + QTNAME(foe)+", forcing "+
    			 OBJECTIVE(foe)+" to engage in combat with you, "+
    			 "rather than "+QTNAME(friend)+".\n",
    			 QCTNAME(actor)+" runs toward " + QTNAME(foe)+
    			 ", forcing "+QTNAME(foe) + " to engage in combat "+
    			 "with "+OBJECTIVE(actor)+" rather than you.\n",
    			 QCTNAME(actor)+" runs toward "+QTNAME(foe)+
    			 ", forcing "+QTNAME(foe)+" to engage in combat "+
    			 "with "+OBJECTIVE(actor)+" rather than "+QTNAME(friend)+".\n",
    			 QCTNAME(actor)+" runs toward you, forcing you to engage "+
    			 "in combat with "+OBJECTIVE(actor)+", rather than "+
    			 QTNAME(friend)+".\n" });
    	break;
    case 3:
    	rescue2 =
    	    ({ "shout out a Solamnic battlecry as you charge "+
    		   "forward, drawing the attention of " + QTNAME(foe)+".\n",
    		   QCTNAME(actor)+" draws the attention of your enemy, "+
    		   QTNAME(foe) + ", as "+PRONOUN(actor)+" charges forward, "+
    		   "shouting out a Solamnic battlecry.\n",
    		   QCTNAME(actor)+" draws the attention of "+QTNAME(foe)+
    		   " as "+PRONOUN(actor)+" charges forward, shouting out a " +
    		   "Solamnic battlecry.\n",
    		   QCTNAME(actor)+" draws your attention as "+PRONOUN(actor)+
    		   " charges forward, shouting out a Solamnic battlecry.\n" });
    	break;
    case 2:
    	rescue2 =
    	    ({ "maneuver so that "+QTNAME(foe)+" is "+
    		   "forced to fight you, and ignore "+QTNAME(friend)+".\n",
    		   QCTNAME(actor)+" maneuvers so that "+QTNAME(foe)+" is "+
    		   "forced to fight "+OBJECTIVE(actor)+", and ignore you.\n",
    		   QCTNAME(actor)+" maneuvers so that "+QTNAME(foe)+" is "+
    		   "forced to fight "+OBJECTIVE(actor)+", and ignore "+
    		   QTNAME(friend)+".\n",
    		   QCTNAME(actor)+" maneuvers so that you are forced to fight "+
    		   "him, and ignore "+QTNAME(friend)+".\n" });
    	break;
    case 1:
    	rescue2 =
    	    ({ "pull "+QTNAME(friend)+" out of harm's way, stepping "+
    		   "forward to take the brunt of "+QTNAME(foe)+"'s "+
    		   "attacks.\n",
    		   "Pulling you out of harm's way, "+QTNAME(actor)+" steps "+
    		   "forward to take the brunt of "+QTNAME(foe)+"'s "+
    		   "attacks.\n",
    		   "Pulling "+QTNAME(friend)+" out of harm's way, "+QTNAME(actor)+
    		   " steps forward to take the brunt of "+QTNAME(foe)+
    		   "'s attacks.\n",
    		   "Pulling "+QTNAME(friend)+" out of harm's way, "+QTNAME(actor)+
    		   " steps forward to take the brunt of your attacks.\n" });
    	break;
    default:
    	rescue2 =
    	    ({ "manage to distract "+QTNAME(foe)+", "+
    		   "enabling "+QTNAME(friend)+" to escape as "+ PRONOUN(foe)+
    		   " turns to attack you.\n",
    		   QCTNAME(foe)+" turns to attack "+QTNAME(actor)+" as "+
    		   QTNAME(actor)+" distracts "+OBJECTIVE(foe)+", allowing "+
    		   "you to escape.\n",
    		   QCTNAME(foe) + " turns to attack "+QTNAME(actor)+" as "+
    		   QTNAME(actor) + " distracts "+OBJECTIVE(foe)+", allowing "+
    		   OBJECTIVE(friend)+" to escape.\n",
    		   "You turn to attack "+QTNAME(actor)+" as "+PRONOUN(actor)+
    		   " distracts you, allowing "+QTNAME(friend)+" to escape.\n" });
    	break;
    }

    actor->attack_object(foe);
    foe->attack_object(actor);
    actor->catch_msg(rescue + rescue2[0]);
    friend->catch_msg(rescue2[1]);
    say(rescue2[2], ({friend, actor, foe}));
    foe->catch_msg(rescue2[3]);
}

static void 
resolve_ability(object actor, mixed * items, 
                mixed * targets, int * resist, mixed * results)
{
    object friend, foe;
    object * foes;
    int j;
    
    if (!sizeof(targets) || !objectp(targets[0]))
    {
        actor->catch_msg("You can't seem to find who you are supposed "
            + "to rescue!\n");
        return;
    }
    
    friend = targets[0];
    foes = items;
    foe = one_of_list(foes);
    
    // First test if the rescue attempt failed or not.
    j = F_RESCUE(TP, foe);
    // If a person cannot see, we modify their rescue by the
    // blindfighting skill
    if (!CAN_SEE_IN_ROOM(actor))
    {
        int blind_skill = actor->query_skill(SS_BLIND_COMBAT);
        j = max(min(5, j), j * blind_skill / 100);
    }    
    if (random(RESCUE_HIT) > random(j))
    {
    	actor->catch_msg("You fail to rescue " + QTNAME(friend) + ".\n");
    	friend->catch_msg(QCTNAME(actor) + " tries to rescue you but fails.\n");
    	say(QCTNAME(actor) + " fails to rescue " + QTNAME(friend) + ".\n",
    	    ({ friend, actor }));
    	return;
    }

    if (sizeof(foes) == 1)
    {
        display_rescue_messages_for_one(actor, friend, foe);
    }
    else
    {
        display_rescue_messages_for_many(actor, friend, foes);
    }    
    
    setuid();
    seteuid(getuid());

    if (!friend->has_knight_rescue_shadow())
    {
        object rescue_ob = clone_object(SPECIALS + "objects/rescue_shadow");
        rescue_ob->shadow_me(friend);
    }
    
    foreach (object foe : foes)
    {
        friend->add_rescue_event(actor, foe);
    }
}

public void
hook_special_complete()
{
}

public void
hook_already_active(object ability)
{
    write("You are already rescuing someone!\n");
}

public void
hook_special_in_cooldown()
{
	write("You are not yet ready to rescue again.\n");
}

/*
 * Function name: check_valid_action
 * Description:   Perform ability-specific checks
 * Arguments:     1. (object) The player
 *                2. (mixed *) The targets
 *                3. (string) Arguments passed to the command
 *                4. (int) Actual spell execution
 * Returns:       (int) 1 if we can continue, 0 if failure
 */
static int 
check_valid_action(object player, mixed * targets, string arg, int execute)
{
    object target;
    object * attackers;
    
    if (!sizeof(targets) || !objectp(targets[0]))
    {
        player->catch_msg("Whom do you wish to rescue?\n");
        return 0;
    }
    
    if (player->query_skill(SS_RESCUE) < 1)
    {
        player->catch_msg("You might want to obtain some training in how "
            + "to rescue others from their opponents first.\n");
        return 0;
    }
    
    target = targets[0];
    if (!CAN_SEE(player, target))
    {
        player->catch_msg("You cannot see well enough to rescue.\n");
	    return 0;
    }

    if (CHARGE_ABILITY->query_ability_preparing(player))
    {
    	player->catch_msg("You are too far away from the battle to rescue "
    	    + QTNAME(target) + "!\n");
    	return 0;
    }

    if (target == player->query_prop(LIVE_O_STEED))
    {
        player->catch_msg("You are mounted on " + QCTNAME(target)
            + " and you are not in a position to rescue your "
            + "steed.\n");
        return 0;
    }

    if (target->query_prop(KNIGHT_I_NO_RESCUE))
    {
    	player->catch_msg(QCTNAME(target) + " may not be rescued.\n");
    	return 0;
    }
    
    attackers = filter(all_inventory(environment(player)),
	    &operator(==)(target) @ &->query_attack());

    if (!sizeof(attackers))
    {
    	player->catch_msg(QCTNAME(target) + " is not under attack.\n");
    	return 0;
    }

    if (IN_ARRAY(player, attackers))
    {
	    player->catch_msg("But you are attacking " + QTNAME(target) + ".\n");
	    return 0;
    }

    attackers = query_attacking_enemies(player, arg);
    if (!sizeof(attackers))
    {
	    player->catch_msg("You find no such foe attacking " +
		    QTNAME(target) + ".\n");
	    return 0;
	}

    return 1;
}

public mixed
parse_input_string(object actor, string str)
{
    int f_index, e_index;
    object friend, enemy;
    mixed * friends, * enemies, * attackers;
    
    parse_command(str, all_inventory(environment(actor)), " %i 'from' %i ",
                  friends, enemies);
    
    friend = 0;
    if (pointerp(friends))
    {
        f_index = friends[0];
        if (f_index < 0)
        {
            if ((f_index * -1) < sizeof(friends))
            {
                friend = friends[f_index * -1];
            }
        }
        else if (f_index == 1)
        {
            friend = friends[1];
        }
    }

    if (!objectp(friend))
    {
        return ({ 0, ({ }) });
    }
            
    enemy = 0;
    attackers = filter(all_inventory(environment(actor)),
	    &operator(==)(friend) @ &->query_attack());
    if (pointerp(enemies))
    {
        e_index = enemies[0];
        if (e_index < 0)
        {
            if ((e_index * -1) < sizeof(enemies))
            {
                enemy = enemies[e_index * -1];
            }
        }
        else if (e_index == 1)
        {
            enemy = enemies[1];
        }
        
        if (objectp(enemy))
        {
            if (!IN_ARRAY(enemy, attackers))
            {
                enemy = 0;
            }
        }
    }
    
    if (parse_command(str, environment(actor), " %i 'from' 'all' ",
                  friends)
        && actor->query_knight_level() == L_ROSE)
    {
        return ({ friend, attackers });
    }
    
    if (!objectp(enemy))
    {
        return ({ friend, ({ one_of_list(attackers) }) });
    }
    
    return ({ friend, ({ enemy }) });
}

public object *
target_friend_for_rescue(object actor, string str)
{
    object friend, enemy;
    object * enemies;

    if (!str)
    {
        actor->catch_tell("Rescue who?\n");
        return 0;
    }
    
    parse_command(str, environment(actor), " %o 'from' %o ",
                      friend, enemy);                              	    	

    if (objectp(friend))
    {
        return ({ friend });
    }
    
    return target_one_other_present_living_or_enemy(actor, str);
}

public object *
query_attacking_enemies(object actor, string str)
{
    // Rescue can take the form of:
    //   rescue friend from enemy
    //     - rescues the friend from a specific enemy attacking
    //   rescue friend
    //     - rescues the friend from the first enemy attacking
    //       (non-Rose Knights)
    //     - rescues the friend from all his attacking enemies
    //       (Rose Knights Only)
    
    mixed  parse_output;
    object friend, enemy;
    object * enemies, * chosen_enemies;
    	    	
    parse_output = parse_input_string(actor, str);
    friend = parse_output[0];
    chosen_enemies = parse_output[1];
    if (!objectp(friend))
    {
        return ({ });
    }
    
    return chosen_enemies;
}
