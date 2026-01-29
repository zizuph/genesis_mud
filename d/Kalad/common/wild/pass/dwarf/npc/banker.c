/* The banker
   by Korat 
   Nov. 1996
*/

inherit "/d/Kalad/std/monster";
#include "/d/Kalad/defs.h"

create_monster() 
{
   int ran;
   
   if (!IS_CLONE)
      return;
   
   set_name("banker");
   add_name("deep dwarf");
   set_race_name("dwarf");
   set_adj("greedy");
   set_alignment(500);
   set_knight_prestige(-2);
   set_long("This dwarf is the keeper of the bank.\n");
   set_stats(({80,30,60,30,40,90}));
   add_prop(CONT_I_WEIGHT,30000);
   add_prop(CONT_I_HEIGHT,500);
   add_prop(LIVE_I_NEVERKNOWN,1);
   add_prop(LIVE_I_SEE_DARK,10);
   
   set_skill(SS_UNARM_COMBAT, 50);
   set_skill(SS_DEFENCE, 75);
   set_skill(SS_AWARENESS,60);
   
   set_chat_time(25);
   add_chat("Hard work this.");
   add_chat("Got some money, have yah?");
   add_chat("Be careful stranger. There are duergars roaming around!");
   add_chat("How did you get here to our beloved Underhome?");
   
   set_cchat_time(6);
   add_cchat("Hey, this idiot wants to fight!");
   add_cchat("I'll smash your face in.");
   add_cchat("Idiot! I hope you carry some good loot.");
   add_cchat("Bring it on scumbag, I'll turn your head into ush!");
   add_cchat("I'll make a smile on your face...from ear to ear.");
   
   set_act_time(20);
   add_act(({"emote counts some coins slowly and carefully.",
      "emote grins greedily.",
      "emote pats his own purse.","wink"}));
   set_cact_time(5);
   add_cact(({"scream","spit","groan","panic"}));
}
