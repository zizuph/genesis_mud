inherit "/std/monster";
inherit "/d/Emerald/ctower/npc/riddle_giver";

#include <stdproperties.h> 
#include "/d/Emerald/defs.h"
#include "/d/Emerald/lib/bit.h"
#include "../ctower.h"

static mapping answered_wrong = ([]);
static string *answered_right = ({});

void config_guardian(int i)
{
  set_name("guardian");
  add_name("tower_guardian");
  set_race_name("guardian");
  set_living_name("_guardian" + i + "_");
  set_long("A pretty strong monster, that. It might let you pass if "+
      "you answer its riddle correctly though. You may ask it for a "+
      "riddle and \"reply\" with the solution.\n");
 
  set_alignment(0);
  set_gender(G_NEUTER);
 
  add_prop(CONT_I_WEIGHT, 47000);
  add_prop(CONT_I_HEIGHT, 142);
  add_prop(LIVE_I_NEVERKNOWN, 1);
  add_prop(NPC_M_NO_ACCEPT_GIVE, 1);
  add_prop(NPC_I_NO_RUN_AWAY, 1);
 
  default_config_npc(30 * i);
 
  set_skill(SS_DEFENCE, 30 * i);
  set_skill(SS_UNARM_COMBAT, 30 * i);
 
  create_riddle(CTOWER_LOG + "riddles" + i, 0);
 
  add_ask(({ "riddle", "about riddle", "for riddle", "for a riddle" }),
      VBFC_ME("ask_riddle"), 0);
}
 
void already_replied(object ob)
{
  if (present(ob, environment()))
  {
    command("say You have already solved my riddle.");
  }
}

void refuse_riddle(object ob)
{
  if (present(ob, environment()))
  {
    command("say No more riddles.... Begone fool!");  
  }
}

static void start_riddle(object ob)
{
  if (member_array(ob->query_real_name(), answered_right))
  {
    set_alarm(0.5, 0.0, &already_replied(ob));
    return;
  }
  
  if (answered_wrong[ob->query_real_name()] &&
      (time() - answered_wrong[ob->query_real_name()] < 3600))
  {
    set_alarm(0.5, 0.0, &refuse_riddle(ob));
    return;
  }

  ::start_riddle(ob);
}
  
string
ask_riddle()
{
  set_alarm(2.0, 0.0, &start_riddle(TP));
  return "";
}
 
void
init_living()
{
  ::init_living();
  init_riddle();
}
 
void
start_riddle_hook(object ob)
{
  tell(ob, "You must answer the following riddle to pass me.");
}

void reward_player(object ob) { }
 
void
wrong_answer_hook(object ob)
{
  command("sigh");
  tell(ob, "The answer is wrong.");
  command("say You are not worthy.");
  attack_object(ob);

  answered_wrong[ob->query_real_name()] = time();
}

void
correct_answer_hook(object ob)
{
  tell(ob, "The answer is correct.");

  answered_right += ({ ob->query_real_name() });

  if (environment())
  {
    environment()->register(ob);
  }
}

static int do_reply(string str)
{
  if (strlen(str) &&
      (answered_wrong[TP->query_real_name()]))
  {
    if (time() - answered_wrong[TP->query_real_name()] < 3600)
    {
      command("say No more guessing.... Begone fool!");
      return 1;
    }
    else
    {
      answered_wrong = m_delete(answered_wrong, TP->query_real_name());
    }
  } 

  return ::do_reply(str);
}

void do_die(object killer)
{
  if (environment())
  {
    environment()->register(killer);
  }

  ::do_die(killer);
}
