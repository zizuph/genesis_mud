/*
  This adventurer's looking for some objects and gives experience.
*/

inherit "/std/monster";

#include <macros.h>
#include <language.h>
#include <stdproperties.h>
#include <ss_types.h>

#include "monsters.h"
#include "indy.h"

/* prototypes */
int query_quest_number(object player);
void increase_questlevel(object player, int questnumber);
void reset_quest(int number);

/*
 * Function name: create_monster
 * Description:   creates the monster (what else?)
 * Arguments:     none
 * Returns:       nothing
 */

create_monster()
{
  set_name("indy");
  set_race_name("adventurer");
  set_living_name("indy");
  set_adj("old");
  set_long(BS("He is one of the adventurer that couldn't stop going "
    + "for it. Now he's old and still looks for some items. "
    + "Maybe you <ask> him what he's looking for. If you think you "
    + "have the object he's looking for you can <show> it to him. \n"));
  default_config_npc(100);
  set_skill(SS_UNARM_COMBAT,100);
  set_skill(SS_DEFENCE,100);
  set_alignment(500);
  add_prop(LIVE_I_ALWAYSKNOWN, 1);
}

/*****************************************************************************/

/*
 * Function name: init_living
 * Description:   add some commands to the player
 * Arguments:     none
 * Returns:       nothing
 */

void
init_living()
{
  add_action("show", "show");
  add_action("ask", "ask");
}

/*****************************************************************************/

/*
 * Function name: show
 * Description:   tests if the object 'what' is the thing Indy's looking for 
 * Arguments:     what the player shows
 * Returns:       0/1
 */

int
show(string what)
{
  object  item;
  int     quest_number;   	   /* quest number the player should work on */

  NF("Show what?\n");
  if(!what) 
    return 0;

  if(!parse_command(what, TP, "%o", item))
    return 0;

  quest_number = query_quest_number(TP);

  if ((quest_number > LAST_QUEST) ||
      (OBJECT(quest_objects[quest_number]) != MASTER_OB(item)))
  {
    command("say I have no use for this at the moment.");
    return 1;
  }

  write(BS("As you show " + LANG_THESHORT(item) + " to Indy he "
    + "suddenly gets shiny eyes and grabs it. He thanks you "
    + "and you feel more experienced.\n"));
  say(QCTNAME(TP) + " does some business with " + QTNAME(TO) + ".\n", TP);
  item->remove_object();

  TP->add_exp(quest_points[quest_number]);
  increase_questlevel(TP,quest_number);
  reset_quest(quest_number);
  
  return 1;
}

/*****************************************************************************/

/*
 * Function name: ask
 * Description:   Tells the player what Indy's looking for 
 * Arguments:     none
 * Returns:       0/1
 */

int
ask()
{
  object  item;
  int     quest_number;   	/* quest number the player should work on */

  quest_number = query_quest_number(TP);

  say(QCTNAME(TP) + " asks " + QTNAME(TO) + " what he can do for him.\n", TP);

  if(quest_number > LAST_QUEST)
    command("say I'm looking for nothing special at the moment.");
  else
    command(commands[quest_number]);
  return 1;
}

/*****************************************************************************/

/*
 * Function name: query_quest_number
 * Description:   Decides the number of the quest the player's working on
 * Arguments:     The player who's tested
 * Returns:       the number
 */

int
query_quest_number(object player)
{
  int number;
    
  number = player->test_bit(DOMAIN, GROUP, BIT0);
  number += 2 * (player->test_bit(DOMAIN, GROUP, BIT1));
  number += 4 * (player->test_bit(DOMAIN, GROUP, BIT2));
  return number;
}

/*****************************************************************************/

/*
 * Function name: increase_questlevel
 * Description:   sets the bits of the player
 * Arguments:     player, actual questnumber
 * Returns:       nothing
 */

void
increase_questlevel(object player, int questnumber)
{
  ++questnumber;

  if (questnumber & 01)
    player->set_bit(GROUP,BIT0);
  else
    player->clear_bit(GROUP,BIT0);

  if (questnumber & 02)
    player->set_bit(GROUP,BIT1);
  else
    player->clear_bit(GROUP,BIT1);

  if (questnumber & 04)
    player->set_bit(GROUP,BIT2);
  else
    player->clear_bit(GROUP,BIT2);

  return;
}


/*****************************************************************************/

/*
 * Function name: reset_quest
 * Description:   resets the done quest
 * Arguments:     number of quest to reset
 * Returns:       none
 */

void
reset_quest(int number)
{
  switch(number)
  {
    case 0:
      ROOM("top")->reset();
      break;
    case 1:
      break;
    case 2:
      break;
    case 3:
      break;
    case 4:
      break;
    case 5:
      break;
    case 6:
      break;
    default:
      break;
  }
}
