/*
 * Neidar Shield Mastery (shield block)
 * 
 * Neidar gain a 10% combat aid evade ('block') bonus
 * when using a shield.
 * 
 * They may give this aid to someone else, in which case
 * at max 2 bonuses will be applied.
 *
 * Used Calian swarm evade by Petros as a model.
 *
 * Louie Oct 2008
 *
 */
 
#pragma strict_types

#include "/d/Genesis/specials/defs.h"

inherit EVADE_OBJ_BASE;

#include "/d/Ansalon/common/defs.h"
#include "guild.h"

#include <stdproperties.h>
#include <wa_types.h>
#include <macros.h>
#include <ss_types.h>
#include <tasks.h>
#include <formulas.h>
#include <filter_funs.h>

#include DEBUGGER_TELL

private int create_time;
private int shield_position;

/*
 * Function     : is_neidar_shield
 * Description  : Is this a neidar shield block obj
 * Arguments    : none
 * Returns      : 1 - always returns true
 */
public int
is_neidar_shield()
{
  return 1;
}

/*
 * Description  : Function to use in a filter() command to filter these objects.
 * Arguments    : Object to check if it is a shield object
 * Returns      : 0/1 - not shield/is shield
 */
public int
filter_neidar_shield(object ob) 
{
  if (!ob || !ob->is_neidar_shield())
  {
    return 0;
  }
  return 1;
}

/*
 * Description  :  Sort the shield objects in descending power.
 *                 Equal objects will be sorted by create_time, which
 *                 should be unique.
 * Arguments    :  *shield_objects:  array of shield objects
 *                 player:  player being attacked (this player)
 *                 attacker:  object attacking player
 *                 attack_id:  attack_id
 * Returns      :  Array of the two best shield objects in order
 *                  ({ best_shield, second_shield })
 */
public mixed
sort_shield_objects(object* shield_objects,
                    object player, 
                    object attacker,
                    int attack_id)
{
  object best_shield, second_shield;

  //Spin through the shield objects to get the top 2.
  foreach (object shield: shield_objects)
  {
    //First check if we're the best shield
    if (!best_shield)
    {
      best_shield = shield;
      continue;
    }

    int s1 = best_shield->query_basic_evade_strength(player,
						     attacker,
						     attack_id);

    int current = shield->query_basic_evade_strength(player,
						     attacker,
						     attack_id);
    if (current > s1)
    {
      second_shield = best_shield;
      best_shield = shield;
      continue;
    }
    
    if (current == s1)
    {
      if (shield->query_create_time() < best_shield->query_create_time())
      {
	second_shield = best_shield;
	best_shield = shield;
	continue;
      }
    }

    //Current isn't the best shield, see if it can be second best
    if (!second_shield)
    {
      second_shield = shield;
      continue;
    }

    int s2 = second_shield->query_basic_evade_strength(player,
						       attacker,
						       attack_id);
    if (current > s2)
    {
      second_shield = shield;
      continue;
    }

    if (current == s2 &&
        shield->query_create_time() < second_shield->query_create_time())
    {
      second_shield = shield;
      continue;
    }
  }
  return ({ best_shield, second_shield });
}

/*
 * Function     : create_effect
 * Description  : The create function called for objects that inherit this
 * Arguments    : none
 * Returns      : nothing
 */
public void
create_effect()
{    
  set_name("_neidar_shield_object_");
  add_name( ({"neidar_shield_object" }) );
  set_short("hidden neidar shield (evade) object");    
  set_long("The object that grants shield blocking (evade) to "+
           "Neidars or their protected target.  This " +
           "should not be visible by players.\n");
  
  setuid();
  seteuid(getuid());
  
  set_evade_stats( TS_STR );
  set_evade_skills( SLAM_SPECIAL_SKILL );
  set_evade_combat_aid(SHIELD_BLOCK_AID);
}                           

/*
 * Function     : remove_neidar_shield_object
 * Description  : Destructor function.
 * Arguments    : none
 * Returns      : nothing
 */
public void
remove_neidar_shield_object()
{
  remove_object();
}

/*
 * Description  : The time() this object was created.  Should be unique.
 * Returns      : The result of time() when created.
 */
public int
query_create_time()
{
  return create_time;
}

/*
 * Description  : Sets the create time for this object. Should be a unique int.
 */
public void
set_create_time(int i)
{
  create_time = i;
}

/* 
 * Description  : Request the base (unmodified) strength of this
 *                  object.  Used when comparing objects to see
 *                  which is the best
 * Arguements   : Same as normal query_evade_strength  
 *                  (player, attacker, attack_id)
 * Returns      : int (evade strength)
 */
public int
query_basic_evade_strength(object player, object attacker, int attack_id)
{
    return ::query_evade_strength(player, attacker, attack_id);
}

/*
 * Description  : Finds a shield (random if there's 2).
 * Arguments    : A player
 * Returns      : The first shield we find (doesn't matter which).
 */
public object
find_shield(object player) 
{
  object shd1 = player->query_armour(TS_RWEAPON), 
         shd2 = player->query_armour(TS_LWEAPON);

  mixed *shields = ({});
  
  if (shd1 && shd1->query_at(A_SHIELD))
  {
    shields += ({shd1});
  }
  
  if (shd2 && shd2->query_at(A_SHIELD))
  {
    shields += ({shd2});
  }
  
  if (sizeof(shields))
  {
    return shields[random(sizeof(shields))];
  }
  return 0;
}

/*
 * Description  : Some basic checks for validity that do not depend
 *                  on a comparison across objects.
 * Arguments    : (same as normal query_evade_valid from base evade)
 *                player    - player who is being attacked
 *                attacker  - the person doing the attacking
 *                attack_id - attack id location
 * Returns      : 0/1 - invalid/valid
 */
public int
query_basic_evade_valid(object player, object attacker, int attack_id)
{
  object defender;

  defender = query_effect_caster();
  
  if (!defender)
  {
    send_debug_message("neidar_shield", "Defender is no longer valid, " +
		       "maybe from quitting.");
    set_alarm(0.1, 0.0, &remove_neidar_shield_object());
    return 0;
  }

  if (environment(defender) != environment(player))
  {
    send_debug_message("neidar_shield", "Defender not valid: " +
		       "not in room.");
    return 0;
  }

  //Defender must have a shield
  if (!find_shield(defender)) 
  {
    send_debug_message("neidar_shield", "Defender is not wearing a " +
		       "shield.");
    return 0;
  }

  if (!CAN_SEE_IN_ROOM(defender)) 
  {
    send_debug_message("neidar_shield", "Defender not valid: "+
		       "cannot see in room.");
    return 0;
  }

  //The Neidar does not need to see the attacker, since he is
  //covering the defendee with his shield regardless.
  //He just needs to see the defendee.
  if (!CAN_SEE(defender, player))
  {
    send_debug_message("neidar_shield", "Defender not valid: "+
		       "cannot see player/defendee.");
    return 0;
  }

  if (defender->query_shield_master_target() != player)
  {
    send_debug_message("neidar_shield", "Defender not valid: "+
		       "defender has changed shield target.");
    set_alarm(0.1, 0.0, &remove_neidar_shield_object());
    return 0;
  }
  return 1;
}

/*
 * Function     : query_evade_valid
 * Description  : Validation function to see whether this evade object is
 *                valid in the current situation
 * Arguments    : player    - player who is being attacked
 *                attacker  - the person doing the attacking
 *                attack_id - attack id location
 * Returns      : 0/1 - invalid/valid
 */
public int
query_evade_valid(object player, object attacker, int attack_id)
{ 
  //Neidar shield blocking requires:
  //- Blocker (Neidar) be in the room
  //- Blocker (Neidar) has a shield
  //- Blocker (Neidar) can see player/defendee
  //- Blocker (Neidar) must still be defending the player
  //
  //These things are checked by query_basic_evade_valid(...)
  //
  //Also, only 2 blocks will be effective.  Any remaining
  //objects will not be valid (but can still exist).  So
  //we may have more than 2 neidar shield objects, but only
  //the 'best' 2 are used.
  //
  //We do this by first finding all valid shield blocks
  //(as filtered out by query_basic_evade_valid())
  //and then taking the best 2.  If there are more than
  //2, we sort by the create_time (first come first serve).
  object *shield_objects;
  
  //Reset our position to 0 (not valid).  We'll set it at the
  //end if we're one of the top 2.
  shield_position = 0;
  
  //First check if we're even valid
  if (!query_basic_evade_valid(player, attacker, attack_id))
  {
    return 0;
  }
  
  shield_objects = filter(player->query_evade_effects(), filter_neidar_shield);

  //If we're the only object, we're good
  //Second half of this check should always be true in this scenario,
  //but just in case...
  if (1 == sizeof(shield_objects) && shield_objects[0] == this_object())
  {
    shield_position = 1;
    return 1;
  }

  //Since there is more than one, determine if we're in the top 2
  shield_objects = sort_shield_objects(shield_objects,
				       player,
				       attacker,
				       attack_id);

  //If we're in the top two, we're valid
  if (shield_objects[0] == this_object())
  {
    shield_position = 1;
    return 1;
  }
  else if (shield_objects[1] == this_object())
  {
    shield_position = 2;
    return 1;
  }
  return 0;
}

/*
 * Function     : query_evade_strength
 * Description  : Function that will be used to gauge the strength of
 *                the evade based on the situation. 
 * Arguments    : player    - player who is being attacked
 *                attacker  - the person doing the attacking
 *                attack_id - attack id location
 * Returns      : the modified value of the evasion percentage
 */
public int
query_evade_strength(object player, object attacker, int attack_id)
{
  int strength;
  
  strength = ::query_evade_strength(player, attacker, attack_id);

  //Ok, so if we've gotten this far, we know we're one of the
  //top 2 shield objects.  If we're #2, we cap the combat aid at half
  //combat aid (not the strength!).  To do this we use the formula
  // evade = (100 * caid) / (100 + caid)
  //This is because evade strength is not the same thing as combat aid.
  if (shield_position == 2) 
  {
    int max_strength = (100 * SHIELD_MASTER_AID / 2) /
                       (100 + SHIELD_MASTER_AID / 2);
    
    if (strength > max_strength) 
    {
      strength = max_strength;
    }
  }
  send_debug_message("neidar_shield", "Neidar shield (evade) strength: " +
		     strength);
  return strength;
}   

/*
 * Function     : attack_blocked
 * Description  : Function to display messages that the attack was
 *                blocked.
 * Arguments    : player    - player who is being attacked
 *                attacker  - the person doing the attacking
 *                attack_id - attack id location
 * Returns      : nothing
 */
public void
attack_blocked(object player, object attacker, int attack_id)
{
  object defender;
  object * exclude_list;
  string defender_desc, player_desc, attacker_desc, watcher_desc;
    
  defender = query_effect_caster();
  object shield = find_shield(defender);

  exclude_list = ({ player, attacker });
    
  if (player == defender)
  {
    defender_desc = "";

    // The evade comes from the player himself.
    switch (random(2))
    {
      case 1:
	player_desc   = "You raise your "+shield->short()+
	                " and block "+QTNAME(attacker)+"'s "+
	                "attack.";
	attacker_desc = "You swing at "+QTNAME(player)+
                        " but "+player->query_pronoun()+
                        " raises "+player->query_possessive()+
                        " "+shield->short()+" and blocks your "+
                        "attack.";
	watcher_desc  = QCTNAME(attacker) + " swings at " +
                        QTNAME(player) + ", but the attack is blocked "+
                        "as "+QTNAME(player)+" quickly raises "+
                        player->query_possessive() + " " +
                        shield->short()+".";
	break;
            
      case 0:
      default:
	player_desc   = "You duck behind your "+shield->short()+
                        " to avoid "+QTNAME(attacker)+"'s "+
                        "swing.";

	attacker_desc = "Your attack on " + QTNAME(player) + 
                        " bounces off "+player->query_possessive()+
                        " "+shield->short()+
                        " as "+player->query_pronoun()+" ducks behind "+
                        "it.";

	watcher_desc = QCTNAME(attacker) + "'s attack "+
                       "is deflected by "+QTNAME(player)+"'s "+
                       shield->short()+" as "+
                       player->query_pronoun()+" ducks behind it.";
    }
  }
  else
  {
    exclude_list += ({ defender });

    //A different Neidar is doing the block
    player_desc = QCTNAME(attacker)+" swings at you, but "+
                  QTNAME(defender)+" quickly raises "+
                  defender->query_possessive()+" "+shield->short()+
                  " and blocks the attack.";

    attacker_desc = "You swing at " + QTNAME(player) + " but "+
                    QTNAME(defender)+" raises "+
                    defender->query_possessive()+" "+shield->short()+
                    " and blocks the attack.";

    watcher_desc = QCTNAME(attacker) + " swings at "+
                   QTNAME(player) + ", but "+
                   QTNAME(defender)+" quickly raises "+
                   defender->query_possessive()+" "+shield->short()+
                   " and blocks the attack.";
    defender_desc = QCTNAME(attacker)+" swings at "+QTNAME(player)+
	            ", but you quickly raise your "+
                    shield->short()+" and block the attack.";
  }
  
  player->catch_msg(player_desc + "\n");
  attacker->catch_msg(attacker_desc + "\n");
  player->tell_watcher(watcher_desc + "\n", attacker, exclude_list);

  if (strlen(defender_desc))
  {
    defender->catch_msg(defender_desc + "\n");
  }
}
