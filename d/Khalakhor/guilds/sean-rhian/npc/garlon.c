/* Garlon - Manach Sacristan who has the key to the Sacristy cabinet
**
**   Coder         Date                Action
** -------------- -------- ----------------------------------------------
** Zima           6/8/98    Created
** Damaris        01/2001   Removed set_short
** Tapakah        08/2021   Refactored
*/

#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>
#include <cmdparse.h>
#include "defs.h"

inherit  SR_NPC+"monkbase";

#define  SACRISTY MACDUNN_KIRK+"room/kbellt2"
int    havekey=1;
string kname;
 
#define  VEST (({"robe","cincture","tonsure","scapular"}))
 
void
arm_me ()
{
  vest_me(VEST);
}
 
string
ask_flask ()
{
  object sac, flask;
  string fn;
 
  if (! TP->query_prop(SEMIONS_BLESSING) ||
      (TP->query_prop(SEMIONS_BLESSING))["name"] != "Blubber Oil")
    return "say I am not permitted to get a flask for you.";
 
  if (present(SR_FLASK,TP))
    return "say But I have already given you one.";
 
  sac = (SACRISTY)->get_this_object();
  if (ENV(TO) != sac) {
    command("say Meet me in the kirk sacristy in the belltower, and "+
            "ask me again, and I'll get one for you.");
    TO->move_living("headed toward the sacristy",sac);
    return "say Ah, here we are.";
  }
 
  flask = clone_object(SR_TOOL+"flask");
  flask->move(TO);
  fn    = lower_case(flask->query_name());
  command("emote unlocks the tall cabinet.");
  command("emote opens the tall cabinet.");
  command("emote takes a "+fn+" from the tall cabinet.");
  command("emote closes the tall cabinet.");
  command("emote locks the tall cabinet.");
  if (!command("give "+fn+" to "+lower_case(TP->query_name())))
    command("drop "+fn);
  command("say There you are. May you have good fortune on your task.");
  return  "emote smiles knowingly.";
}
 
string
ask_key ()
{
  object key;
  if (present(SHAM_PENDANT,TP))
    if (havekey) {
      key=clone_object(SR_OBJ+"scabkey");
      key->move(TO);
      havekey=0;
      kname=(TP->query_name());
      command("give key to "+lower_case(kname));
      command("drop key");
      return "say Return it to me when you are finished, aspirant.";
    }
    else
      return ("say I gave it to "+kname+".");
  else
    return "say I can not give the key to one who is not of the faith.";
}

void
create_khalakhor_human ()
{
  ::create_khalakhor_human();
  add_name(({"monk","manach","sacristan"}));
  add_adj(({"lean","gray-haired"}));
  set_long("He is a lean gray-haired human, his habit identifying him as "+
           "a monastic member of the Order of Sean-Rhian.\n");
 
  set_manach_stats((40+random(60)));
  add_prop(NPC_M_NO_ACCEPT_GIVE,0); // may accept gifts
  set_wander(MACDUNN_KIRK+"room/k",SACRISTY,45);
  set_act_time(30);
  add_act("emote mumbles a silent prayer.");
  set_default_answer(defans);
  add_ask("censor","say It is a tool used to burn incense.",1);
  add_ask(({"platter","chalice"}),
          "say It is used in the rites performed here.",1);
  add_ask(({"cabinet","cabinets"}),
          "say They hold the vestments and equipment used in the rites here.",1);
  add_ask("rites","say They are the rituals of worship we perform.",1);
  add_ask("abbot","say Abbott Semion is usually in his office.",1);
  add_ask(({"key","for key","for key to cabinet","for key to cabinets"}),
          ask_key, 1);
  add_ask(({"flask","for flask","for oil flask","for flask from cabinet"}),
          ask_flask, 1);
  // add_ask("security",ask_security,1);
}
 
void
check_ob (object ob, object from)
{
  if (living(from))
    if (ob->id("_sr_scabkey")) {
      command("emote nods at you thankfully.");
      ob->remove_object();
      havekey=1;
    }
    else if (ob->id("_baile_ashlagh_letter")) {
      return;
    }
    else {
      command("say I can not accept this.");
      command("give "+lower_case(ob->query_name())+" to "+
              lower_case(from->query_name()));
      command("drop "+lower_case(ob->query_name()));
    }
}

void
enter_inv (object ob, object from)
{
  ::enter_inv(ob,from);
  set_alarm(3.0,0.0,&check_ob(ob,from));
}
