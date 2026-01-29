inherit "/d/Kalad/std/monster";
inherit "/d/Kalad/lib/intro";
#include "/d/Kalad/defs.h"
#define DO_I_TELL_RUMOURS  "_do_i_tell_rumours"
/* by Antharanos */
create_monster()
{
   ::create_monster();
   add_prop(DO_I_TELL_RUMOURS,1);
   set_name("elden");
   add_name("merchant");
   add_name("banker");
   set_race_name("human");
   set_adj("middle-aged");
   add_adj("grim");
   set_long("Dressed in the finest of imported silks, this man must clearly be "+
      "a high-ranking member of the Merchants Guild of Kabal. That, and the "+
      "fact that he apparently owns this bank.\n");
   set_stats(({75,70,65,125,130,70}));
   set_alignment(100);
   set_skill(SS_AWARENESS,50);
   set_skill(SS_TRADING,75);
   set_act_time(3);
   add_act("say You could learn a lot from my experiences.");
   add_act("say Welcome to my bank, and please, make as many transactions as you can afford.");
   add_act("smile greed");
   set_title("the Wealthy Merchant of Kabal");
   add_speak("I own this bank because i'm quite the high-ranking member of this guild.\n");
   set_knight_prestige(-10);
   add_prop(OBJ_M_NO_ATTACK,"You can't attack him! He manages this bank, "+
      "and without him, the guild would not have a bank!\n");
}