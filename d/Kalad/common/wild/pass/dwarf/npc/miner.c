/* miners */
/* made by Korat */

inherit "/d/Kalad/std/monster";
#include "/d/Kalad/defs.h"

/* These are random guards descriptions */
#define RNDADJ ({"broad","grim","young","strong","grumpy"})

create_monster() {
   int ran;
   
   if (!IS_CLONE)
      return;
   
   ran = random(5);
   set_name("miner");
   add_name("dwarf miner");
   set_pname("miners");
   set_short(RNDADJ[ran]+" miner dwarf");
   set_race_name("dwarf");
   set_adj(RNDADJ[ran]);
   set_alignment(ran*100);
   set_long("This is a deep dwarf that uses his days mining here "+
      "in the caves.\n");
   set_stats(({90,30,60,30,40,90}));
   add_prop(CONT_I_WEIGHT,30000);
   add_prop(CONT_I_HEIGHT,500);
   add_prop(LIVE_I_NEVERKNOWN,1);
   add_prop(LIVE_I_SEE_DARK,10);
   set_knight_prestige(ran*100);   
   
   set_skill(SS_UNARM_COMBAT, 10);
   set_skill(SS_WEP_AXE, 50);
   set_skill(SS_DEFENCE, 40);
   set_skill(SS_PARRY, 10);
   
   set_chat_time(16+ran);
   add_chat("Mining for coal are yah, stranger?");
   add_chat("I love this work! Chiseling out the heart of the mountain.");
   add_chat("Be careful stranger. You might trip on your tools!");
   add_chat("Strangers ... in my cave!");
   
   set_act_time(10+2*ran);
   add_act(({"emote chisels on a vein","emote studies the rock carefully",
            "grumble","grin.","emote tests a small rock with the pickaxe"}));
   set_cact_time(5);
   add_cact(({"scream","spit","groan","panic"}));
   trig_new("%w 'mines' 'for' %s","react");
}

void
react()
{
   switch(random(7))
   {
      case 0: TO->command("say Chiseling for coal ehh?");
      TO->command("emote laughs loudly."); break;
      case 1: TO->command("emote peers at you and your lousy "+
         "way of mining."); break;
      case 2: TO->command("emote sings an ancient dwarven "+
         "song about mining."); break;
      case 3: TO->command("emote grumbles: Find ye'r own cave!"); break;
      default: break;
   }
}

/* Here I equip the dewars with weapons and armours */
void
arm_me()
{
   object weap;
   object armo;
   seteuid(getuid(this_object()));
   weap = clone_object("/d/Kalad/common/wild/pass/dwarf/wep/miner_axe");
   weap -> move(this_object());
   command("wield all");
   armo = clone_object("/d/Kalad/common/wild/pass/dwarf/arm/jerkin");
   armo -> move(this_object());
   armo = clone_object(CPASS(dwarf/arm/dew_boots));
   armo -> move(this_object());
   command("wear all");
}
