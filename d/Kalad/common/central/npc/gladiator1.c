/* a training gladiator */

inherit "/d/Kalad/std/monster";
inherit "/d/Kalad/lib/intro";
#include "/d/Kalad/defs.h"
#include "/sys/ss_types.h"
#include "/sys/macros.h"
#include "/sys/money.h"
int str;
int dex;
int con;

/* by Korat */
create_monster()
{
   ::create_monster();
   switch (random(3)){
      case 0:
      set_race_name("human");
      break;
      case 1:
      set_race_name("dwarf");
      break;
      case 2:
      set_race_name("goblin");
      break;
      case 3:
      set_race_name("elf");
      break;
   }
   switch (random(3))
   {
      case 0:
      set_adj("ugly");
      break;
      case 1:
      set_adj("grumpy");
      break;
      case 2:
      set_adj("grim");
      break;
      case 3:
      set_adj("strong");
      break;
   }
   set_name("gladiator");
   set_long("This man is a gladiator of the arena in Kabal, and he looks like "+
      "it too with scars all over his face. A dangerous man this, if he is irritated.\n");
   str = 50 + random(20);
   dex = 50 + random(30);
   con = 40 + random(30);
   set_stats(({str,dex,con,40,40,80}));
   set_alignment(0);
   set_skill(SS_WEP_SWORD,90);
   set_skill(SS_UNARM_COMBAT,50);
   set_skill(SS_DEFENCE,80);
   set_skill(SS_PARRY,50);
   set_skill(SS_AWARENESS,20);
   set_act_time(4);
   add_act("stretch");
   add_act("emote removes a bandage and drops it on the table.");
   add_act("groan");
   add_act("emote scratches his back.");
   add_act(({"say Who are you?","ponder newbie gladiators...dead meat.","grin"}));
   set_cact_time(1);
   add_cact("shout For the glory and the sound of death!");
   add_cact("emote winces in pain.");
   add_cact("say Ahh, lets see how good a fighter you are!");
   add_cact("say I will kill you! So you better leave now!");
   set_knight_prestige(0);
   add_speak("Shut up will you? I am too tired to talk.\n");
   set_default_answer("What was that? Ohhh don't bother to repeat it...\n");
   set_title("gladiator of the Kabal arena");
   trig_new("%w 'strikes' 'you' 'with' %s","react_charge");
}
void
arm_me()
{
   object wep,arm;
   seteuid(getuid(this_object()));
   arm = clone_object("/d/Kalad/common/central/arm/collar");
   arm -> move(TO);
   arm = clone_object("/d/Kalad/common/central/arm/glad_shield");
   arm -> move(TO);
   command("wear all");
   wep = clone_object("/d/Kalad/common/central/wep/gladius");
   wep -> move(this_object());
   command("wield all");
   MONEY_MAKE_CC(random(30))->move(this_object(),1);
   MONEY_MAKE_GC(random(3))->move(this_object(),1);
}

int
react_charge(string who, string dummy){
   if(who){
      who = lower_case(who);
      set_alarm(3.0,0.0,"return_hurt",who);
      return 1;
   }
}

void
return_hurt(string who){
   object obj;
   int ran;
   if(obj = present(who, environment())){
      command("fume "+obj->query_real_name());
      command("say What a bloody coward you are "+ capitalize(obj->query_real_name()));
      command("emote spits on the ground in front of "+ capitalize(obj->query_real_name()));
      command("say Meet me in the arena next time! I will be prepared then.");
   }
}

public void
introduce_me(string who)
{
   object obj;
   int ran;
   if (obj = present(who, environment()))
   {
      switch (random(3))
      {
         case 0: command("emote looks at you with some uninterested eyes."); break;
         case 1: command("say Now why would I befriend you, when I might "+
            "end up killing you tomorrow."); break;
         case 2: command("say Nice to meet you, and nice to forget you."); break;
         case 3: break;
         default: break;
      }
   }
}
