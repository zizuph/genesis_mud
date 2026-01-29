/*
 * Quest NPC routines
 * Tapakah, 06/2021
 */

#pragma no_clone
#pragma strict_types

#include "../defs.h"

string domain = domain(TO);
string file = "/d/" + domain + "/log/quests.log";

varargs void
log_quest (int group, int bit, string player,
           string message, string severity="info")
{
  string log_string = sprintf("%s [%-7s] %2d %2d (%-11s) %s\n",
                              ctime(time()), severity,
                              group, bit,
                              player, message);
  write_file(file, log_string);
}

int
check_bit (int group, int bit)
{
  if (TP->test_bit(domain, group, bit)) {
    command("hmm");
    command("say I have a de ja vu feeling about it.");
    command("say Maybe you should consult higher authorities about this case.");
    log_quest(group, bit, TPQN, "Reward out of turn", "error");
    return 1;
  }
  return 0;
}

void
extra_reward ()
{
}

varargs void
do_reward_player (int group, int bit, int exp, mixed prop_to_remove=0)
{
  if (check_bit(group, bit))
    return;

  extra_reward();
  log_quest(group, bit, TPQN, "Extra reward received");
  TP->set_bit(group, bit);
  TP->add_exp_quest(exp);
  TP->catch_msg("You feel more experienced!\n");
  log_quest(group, bit, TPQN, "Received " + exp + " XP");
  if (prop_to_remove)
    TP->remove_prop(prop_to_remove);
}
