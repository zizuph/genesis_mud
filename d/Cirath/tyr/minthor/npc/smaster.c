inherit "/std/monster.c";
#include "defs.h"
#include  "/sys/money.h"
#include "/d/Cirath/common/introfnc.h"
void
create_monster()
{
   set_name("olgars");
   add_name("master");
   set_title("Slavemaster of the Minthor House");
   set_race_name("human");
   set_adj("brutal");
   set_long("This is the slavemaster of the Minthors. He is not a "
	+"nice guy at all. He looks fairly tough, you better keep "
	+"your distance.\n");
   set_stats(({100,100,100,55,55,70}));
   set_skill(SS_DEFENCE, 50);
   set_skill(SS_WEP_CLUB, 75);
   set_skill(SS_PARRY, 40);
   set_act_time(3);
   add_act("grin");
   add_act("emote slaps his club into his hand.");
   add_act("smile demonically");
   add_act("emote whips a poor slave.");
   set_cact_time(3);
   add_cact("emote shakes his head in disbelief.");
   add_cact("poke all eye");
   set_chat_time(3);
   add_chat("Work you miserable curs!\n");
   add_chat("You better get out of here, or i'll hit you.\n");
   add_chat("I am not happy to see you, so leave!\n");
   set_cchat_time(3);
   add_cchat("You are not that smart are you?\n");
   add_cchat("Does your mother know you are this dumb?\n");
   add_cchat("Now i'm going to kick your ass.\n");
}
void
arm_me()
{
   clone_object(TZ_MINTHOR + "arm/bplate.c")->move(TO);
   command("wear all");
   clone_object(TZ_MINTHOR + "wep/baton.c")->move(TO);
   command("wield all");
   MONEY_MAKE_SC(random(10))->move(this_object(),1);
   MONEY_MAKE_GC(random(5))->move(this_object(),1);
}
