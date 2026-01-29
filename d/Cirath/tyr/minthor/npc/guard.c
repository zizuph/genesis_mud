#pragma strict_types
#pragma save_binary

inherit "/d/Cirath/std/monster.c";
#include "defs.h"
#include  "/sys/money.h"
#include <options.h>
void
create_monster()
{
    ::create_monster();
    set_name("guard");
    set_short("watchful guard");
   set_race_name("half-elf");
   set_adj("watchful");
   set_long("This is a standard guard of the Minthor house. They are "
	+"trained to be fierce warriors with amazing fighting prowess.\n");
  set_stats(({120,130,120,100,100,100}));
   set_skill(SS_DEFENCE, 80);
   set_skill(SS_WEP_POLEARM, 75);
   set_skill(SS_PARRY, 40);
   set_act_time(3);
   add_act("grin");
   add_act("emote paces back and forth.");
   add_act("chuckle evilly");
   add_act("emote stops and sniffs the air.");
   set_cact_time(3);
   add_cact("emote spins his double spear in circles.");
   add_cact("chuckle solemnly");
   set_chat_time(3);
   add_chat("What is your business here?\n");
   add_chat("We were trained by the same man who trained Lyden.\n");
   add_chat("You want some, boy?\n");
   set_cchat_time(3);
   add_cchat("Looks like we got ourselves a hero\n");
   add_cchat("How's that feel punk?\n");
   add_cchat("Glory to House Minthor!\n");
}
void
arm_me()
{
   clone_object(TZ_MINTHOR + "arm/bplate.c")->move(TO);
   command("wear all");
   clone_object(TZ_MINTHOR + "wep/dspear.c")->move(TO);
   command("wield all");
   MONEY_MAKE_SC(random(50))->move(this_object(),1);
}

int
query_option(int opt)
{
  return (opt == OPT_UNARMED_OFF);
}




