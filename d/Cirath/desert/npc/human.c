inherit "/std/monster";
#include "/d/Cirath/common/defs.h"
#include <std.h>
#include <stdproperties.h>
#include <ss_types.h>
#include <money.h>
#include "../defs.h"

#define RNDADJ ({"wary", "dirty", "frightened", "tired"})
#define RNDADJ2 ({"adolescent","middle-aged","young","old"})

mixed attackers;

create_monster()
{
   set_race_name("human");
   set_adj(RNDADJ2[random(4)]);
   add_adj(RNDADJ[random(4)]);
   set_long("This human is looking around in fear, he looks to "
   	+"have been possibly injured in a fight.  His clothes "
   	+"dictate either poverty, or severe neglect.\n");
   set_alignment(300);
   set_stats(({70,105,70,60,60,60}));
   set_skill(SS_WEP_POLEARM,40);
   set_skill(SS_PARRY,10);
   set_skill(SS_AWARENESS,10);
   set_skill(SS_DEFENCE,30);
   set_act_time(9);
   add_act("say Those creatures just burst from the sand and "
   	+"attacked me!");
   add_act("emote rubs his tired muscles.");
   add_act("say I think there are gith out there, be careful they "
   	+"attack any stranger on sight.");
   add_act("say I've heard tales of some camp of gith in the "
   	+"mountains, but no one has ever come back from there alive.");
   add_act("say A passing caravan leader said that he had been "
   	+"raided by the gith, and that their leader was a powerful "
   	+"psionicist.");
   set_cact_time(9);
   add_cact("say Why?  Save me Kalak, save me!");
   add_cact("say Stop it you damn thieves!  You're one of them "
   	+"aren't you?");
   add_cact("say Help!  Oh sweet mother of Kalak!  Help!!");
   add_prop(LIVE_I_NEVERKNOWN,1);
}

void
arm_me()
{
   clone_object(DES_WEP + "staff")->move(TO);
   command("wield all");
   clone_object(DES_ARM+ "robe")->move(TO);
   command("wear all");
}

