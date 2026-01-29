//Intro routines taken from Merrygrin's torch seller.
// Used in a new way, by Dunstable Feb 1995

inherit "/std/monster";
inherit "/lib/trade";

#include "macros.h"
#include "stdproperties.h"
#include "money.h"
#include "/sys/ss_types.h"
#include "/d/Shire/common/defs.h"
#include "/d/Shire/common/monster/tobacco.h"
#include "/d/Shire/common/lib/goodkill.h"
#include "/d/Shire/prestige.h"

int intro;

void reset_intr();
void return_introduce(string who);

void
create_monster()
{
  if (!IS_CLONE) return;
  set_name("gamgee");
   set_title("the Candlemaker of Gamwich");
  add_name("candlemaker");
  set_living_name("gamgee");
  set_adj(({"smiling","strutting"}));
  set_race_name("hobbit");
  set_long("This hobbit is the proprietor of the candle shoppe. "+
  "If he doesn't appear to be listening, you might read the pricelist.\n");
  default_config_npc(30);	/* But we are not supposed to kill him */
  config_default_trade();
    
  set_chat_time(5);
  add_chat("Candlemaking is good for the soul.");
  add_chat("I'm nearly out of wick.");
  add_chat("I wish I had some more boiling oil.");

  set_act_time(5);
  add_act("emote dips a wick into the hot wax, over and over again.");
  add_act("emote wraps a stick in pitch-dripping cloth.");
  add_act("sigh");
  add_act("think retirement");  

  set_skill(SS_AWARENESS, 40);
  set_skill(SS_DEFENCE, 50);
  set_skill(SS_UNARM_COMBAT, 60);

  clone_tobacco();
  trig_new("%s 'introduces' %s", "react_introduce");

  intro = 1;

}


void
return_introduce(string who)
{
  if (random(4) && present(who, environment())) {
    command("introduce myself to " + who);
  }
  else {
    command("introduce myself");
  }
}


int
react_introduce(string who, string tmp)
{
  object ob;

  if (!intro) return 0;
  intro = 0;
   set_alarm(30.0, 0.0, &reset_intr());
/*  if (!who) return 0;
  if (!notmet_me(ob)) return 0;
  if (!random(20)) return 0;*/
  set_alarm(3.0, 0.0, &return_introduce(who));
  return 1;
}


reset_intr() 
{  
  intro = 1;
}
