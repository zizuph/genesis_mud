/* a training warrior */

inherit "/d/Kalad/std/monster";
inherit "/d/Kalad/lib/intro";
#include "/d/Kalad/defs.h"
#include "/sys/ss_types.h"
#include "/sys/macros.h"
#include "/sys/money.h"
/* by Korat */
   create_monster()
{
   ::create_monster();
   set_name("gharrack");
   set_race_name("goblin");
   set_adj("broad");
   set_long("This goblin is a warrior that has come here to train "+
      "in using his club as far as the trainer can help him.\n");
   set_stats(({70,75,70,30,30,60}));
   set_alignment(-10);
   set_skill(SS_WEP_CLUB,28);
   set_skill(SS_UNARM_COMBAT,20);
   set_skill(SS_DEFENCE,40);
   set_skill(SS_PARRY,40);
   set_skill(SS_AWARENESS,25);
   set_act_time(4);
   add_act("emote tries to bonk the wooden pole further down into the ground, but "+
      "misses.");
   add_act("grumble");
   add_act(({"scream","say What am I doing wrong here!?"}));
   add_act("emote tries to hit the pole hard with a low swing with her club.");
   add_act("emote swings the club high into the air and then thrusts it "+
      "sideways towards the pole with all her strength. The club smashes into "+
      "the pole and ricochettes back hard, making the goblin to loose her  "+
      "balance.");
   add_act("emote bends down and move fast foreward with the club in her "+
      "right hand, ready to hit hard. Then suddenly she grips the club with her "+
      "other hand and sends the club hard into the pole. A difficult move that!"); 
   set_cact_time(1);
   add_cact("say Hey! This is more fun than hitting a pole!.");
   add_cact(({"say you bastard! I shall kill you now!","emote tries to avoid your"+
      "hits.","scream"}));
   add_cact("say curse you! I will splatter you all over this room...");
   set_knight_prestige(1);
   set_title("Freelance warrior for hire.");
   set_default_answer("I am paying to train here...so shut up!\n");
   set_alarm(0.0,0.0,"arm_me");
}
void
arm_me()
{
   object wep;
   seteuid(getuid(this_object()));
   wep = clone_object("/d/Kalad/common/central/wep/wdclub");
   wep -> move(this_object());
   command("wield all");
   MONEY_MAKE_SC(random(30))->move(this_object(),1);
}
