/* This file is included in the guild shadow.  It contains the code
 * for the guild's special attack.  We keep it in a separate file to
 * keep from cluttering the shadow and for easier debugging.
 *
 * Modified by Blizzard:
 * 25.08.2003 - Changed the chop prepare time (now random)
 * 1.10.2003  - Dis check only if we are not already fighting the target.
 * 
 * 2008 Sept - Louie - Recoded to make use of new specials library.
 */

#include <stdproperties.h>
#include <formulas.h>
#include <macros.h>
#include <ss_types.h>
#include <wa_types.h>
#include "/d/Ansalon/common/defs.h"
#include "racial_enemies.h"
#include "guild.h"

inherit "/d/Genesis/specials/std/damage.c";

#define AXEWIELDR query_weapon(W_RIGHT)->query_wt() == W_AXE
#define AXEWIELDL query_weapon(W_LEFT)->query_wt() == W_AXE
#define AXEWIELDB query_weapon(W_BOTH)->query_wt() == W_AXE

static private int chop_alarm = 0;
static private int preparing_chop = 0;
public object find_best_neidar_weapon(object player);

/*
 * Check if the enemy is a racial enemy (from racial_enemies.h)
 */
public int
is_racial_enemy(object enemy)
{
  if (!enemy)
  {
    return 0;
  }

  int x = member_array(enemy->query_race(), NEIDAR_RACIAL_ENEMIES);
  int y = member_array(enemy->query_race_name(), NEIDAR_RACIAL_ENEMIES);

  if (x > -1 || y > -1)
  {
    return 1;
  }
  return 0;
}

/*
 * Function name: config_ability
 * Description  : Main fuction that configures what the special
 *                should look like. Set basic things like combat
 *                aid and the skills to be used for calculating
 *                damage and of course, the name.
 * Arguments    : none
 * Returns      : nothing
 */
public void 
config_ability()
{
  ::config_ability();
  // Maximum combat aid is in guild.h
  set_combat_aid(CHOP_AID);
    
  // Dwarves have bonus on both str and dis
  set_stats( ({ SS_STR, SS_DIS }) );
  set_skills( ({ SS_GUILD_SPECIAL_SKILL }) );

  // 20 sec per ability, dwarves are strong but slow.
  // So specials a little on the slower side.
  set_ability_prep_time(10);
  set_ability_cooldown_time(10);
  set_guild_stat_modifier(SS_OCCUP, 20, 100);
  set_dt(W_SLASH); //This will change based on weapon
  set_ability_name("chop");
}

/*
 * Function name: special_did_hit
 * Description  : Mask this function to process when the special
 *                scores. Descriptions seen by everyone are set
 *                here.
 * Arguments    : aid   - attack id
 *                hdesc - hit description
 *                hid   - 
 *                phurt - extent of damage
 *                enemy - person being hit by special
 *                dt    - damage type
 *                phit  - 
 *                dam   - damage amount
 * Returns      : nothing
 */
public void special_did_hit(int aid,
			    string hdesc,
			    int hid, 
			    int phurt,
			    object enemy,
			    int dt,
			    int phit, 
			    int dam)
{
  object attacker = this_player();
  string weapon, wdtype, watype;
  string *attack_message;
  object wep;
  int wielding_axe;
    
  //Check what we're wielding
  wep = find_best_neidar_weapon(attacker);
  
  //Is it even possible we'd lose our weapon between applying damage
  //and displaying these messages?
  if (!wep)
  {
    attacker->catch_msg("You applied damage but don't appear to have "+
			"an axe or club! Please report this.\n");
    return;
  }
    
  weapon = wep->short();
  
  if (wep->query_wt == W_AXE)
  {
    wielding_axe = 1;
  }

  //big miss.  Miss of exactly 0 handled below this.
  if (dam < 0)
  {
    /* message to attacker */
    attacker->catch_msg("You swing your " +weapon+ " at "+
			QTNAME(enemy)+ " but miss by a mile.\n");
    
    if (interactive(enemy)) 
    {
      /* message to target */
      enemy->catch_msg(QCTNAME(attacker) + " swings at you with "
		       +HIS(attacker)+ " " +weapon+ " but misses by a mile.\n");
    }                            
    /* message to onlookers */
    attacker->tell_watcher(QCTNAME(attacker) + " swings at " +
			   QTNAME(enemy)+ " but misses by a mile.\n", enemy);
    return;
  }

  switch (phurt)
  {
    case 0:
      attack_message = ({
	      "You curse foully in dwarven as your wild swing " +
	      "with your " +weapon+ " at " +enemy->query_the_name(attacker)+
	      " just misses.\n",
	      attacker->query_The_name(enemy)+ " curses foully in dwarven " +
	      "as " +HIS(attacker)+ " wild swing just misses you.\n",
	      QCTNAME(attacker)+ " curses foully in dwarven as " +
	      HIS(attacker)+ " wild swing at " +QTNAME(enemy) + 
	      " just misses.\n"
	    });
      break;
    case 1..2:
      attack_message = ({
	      "You strike out wildly with your " +weapon+ ", just " +
	      "grazing " +enemy->query_the_name(attacker)+
	      "'s " +hdesc+ ".\n",
	      attacker->query_The_name(enemy)+ " strikes out wildly " +
	      "at you with " +HIS(attacker)+ " " +weapon+ ", just grazing " +
	      "your " +hdesc + ".\n",
	      QCTNAME(attacker)+ " strikes out wildly at " +QTNAME(enemy)+
	      "with " +HIS(attacker)+ " " +weapon+ ", just grazing " +
	      QTNAME(enemy)+ "'s " +hdesc+ ".\n"
	    });
      break;
    case 3..5:
      if(wielding_axe)
      {
	wdtype = "slicing a minor flesh wound";
      }
      else
      {
	wdtype = "bruising it moderately";
      }
      attack_message = ({
	      "You grin fiercely as you bring your " +weapon+
	      " down upon " +enemy->query_the_name(attacker)+ "'s " +
	      hdesc+ ", " +wdtype+ ".\n",
	      attacker->query_The_name(enemy)+ " grins fiercely as " +HE(attacker)+
	      " brings " +HIS(attacker)+ " " +weapon+ " down upon your " +hdesc+
	      ", " +wdtype+ ".\n",
	      QCTNAME(attacker)+ " grins fiercely as " +HE(attacker)+ " brings " +
	      HIS(attacker)+ " " +weapon+ " down upon " +QTNAME(enemy)+ "'s " +hdesc+
	      ", " +wdtype+ ".\n"
	    });              
      break;
    case 6..10:
      attack_message = ({
	      "You swing furiously at " +enemy->query_the_name(attacker)+ ", " +
	      "slamming the face of your " +weapon+ " into " +
	      enemy->query_the_name(attacker)+ "'s " +hdesc+ ".\n",
	      attacker->query_The_name(enemy)+ " swings furiously at you, slamming " +
	      "the face of " +HIS(attacker)+ " " +weapon+ " into your " +hdesc+ ".\n",
	      QCTNAME(attacker)+ " swings furiously at " +QTNAME(enemy)+ ", " +
	      "slamming the face of " +HIS(attacker)+ " " +weapon+ " into " +QTNAME(enemy)+ "'s " +
	      hdesc + ".\n"
	    });
      break;
    case 11..20:
      if(wielding_axe)
      {
	watype = "chop";
	wdtype = "slashing a nasty wound";
      }
      else
      {
	watype = "slam";
	wdtype = "striking a painful blow";
      }
      attack_message = ({
	      "You " +watype+ " down mightily upon " +enemy->query_the_name(attacker)+
	      "'s " +hdesc+ " with your " +weapon+ ", " +wdtype+ ".\n",
	      attacker->query_The_name(enemy)+ " " +watype+ "s down mightily upon " +
	      "your " +hdesc+ " with " +HIS(attacker)+ " " +weapon+ ", " +wdtype+ ".\n",
	      QCTNAME(attacker)+ " " +watype+ "s down mightily upon " +QTNAME(enemy)+
	      "'s " +hdesc+ " with " +HIS(attacker)+ " " +weapon+ ", " +wdtype+ ".\n"
	    });
      break;
    case 21..30:
      if(wielding_axe)
      {
	watype = "slice a deep wound upon";
	wdtype = "slices a deep wound upon";
      }
      else
      {
	watype = "smash";
	wdtype = "smashes";
      }
      attack_message = ({
	      "You roar gleefully as you " +watype+ " " +
	      enemy->query_the_name(attacker)+ "'s " +hdesc+ " with your " +
	      weapon + ".\n",
	      attacker->query_The_name(enemy)+ " roars gleefully as " +
	      HE(attacker)+ " " +wdtype+ " your " +hdesc+ " with " +
	      HIS(attacker)+ " " +weapon+ ".\n",
	      QCTNAME(attacker)+ " roars gleefully as " +HE(attacker)+ " " +
	      wdtype+ " " +QTNAME(enemy)+ "'s " +hdesc+ " with " +
	      HIS(attacker)+ " " +weapon+ ".\n"
	    });
      break;
    case 31..50:
      if(wielding_axe)
      {
	wdtype = "burying it deeply in";
      }
      else
      {
	wdtype = "smashing it powerfully upon";
      }
      attack_message = ({
	      "You swing your " +weapon+ " in a deadly arc, " +
	      wdtype+ " " +enemy->query_the_name(attacker)+ "'s " +hdesc+
	      ".\n",
	      attacker->query_The_name(enemy)+ " swings " +HIS(attacker)+
	      " " +weapon+ " in a deadly arc, " +wdtype+ " your " +
	      hdesc+ ".\n",
	      QCTNAME(attacker)+ " swings " +HIS(attacker)+ " " +weapon+
	      " in a deadly arc, " +wdtype+ " " +QTNAME(enemy)+ "'s " +
	      hdesc+ ".\n"
	    });
      break;
    case 51..75:
      if(wielding_axe)
      {
	wdtype = "tearing a great wound in";
      }
      else
      {
	wdtype = "gleefully pulping";
      }
      attack_message = ({
	      "You launch yourself into the air, bringing your " +weapon+ 
	      " down powerfully upon " +enemy->query_the_name(attacker)+
	      ", " +wdtype+ " " +HIS(enemy)+ " " +hdesc+ ".\n",
	      attacker->query_The_name(enemy)+ " launches " +HIM(attacker)+
	      "self into the air, bringing " +HIS(attacker)+ " " +weapon+
	      " powerfully down upon you, " +wdtype+ " your " +hdesc+ ".\n",
	      QCTNAME(attacker)+ " launches " +HIM(attacker)+ "self into " +
	      "the air, bringing " +HIS(attacker)+ " " +weapon+
	      " powerfully down upon " +QTNAME(enemy)+ ", " +wdtype+ " " +
	      HIS(enemy)+ " " +hdesc+ ".\n"
	    });
      break;
    case 76..99:
      if(wielding_axe)
      {
	wdtype = "rips to shreads";
      }
      else
      {
	wdtype = "pulverises";
      }
      attack_message = ({
	      "You begin to sing a dwarven warsong of victory, as your blow " +
	      "with the " +weapon+ " " +wdtype+ " " +
	      enemy->query_the_name(attacker)+ "'s " +hdesc+ ", splattering " +
	      "blood everywhere.\n",
	      attacker->query_The_name(enemy)+ " begins to sing a dwarven " +
	      "warsong of victory, as " +HIS(attacker)+ " blow with the " +
	      weapon + " " +wdtype+ " your " +hdesc+ ", splattering blood " +
	      "everywhere.\n",
	      QCTNAME(attacker)+ " begins to sing a dwarven warsong of victory, " +
	      "as " +HIS(attacker)+ " blow with the " +weapon+ " " +wdtype+ " " +
	      QTNAME(enemy)+ "'s " +hdesc+ ", splattering blood everywhere.\n"
	    });
      break;
    default:
      attack_message = ({
	      "You roar in victory as you deal a mortal wound to " +
	      enemy->query_the_name(attacker)+ " with your " +weapon+ ".\n",
	      attacker->query_The_name(enemy)+ " roars in victory as " +
	      HE(attacker)+ " deals you a mortal wound with " +HIS(attacker)+
	      " " +weapon+ ".\n",
	      QCTNAME(attacker)+ " roars in victory as " +HE(attacker)+
	      " deals " +QTNAME(enemy)+ " a mortal wound with " +HIS(attacker)+
	      " " +weapon+ ".\n"
	    });
      break;
  }

  if (is_racial_enemy(enemy))
  {
    attacker->catch_msg("Your racial hatred of " +QTNAME(enemy)+
			" gives you renewed strength!\n");
    attacker->tell_watcher(QCTNAME(attacker)+ "'s eyes seem to blaze " +
			   "with pure hatred!\n");
  }

  //Tell the messages
  attacker->catch_tell(attack_message[0]);
  enemy->catch_tell(attack_message[1]);
  attacker->tell_watcher(attack_message[2], enemy);

  if (enemy->query_hp() <= 0)
  {
    enemy->do_die(attacker);
  }
}

/*
 * Filter valid chop weapons
 */
int filter_neidar_weapons(object ob)
{
  if (!ob)
  {
    return 0;
  }

  if (!ob->check_weapon())
  {
    return 0;
  }

  int i = ob->query_wt();

  if (i == W_AXE || i == W_CLUB)
  {
    return 1;
  }
  return 0;
}

/*
 * Find the best neidar weapon for a player
 */
public object 
find_best_neidar_weapon(object player)
{
  object best;
  mixed *weapons = player->query_weapon(-1);

  if (!sizeof(weapons))
  {
    return 0;
  }

  weapons = filter(weapons, filter_neidar_weapons);
  
  if (!sizeof(weapons))
  {
    return 0;
  }
  
  foreach (object ob : weapons)
  {
    if (!best)
    {
      best = ob;
      continue;
    }
    
    if (ob->query_pen() > best->query_pen())
    {
      best = ob;
    }
  }
  return best;
}

/*
 * Function name: check_required_items
 * Description  : Look for an axe or club
 * Returns      : items that are required.
 */
static mixed * 
check_required_items(object actor,
		     mixed * targets,
                     string arg,
		     int pretest)
{
  //Must have a axe/club
  object weapon = find_best_neidar_weapon(actor);
  
  if (weapon)
  {
    return ({ weapon });
  }
  return 0;
}

/**
 * Function     :   check_neidar_requirements
 * Description  :   Checks that the special can fire
 * Arguments    :   Player executing special
 * Returns      :   1 if ok, 0 if fail
 */
public int
check_neidar_requirements(object player) 
{
  object ob = find_best_neidar_weapon(player);

  if (!ob)
  {
    player->catch_tell("You are not wielding a proper weapon!\n");
    return 0;
  }
  //Passed requirements
  return 1;
}

/*
 * Function name: apply_costs_to_player
 * Description  : By default, a small fatigue cost is applied
 *                for the special. Other costs can be applied
 *                as well by a masked function.
 *                Neidar have no fatigue penalty for using their special.
 * Arguments    : player - player executing the special
 * Returns      : nothing
 */
public void
apply_costs_to_player(object player) 
{
    //Neidar have no fatigue cost
}

public void hook_special_complete()
{
  object who = this_player();
  if(who->AXEWIELDR || who->AXEWIELDL || who->AXEWIELDB)
  {
    who->catch_tell("You feel ready to chop again.\n");
  }
  else
  {
    who->catch_tell("You feel ready to crush your foes again.\n");
  }
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
  if (!check_neidar_requirements(player))
  {
    return 0;
  }
  return 1;
}

/*
 * Function name: force_fail
 * Description:   This function allows the special to force a failure for
 *                whatever reason. Called right before execution at the end
 *                of the delay
 * Arguments:     1. (object)   The player
 *                2. (object) The targets
 *                3. (int *)    Resistance values corresponding to each target
 *                4. (int)      The attempt result as returned by
 *                              query_casting_success()
 * Returns:       1 for failure, 0 for not.
 */
public int 
force_fail(object player,
	   mixed * items,
	   object enemy, 
           int resist,
	   int result)
{
  if (!check_neidar_requirements(player))
  {
    return 1;
  }
  return 0;
}

/*
 * 100 is used for racial enemies.
 * 90 is used for normal.
 * Function name: query_combat_aid_modifier
 * Description  : Calculates the percentage of the maximum
 *                combat aid that applies to the current situation
 * Arguments    : player - player executing special
 * Returns      : number between 1 and 100
 */
public int 
query_combat_aid_modifier()
{
  int aid;
  object enemy = TP->query_attack();
  
  if(enemy && is_racial_enemy(enemy))
  {
    aid = 100;
  }
  else
  {
    aid = 90;
  }
  return aid;
}
