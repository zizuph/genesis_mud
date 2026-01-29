inherit "/d/Cirath/std/gith";
#include "../defs.h"
#include <std.h>
#include <stdproperties.h>
#include <ss_types.h>
#include <money.h>
#include "/d/Cirath/common/teamfnc.h"

#define RNDADJ ({"twitching","mean","aggressive","brutish","scarred"})
#define RNDADJ2 ({"deformed","ugly","violent","large","small"})
#define RNDWEP ({"g_spear1","g_club1","g_axe1","g_sword1"})

create_monster()
{

   set_race_name("gith");
   set_adj(RNDADJ2[random(5)]);
   add_adj(RNDADJ[random(5)]);
   set_long("Gith are a strange Athasian race akin to goblins.  There "
     +"aren't many physical similarities between the two, though.  This "
	+"creature looks to be about seven feet tall when standing up "
	+"straight, but thankfully, its hunched disfigured frame only "
	+"allows it to stand five feet tall.  Scaly brownish green skin "
	+"covers its emaciated body, but beneath the surface, rippling "
	+"muscles are obvious.  Small, coal, black eyes stare at you "
	+"from beneath its thick brow.  This is truly a fearsome creature.\n");
   set_aggressive(1);
   set_alignment(0);
   set_stats(({100,140,140,90,90,100}));
   set_skill(SS_WEP_POLEARM,70);
    set_skill(SS_WEP_SWORD,70);
   set_skill(SS_WEP_AXE,70);
   set_skill(SS_WEP_CLUB,70);
   set_skill(SS_PARRY,50);
   set_skill(SS_AWARENESS,50);
   set_skill(SS_DEFENCE,70);
   set_act_time(6);
   add_act("say That last caravan had lots of goodies.");
   add_act("say Try something, I dare ya.");
   add_act("grin evilly");
   add_act("cackle maniacally");
   set_cact_time(6);
   add_cact("say Die fool!");
   add_cact("say Die!");
   add_cact("growl softly");
   add_cact("roar");
   add_prop(LIVE_I_NEVERKNOWN,1);
   add_prop(LIVE_I_SEE_DARK,5);
}

void
arm_me()
{
   clone_object(GITH_WEP + RNDWEP[random(4)])->move(TO);
   command("wield all");
   clone_object(GITH_ARM + "g_body1")->move(TO);
   clone_object(GITH_ARM + "g_helm1")->move(TO);
   command("wear all");
}

