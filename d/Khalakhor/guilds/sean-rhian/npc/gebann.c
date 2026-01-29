/* Gebann - Prior of the kirk at Tabor Sagh
**
**   Coder         Date                Action
** -------------- -------- ----------------------------------------------
** Zima           1/10/98     Created
** Tapakah        08/2021     Refactored
*/

#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>
#include <cmdparse.h>
#include "../objects/powder.h"
#include "defs.h"
 
inherit  SR_NPC+"monkbase";

#define  VEST (({"robe","cincture","tonsure","scapular","cope"}))
 
void
arm_me ()
{
  vest_me(VEST);
}
 
void
create_khalakhor_human () {

  ::create_khalakhor_human();
  add_name(({"manach", "prior", "monk"}));
  set_adj(({"wizened", "white-haired"}));
  set_title("the Manach of Sean-Rhian and Prior of the Kirk at Tabor Sagh");
  set_long("He is a wizened white-haired human, impressively dressed in "+
           "the habit of a kirk prior.\n");
 
  set_manach_stats((60+random(60)));
  set_size_descs("tall","thin");
  set_act_time(60);
  add_act("emote mumbles a silent prayer.");
  add_act("emote puts his hands together prayerfully.");
  add_act("emote bows his head prayerfully.");
  add_act("emote raises his hands and sings a quiet chant.");
  add_act("emote folds his arms into the sleeves of his robe.");
  add_act("emote nods at you hospitably.");
  add_act("emote chants in an ancient tounge.");
  add_act("emote traces three circles before his face.");
  add_act("emote genuflects on one knee and prays.");
  add_act("emote folds his arms beneath his scapular.");
  remove_prop(LIVE_M_NO_ACCEPT_GIVE); 
  set_default_answer(defans);
  add_ask(({"job","tour","quest","task","for job","for task",
            "for a job","for a task"}),
          "say I do need some incense from Kirk Seanchan Tor. Go see "+
          "Abbot Semion there.",1);
  add_ask(({"abbot","semion","abbot semion","abbot Semion","Abbot Semion"}),
          "say Semion is Abbot of Kirk Seanchan Tor.",1);
  add_ask(({"kirk seanchan tor","Kirk Seanchan Tor"}),
          "say It is in the city of Port MacDunn.",1);
  add_ask(({"port","macdunn","port macdunn","Port MacDunn","city"}),
          "say Port MacDunn is the village where ships arrive from foreign "+
          "lands. I'm sure you've been there.",1);
  add_ask(({"incense","about incense","for incense"}),
          "say I need some from Kirk Seanchan Tor. Have you brought me some?",1);
  add_ask(({"reward","for reward"}), "say I can not reward you for "+
          "anything. See Abbot Semion about that.",1);
  add_ask(({"blessing","for blessing"}), "@@ask_bless",1);
  add_ask(({"bees","bee","honey","hive","honeycomb","comb","beeswax"}),
          "say I've often seen honeybees on the trail north of the village.",1);
  add_ask(({"help","for help"}),
          "say How can I help you? Ask me something and perhaps I can "+
          "answer.",1);
}
 
string
ask_bless ()
{
  object tp=this_player();
  if (tp->query_prop(GEBANNS_BLESSING))
    command("say I have already given you my blessing, "+
            tp->query_name()+".");
  else if (objectp(present(TOUR_INCENSE,tp)))
    command("say Give me the incense and I shall bless you.");
  else {
    command("say You have done nothing to receive my blessing, "+
            tp->query_name()+".");
    command("say Perhaps you could ask me for a task?");
  }
  return "";
}
 
void
do_thank (object ob, object from, int step)
{
  if (!objectp(present(from,environment())))
    return;
  switch (step) {
  case 1:
    command("say Thank you! I have been needing this for days now!");
    break;
  case 2:
    command("say Receive my blessings good friend!");
    command("emote raises his hands and closes his eyes.");
    break;
  case 3:
    command("emote chants: Bannaghey Ardaugh eh shoh "+
            capitalize(from->query_name())+"!");
    from->add_prop(GEBANNS_BLESSING,1);
    break;
  case 4:
    command("emote lowers his hands and opens his eyes.");
    command("smile");
    ob->remove_object();
    return;
  }
  set_alarm(3.0,0.0,&do_thank(ob,from,(step+1)));
}
 
void
do_return (object ob, object from)
{
  string obname=lower_case(ob->query_name());
  command("emote examines the "+(ob->query_short())+" bewilderedly.");
  if (ob->id(TOUR_INCENSE)) {
    command("say You do not have the blessing of Semion to bring this.");
    command("say I can not accept it, as much as I need it.");
    command("say Go and obtain his blessing to do this task.");
    command("say Then return to me with your gift and I may bless you.");
  }
  else
    command("say Thank you, but I do not need this.");
  command("give "+obname+" to "+lower_case(from->query_name()));
  command("drop "+obname);
}
 
void
enter_inv (object ob, object from)
{
  ::enter_inv();
  if (interactive(from))
    set_alarm(3.0,0.0,
              ob->id(TOUR_INCENSE) && from->query_prop(SEMIONS_BLESSING)
              ? &do_thank(ob,from,1) : &do_return(ob,from));
}
