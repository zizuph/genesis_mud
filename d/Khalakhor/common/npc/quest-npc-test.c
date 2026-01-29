/*
 * Quest NPC routines
 * Tapakah, 06-08/2021
 */

#pragma no_clone
#pragma strict_types

#include <macros.h>
#include <math.h>

#include "/d/Khalakhor/sys/defs.h"
#include "/d/Khalakhor/private/QUESTS/quests.new.h"

inherit KLOGGER;

string domain = domain(TO);
string file = "/d/" + domain + "/log/quests.log";

string *
my_quests ()
{
  return 0;
}

varargs void
log_quest (int bit, string player,
           string message, string severity="info")
{
  string x_message = sprintf("%-11s %d %s",
                             player, bit, message);
  log_me(x_message, severity, file);
}

int
check_bit (int bit)
{
  if (TP->test_domain_bit(domain, bit)) {
    command("hmm");
    command("say I have a de ja vu feeling about it.");
    command("say Maybe you should consult higher authorities about this case.");
    log_quest(bit, TPQN, "Reward out of turn", "error");
    return 1;
  }
  return 0;
}

void
extra_reward ()
{
}

varargs void
do_reward_player (int bit, int exp, mixed prop_to_remove=0,
                  string message="You feel more experienced!", int no_save=0)
{
  // dump_array(({bit, exp, message }));
  if (check_bit(bit))
    return;
  extra_reward();
  TP->set_domain_bit(domain, bit);
  TP->add_exp_quest(exp);
  if (message)
    TP->catch_msg(message + "\n");
  log_quest(bit, TPQN, "Received " + exp + " XP");
  if (prop_to_remove) {
    if (!pointerp(prop_to_remove))
      prop_to_remove = ({ prop_to_remove });
    foreach (string prop: prop_to_remove)
      TP->remove_prop(prop);
  }
  if (! no_save)
    TP->command("$save");
}

mapping *
get_quests_by_qm (object qm)
{
  string qm_file = MASTER_OB(qm);
  foreach (mapping q_group: KHALAKHOR_QUESTS)
    if (q_group["qm"] == qm_file)
      return q_group["quests"];

  return 0;
}

mapping
get_quest_by_name (string quest_name)
{
  string *q_indices;

  foreach (mapping q_group: KHALAKHOR_QUESTS)
    foreach (mapping quest: q_group["quests"])
      if (lower_case(quest["name"]) == lower_case(quest_name)) {
        q_indices = m_indices(quest);
        quest["real_bit"] = IN_ARRAY("new_bit", q_indices)
          ? quest["new_bit"]
          : quest["bit"];
        if (! quest["new_xp"])
          quest["new_xp"] = quest["xp"];
        return quest;
      }
  return 0;
}

int
quest_done (mixed quest_name)
{
  string *q_indices;

  mapping quest = stringp(quest_name)
    ? get_quest_by_name(quest_name)
    : quest_name;
  
  q_indices = m_indices(quest);
  if (IN_ARRAY("new_bit", q_indices) &&
      TP->test_domain_bit(domain, quest["new_bit"]))
    return 2;
  if (TP->test_domain_bit(domain, quest["bit"]))
    return 1;
  return 0;
}

mapping
get_next_quest ()
{
  mapping quest;
  
  string *quest_names = my_quests();
  foreach (string quest_name: quest_names) {
    quest = get_quest_by_name(quest_name);
    if (! quest) {
      log_me(sprintf("Strange quest %s NOT FOUND", quest_name),
             "error", "quest-errors");
      continue;
    }
    if (! quest_done(quest))
      return quest;
  }
  return 0;
}

mapping *
get_quest_adjustments (object tp)
{
  mapping *quests = get_quests_by_qm(TO);
  mapping *quests_to_adjust = ({});

  foreach (mapping quest: quests) {
    if (quest_done(quest) == 1)
      quests_to_adjust += ({ quest });
  }

  if (! sizeof(quests_to_adjust))
    return 0;
  return quests_to_adjust;
}

void
adjust_quests (mapping adjustment, string tpqn)
{
  int all_delta, d, *delta = ({});
  string info;
  
  foreach (mapping quest: adjustment[tpqn]) {
    d = quest["new_xp"] - quest["old_xp"];
    delta += ({d});
    if (d > 0)
      info = "For the %s you deserve some extra reward.";
    else if (d < 0)
      info = "Unfortunately, we revised the effort for %s down a bit.";
    else
      info = "The reward for %s remains unchanged.";
    command("say " + sprintf(info, quest["name"]));
  }
  all_delta = SUM_ARRAY(delta);

  if (all_delta <= 0) {
    command("hmm");
    command("say it looks like after the revision your reward "+
            "remains unchanged. Apologies for the inconvenience.");
  }
  
  int r = 0;
  int no_save;
  foreach (mapping quest: adjustment[tpqn]) {
    log_quest(quest["new_bit"], capitalize(tpqn),
              "Quest adjustment from " + quest["bit"]);
    no_save = r == sizeof(delta)-1 ? 0 : 1;
    do_reward_player(quest["new_bit"], delta[r], 0, 0, no_save);
    r++;
  }
  int qexp = TP->query_exp_quest();

  if (all_delta > qexp / 20)
    TP->catch_msg("You feel much more experienced!\n");
  else if (all_delta > qexp / 40)
    TP->catch_msg("You feel quite more experienced!\n");
  else if (all_delta > qexp / 60)
    TP->catch_msg("You feel somewhat more experienced!\n");
  else
    TP->catch_msg("You feel a bit more experienced!\n");
  
  adjustment[tpqn] = 0;
}

