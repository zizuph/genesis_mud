inherit "/std/monster";

#include <macros.h>
#include <ss_types.h>
#include <language.h>
#include <stdproperties.h>
#include "/d/Rhovanion/defs.h"

#define RHUN_TOUR "_rhun_tour"
#define REPORT    RHUN_DIR+"npc/report"

void arm_me()
{
  seteuid(getuid());
  clone_object(WEAPON_DIR+"knife_med")->move(TO);
  command("wield all");
}

void create_monster()
{
  set_alarm(1.0, 0.0, "arm_me");

  set_race_name("human");
  set_name(({"mayor","man"}));
  set_adj(({"fat","village"}));
  set_short("fat village mayor");
  set_gender(0);
  set_alignment(120);
  set_long("This is the mayor of the village.  He's a rather fat man"
        + " dressed in moderately-fine clothes, considering the"
        + " area he lives in.  He looks a bit lazy and unorganized.\n");
  add_prop(CONT_I_WEIGHT, 77 * 1000);
  add_prop(CONT_I_VOLUME, 77 * 1000);
  add_prop(CONT_I_HEIGHT, 173);
  add_prop(NPC_M_NO_ACCEPT_GIVE, 0);
  set_stats(({ 48, 40, 50, 50, 50, 55 }));
  set_skill(SS_WEP_KNIFE, 30);

  set_chat_time(5);
  add_chat("The people here are good at heart.");
  add_chat("The ruins southwest of town are a bit scary.");
  add_chat("Many people have fled the area because of the Easterling warriors.");

  add_ask("report", VBFC_ME("answ_func"));
  set_default_answer(VBFC_ME("def_answ_func"));
  set_dont_answer_unseen(1);
}

string def_answ_func()
{
  command("say Let me think...");
  set_alarm(1.0, 0.0, "command", "think");
  set_alarm(5.0, 0.0, "command", "hmm");
  set_alarm(6.0, 0.0, "command", "say I give up. Give me some other riddle.");
  set_alarm(7.0, 0.0, "command", "smile at "+TP->query_real_name());
  return "";
}

string answ_func()
{
  if (TP->query_prop(RHUN_TOUR) == 1)
  {
    command("say Oh my god! I've forgotten to write a report! "+
            "I'll do it right away!");
    tell_room(environment(), QCTNAME(TO) + " starts to write a report.\n");
    set_alarm(6.0, 0.0, "middle_of_writing");
    set_alarm(12.0, 0.0, "done_with_report", TP);
  }
  else
    command("say Why should I give a report to you?");
  return "";
}

void middle_of_writing()
{
  command("say I'm almost done...");
  tell_room(environment(), QCTNAME(TO) +
            " dips his quill in the ink pot as he writes the report.\n");
}

void done_with_report(object tp)
{
  tell_room(environment(), QCTNAME(TO) +
            " is finished with the report. He seals it in red wax.\n");
  seteuid(getuid());
  clone_object(REPORT)->move(TO);

  set_alarm(2.0,0.0,"command","give report to "+tp->query_real_name());
}
