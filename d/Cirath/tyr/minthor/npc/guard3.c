#pragma strict_types
#pragma save_binary

inherit "/d/Cirath/std/monster.c";
#include "/d/Cirath/common/defs.h"
#include "defs.h"
#include  "/sys/money.h"
#include <options.h>

void
kick_me_out();

void
create_monster()
{
   set_name("guard");
   set_short("experienced guard");
   set_race_name("half-elf");
   set_adj("experienced");
   set_long("This is a standard guard of the Minthor house. They are "
	+"trained to be fierce warriors with amazing fighting prowess.\n");
   set_stats(({100,110,90,90,90,90}));
   set_skill(SS_DEFENCE, 90);
   set_skill(SS_WEP_POLEARM, 80);
   set_skill(SS_PARRY, 60);
   set_act_time(5);
   add_act("grin");
   add_act("emote paces back and forth.");
   add_act("chuckle evilly");
   add_act("emote stops and sniffs the air.");
   add_act("emote spins his double spear in circles.");
   add_act("chuckle solemnly");
   set_cact_time(3);
   add_cact("' What is your business here?");
   add_cact("' We were trained by the same man who trained Lyden.");
   add_cact("' You want some boy?");   
   add_cact("' Looks like we got ourselves a hero.");
   add_cact("' How's that feel punk?");
   add_cact("' Glory to House Minthor!");
	set_alarm(300.0,0.0,kick_me_out);
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

void
kick_me_out()
{
	say("Guard steps back to his chamber.\n");
	remove_object();
}
