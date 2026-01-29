inherit "/std/monster";
#include "/d/Cirath/common/defs.h"
#include "/d/Cirath/tyr/minthor/defs.h"
#include <std.h>
#include <stdproperties.h>
#include <ss_types.h>
#include <money.h>

void
create_monster()
{
   set_name("Lila");
   set_race_name("human");
   set_adj("young");
   add_adj("rich");
   set_gender(1);
   set_short("young rich female human");
   set_long("You imagine this is one of the daughters of Maximus "
	+"Minthor.  She is quite attractive, but obviously very "
	+"naive about worldly matters.  Obviously she enjoys being "
	+"wealthy, her clothes tell you that much.\n");
   set_alignment(150);
   set_stats(({30,40,30,35,35,30}));
   set_skill(SS_WEP_KNIFE,20);
   set_skill(SS_DEFENCE,30);
   set_skill(SS_PARRY,20);
   set_skill(SS_AWARENESS,20);
   set_act_time(3);
   add_act("say I love this house, it is so nice.");
   add_act("say Being rich is the best.");
   add_act("say Did you get invited here?");
   add_act("emote smiles happily.");
   set_cact_time(6);
   add_cact("say Leave me alone!");
   add_cact("say Please don't hurt me!");
   add_cact("emote screams for help.");
   add_prop(LIVE_I_NEVERKNOWN,1);
 
}
void
arm_me()
{
   clone_object(TZ_MINTHOR + "wep/knife_nk")->move(TO);
   command("wield all");
   MONEY_MAKE_SC(random(50))->move(this_object(),1);
}

