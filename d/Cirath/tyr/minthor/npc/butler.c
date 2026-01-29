inherit "/std/monster.c";
#include "defs.h"
#include  "/sys/money.h"

void
create_monster()
{
    set_name("jeeves");
    set_short("humble serving human");
   set_race_name("human");
   set_adj("humble");
   set_adj("serving");
   set_long("This appears to be one of the butlers that the "
	+"Minthor's keep in the house to keep their guests happy "
	+"and quiet.  They bring drinks and food to people and "
	+"keep visible to help keep away troublemakers.\n");
   set_alignment(250);
   set_stats(({20,30,30,35,35,30}));
   set_skill(SS_DEFENCE, 30);
   set_skill(SS_WEP_CLUB, 20);
   set_skill(SS_PARRY, 20);
   set_act_time(3);
   add_act("say Would you like a drink?");
   add_act("say The Minthor's treat us well.");
   add_act("say Can I help you?");
   add_act("emote smiles happily.");
   set_cact_time(6);
   add_cact("say Someone help me!");
   add_cact("say What did I do to you?");
   add_cact("emote screams like a girl.");
}
void
arm_me()
{
   clone_object(TZ_MINTHOR + "wep/serv_tray")->move(TO);
   command("wield all");
   MONEY_MAKE_SC(random(50))->move(this_object(),1);
}


