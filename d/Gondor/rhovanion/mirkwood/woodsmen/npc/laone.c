inherit "/std/monster.c";

#include "/d/Gondor/rhovanion/mirkwood/defs.h"
#include <stdproperties.h>
#include <macros.h>
#include "/sys/ss_types.h"


void

introduce_me();
arm_me();

int intro_id;

void
create_monster()
{
   
   set_name("laone");
   add_adj(({"bearded","brown-haired"}));
   set_long("This bearded man appears rather intense and serious.\n");
   set_race_name("human");
   set_gender(0);
   
   add_act("emote gives you a small, subtle smile.");
   add_act("emote stares confidently at you with piercing eyes.");
   add_act("scratch nose");
   add_act("say Greetings friend.");
   add_act("emote takes a moment to tell you an amusing story about his " +
      "wonderful daughter Doris.");
   add_act("emote goes through a complex series of stretches and exercises.");
   add_act("emote shuffles through some of the papers on the table, making " +
      "some notes.");
   add_act("yawn");

   add_ask(({"daughter","doris"}),VBFC_ME("ask_doris"));

   set_act_time(10);
   
   set_skill(SS_UNARM_COMBAT,100);
   set_skill(SS_DEFENCE, 100);

   set_stats(({ 100, 100, 100, 110, 110, 100}), 10);
   
   set_alignment(150);
   
   
   intro_id = 0;
   set_alarm(0.5,0.0,"arm_me");

}

arm_me()
{
   object axe, shirt, pants;

   FIXEUID;

   axe = clone_object(WOODSMEN_DIR + "wep/laone_axe.c");
   shirt = clone_object(WOODSMEN_DIR + "arm/laone_shirt.c");
   pants = clone_object(WOODSMEN_DIR + "arm/laone_pants.c");

   axe->move(TO);
   shirt->move(TO);
   pants->move(TO);   

   command("wear all");
   command("wield all");
}

void
add_introduced(string person)
{
   if (intro_id == 0) {
      intro_id = set_alarm(4.0,0.0, introduce_me);
   }
}

void
allow_introductions() 
{
   intro_id = 0;
}

void
introduce_me()
{
   command("introduce me");

   set_alarm(15.0, 0.0, allow_introductions);
}

string
ask_doris()
{
command("say Ahh, my daughter Doris. She is the light of my life you " +
   "know! Words cannot express just how dear she is to me.\n");
return "";
}