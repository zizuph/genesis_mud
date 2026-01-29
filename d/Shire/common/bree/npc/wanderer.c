inherit "/std/monster";
#include "/sys/ss_types.h"
#include "/sys/stdproperties.h"
#include "/d/Shire/common/defs.h"
#include "/d/Shire/common/make_money.h"


void
create_monster()
{
   set_name("bebe");
   set_pname("bebes");
   set_race_name("hobbit");
   add_adj(({"wiry","nimble"}));
   set_long("This hobbit looks rather wiry- you should think "+
	    "twice before messing with him.\n");

   set_alignment(100 + random(100));
   add_prop(LIVE_I_NEVERKNOWN, 1);
   set_stats(({39,55,41,34,33,33}));
   set_skill(SS_DEFENCE, 45);
   set_skill(SS_WEP_KNIFE, 65);
   set_skill(SS_HERBALISM, 40);
   set_skill(SS_HIDE, 70);
   set_skill(SS_SNEAK, 63);


   MAKE_MONEY;
   set_act_time(10);
   add_act("emote wonders where everybody went.");
   add_act("think");
   add_act("search here for herbs");

   set_chat_time(4);
   add_chat("Where is that darn herb?");
   add_chat("Nice weather, isn't it?");
   add_chat("Sometimes I wonder if I shouldn't be farming");
   add_chat("I live in Michel Delving.");
   add_chat("I like travelling, do you?");
   add_chat("You wouldn't happen to have any extra pipe-weed on you, would you?");

   set_cact_time(1);
   add_cact("spit all");
   add_cact("knee all");
   add_cact(({"sneak west","sneak west","stop fighting"}));
   add_cact(({"sneak north","stop fighting","hide"}));
   add_cact("hide");

   set_cchat_time(2);
   add_cchat("I hate you!");
   add_cchat("I don't want to fight!");
   add_cchat("See you later!");

   set_restrain_path(({"/d/Shire/common/hobbiton","/d/Shire/common/michel","/d/Shire/common/eastroad","/d/Shire/common/bree"}));
   set_random_move(5);
   set_monster_home("/d/Shire/common/bree/crossing");

}





 
