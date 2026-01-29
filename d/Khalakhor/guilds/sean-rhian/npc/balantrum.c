// Balantrum - "nurse" for a sick novice (tinne); quest npc
//
//   Coder         Date                Action
// -------------- -------- ----------------------------------------------
// Zima           6/24/98  Created - accepts oil from questor to anoint
//                         Tinne. Blesses questor for bringing oil, allowing
//                         Semion to reward him/her.
//
// TAPAKAH        08/2021  Refactoring

#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>
#include <cmdparse.h>
#include "../tool/oils.h"
#include "defs.h"

inherit  SR_NPC+"monkbase";
 
void
arm_me ()
{
  vest_me(({"robe","cincture","tonsure","scapular","cope"}));
}
 
void
create_khalakhor_human ()
{
  ::create_khalakhor_human();
  add_name(({"manach","monk"}));
  add_adj(({"worried","gray-haired","forgetful"}));
  set_long("He is a gray-haired manach who has a worried look on his face. "+
           "He seems to be fretting over a sick novishagh. Rumor has it "+
           "that he tends to be a bit forgetful.\n");
  
  set_manach_stats((60+random(60)));
  set_size_descs("short","plump");
 
  set_act_time(30);
  add_act("emote examines the novishagh worriedly.");
  add_act("emote bows his head prayerfully.");
  add_act("sigh");
  add_act("emote paces about worriedly.");
  add_act("emote paces about worriedly.");
  add_act("say You never should have gone out with your hair wet!");
  add_act("say We don't have any oil left to anoint you.");
  add_act("emote scolds the novishagh lightly.");
 
  set_default_answer("@@defans");
  add_ask(({"help","sick","novishagh","anoint"}),
          "say Novishagh Tinne is sick and I'm out of oil to anoint him.",1);
  add_ask(({"quest","tour","job","task","chore"}),
          "say You must see Abbot Semion about that. I may not assign "+
          "anything to you.",1);
  add_ask("oil",
          "say If I had the right oil, I could anoint the sick lad with it.",1);
  add_ask(({"right oil","about oil","kind of oil","what kind of oil",
            "which oil","what is the right oil"}),
          "say There is an oil I could use to anoint the sick lad with. "+
          "Cimbaeth could make it if he had the ingredients.",1);
  add_ask("flask","say I don't have one.",1);
  add_ask(({"blubber","slab","slab of blubber","whale","ingredients"}),
          "say Ask Cimbaeth about that.",1);
  add_ask(({"cimbaeth","Cimbaeth"}),
          "say He's usually in the kitchen. He knows all about making oils.",1);
  add_ask(({"vowed","vowed brathairs"}),
          "say They are the brathairs who have take a vow of silence.",1);
  add_ask(({"powder","mortar","pestle"}),
          "say You can grind an herb into a powder with a mortar and pestle.",1);
  add_ask(({"tinne","Tinne"}),
          "say Tinne is the sick Novishagh here.",1);
  add_ask("beatha",
          "say It is a small red berry, hard to identify sometimes. It grows "+
          "on the plains often. It has healing powers.",1);
 
  remove_prop(NPC_M_NO_ACCEPT_GIVE);
}
 
void
do_bless (object flask, object tp)
{
  object rm=ENV(TO);
  object nov=present("tinne",rm);
  string novs;
 
  command("say Ah, this is just what the sick lad needs.");
  if (objectp(nov)) {
    novs = nov->short();
    command("emote anoints the "+novs+" with oil.");
    command("emote lays his hands on the "+novs+" and mumbles a prayer.");
  }
  else
    command("say I'll anoint him as soon as I can find him.");
  command("say Thank you for bringing this to me!");
  tp->catch_msg(QCTNAME(TO)+" raises his hand over you and blesses you.\n");
  tell_room(rm, QCTNAME(TO)+" raises his hand over "+QTNAME(tp)+
            " and blesses "+(tp->query_objective())+".\n",tp);
  tp->add_prop(BALANS_BLESSING,1);
  flask->remove_object();
}
 
void
do_return (string msg, string obs, string tpn)
{
  command("say "+msg);
  if (!command("give "+obs+" to "+tpn))
    command("drop "+obs);
}
 
void
check_ob (object ob, object tp)
{
  string obs = lower_case(ob->query_name());
  string tpn = lower_case(tp->query_name());
 
  // accept only a sr oil flask
  if (!(ob->id(SR_FLASK)))
    {
      command("emote examines the "+(ob->short())+" carefully.");
      do_return("Hmm, I don't think this will help any.",obs,tpn);
      return;
    }
 
  // make sure he's on the quest.
  if (! tp->query_prop(SEMIONS_BLESSING) ||
      (tp->query_prop(SEMIONS_BLESSING))["name"] != "Blubber Oil")
    {
      command("emote peers at you suspiciously.");
      command("say You do not have the abbot's blessing to do this.");
      do_return("I can not accept this from you.", obs,tpn);
      return;
    }
 
  // check if anything in it
  if (ob->query_amt() <= 0)
    {
      command("emote turns the flask upside down.");
      command("blink unexpetedly");
      command("say This flask is empty!");
      do_return("If it were filled with oil, I could use it.",obs,tpn);
      return;
    }
 
  // check oil type
  switch (ob->query_oilid())
    {
    case WHALE_OIL:
      command("say Thank You!");
      command("say Oh wait, I forgot something.");
      command("say It needs powdered beatha added it to it to work.");
      do_return("Find some beatha, grind it into powder and add it "+
                "to the oil and bring it back.",obs,tpn);
      break;
    case BEATHA_OIL:
      command("say Thank You!");
      command("say Oh wait, I forgot something.");
      command("say It needs to be blessed by one of the vowed "+
              "brathairs.");
      command("say Not all of us can give this blessing.");
      do_return("Ask one of them to bless the oil and bring it back.",
                obs,tpn);
      break;
    case BL_BEATHA_OIL:
      do_bless(ob,tp);
      break;
    default:
      command("sigh");
      command("say This is not the right kind of oil.");
      command("say It needs to have powdered beatha added to it.");
      do_return("See if you can find the right oil for me.",obs,tpn);
    }
}
 
void
enter_inv (object ob, object from)
{
  ::enter_inv(ob,from);
  if (living(from))
    set_alarm(3.0,0.0,&check_ob(ob,from));
}
