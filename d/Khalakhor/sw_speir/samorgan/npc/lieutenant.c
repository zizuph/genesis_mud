/* SaMorgan village guard lieutenant
 * Tapakah, 04/2021
 */

#pragma strict_types

#include <money.h>
#include "../defs.h"
#include "../quests.h"

inherit SM_WARRIOR;
inherit "/d/Khalakhor/common/npc/quest-npc";

#define TOWERS 4
// Sergeant included, courier is not
#define GUARDS_IN_TOWER 4

void
check_task ()
{
  setuid(); seteuid(getuid());
  if (TP->test_bit(domain,
                   SAMORGAN_QUEST_GROUP,
                   SAMORGAN_QUEST_FEED_GUARDS_BIT))
    command("say I don't have any tasks left for you at the moment.");
  else 
    if (TP->query_prop(QUEST_M_GUARD_MENU_LIST))
      command("say Have you checked with the sergeants, as I asked you?");
    else {
      command("say We have been forced to run longer guard shifts than usual.");
      command("say Please check with the sergeants in each guard tower and " +
            "help them with getting some food for the guards. When you're "+
            "done, you can come here for a reward.");
      log_quest(SAMORGAN_QUEST_FEED_GUARDS_BIT,
                TPQN, "Started quest");
      TP->add_prop(QUEST_M_GUARD_MENU_LIST, ([]));
    }    
}

int
check_complete (mapping guard_order)
{
  int t = 0, t_o = 0, o = 0;
  foreach (string tower, mapping tower_order: guard_order) {
    foreach (string guard, mapping order: tower_order)
      foreach (string item, int have_it: order)
        t_o += have_it;
    t++;
  }
  if (t < TOWERS*2) {
    command("say You haven't been to all the towers yet!");
    return 0;
  }
  if (t_o < TOWERS*GUARDS_IN_TOWER*2) {
    command("say You haven't provided to all the guards yet!");
    return 0;
  }
  return 1;
}

void
extra_reward ()
{
  command("say Thanks! You've been a great help! Our guards "+
          "will be able to keep their vigil more easily now.");
  command("say Allow me to repay your expenses and then some.");
  MONEY_MAKE_PC(10)->move(this_object());
  command("give platinum coins to " + TPQN);
}

void
do_check_reward ()
{
  if (! check_complete(TP->query_prop(QUEST_M_GUARD_MENU_LIST)))
    command("say You haven't completed the task yet!");
  else
    do_reward_player(SAMORGAN_QUEST_FEED_GUARDS_BIT,
                     SAMORGAN_QUEST_FEED_GUARDS_EXP, QUEST_M_GUARD_MENU_LIST);
}

void
check_reward ()
{
  if (TP->test_bit(domain,
                   SAMORGAN_QUEST_GROUP,
                   SAMORGAN_QUEST_FEED_GUARDS_BIT)) {
    command("say You have been rewarded already, my friend.");
    log_quest(SAMORGAN_QUEST_FEED_GUARDS_BIT,
              TPQN, "Requested reward again", "warning");
  }
  else 
    if (! TP->query_prop(QUEST_M_GUARD_MENU_LIST))
      command("say Reward? For what?");
    else
      do_check_reward();  
}

void
create_khalakhor_elf ()
{
  set_samorgan_level(SM_LIEUTENANT_LEVEL);
  set_name("lieutenant");
  ::create_khalakhor_elf();
  set_short("SaMorgan lieutenant");
  set_long("This is SaMorgan guard lieutenant. He seems relatively young "+
           "but his eyes are sharp and the body language shows a person "+
           "who has both the experience and the capacity for being in "+
           "command.\n");
  add_act("emote dips a quill in the ink and makes a note.", 1);
  add_act("ponder", 1);
  set_default_answer("I'm a bit busy right now to discuss this.", 1);
  add_ask(({"quest", "help", "task", "job"}),
          check_task);
  add_ask(({"food", "drink", "meals"}),
          "say I need someone to buy and deliver meals to the guards "+
          "in the towers around the village.", 1);
  add_ask(({"guards", "sergeants", "guard", "sergeant"}),
          "say There is a sergeant and three guards in each tower. "+
          "There may also be a courier, but he does not need food.", 1);
  add_ask(({"tower", "towers", "guard tower", "guard towers"}),
          "say Guard towers are in the four corners of the villages. "+
          "The sergeant is usually downstairs, and the guards are "+
          "up in the landing.", 1);
  add_ask(({"reward"}),
          check_reward);
  
  set_act_time(600);
}
