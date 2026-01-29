inherit "/d/Cirath/std/gith";
#include "/d/Cirath/common/defs.h"
#include <std.h>
#include <stdproperties.h>
#include <ss_types.h>
#include <money.h>
#include "/d/Cirath/common/teamfnc.h"
#include "../defs.h"

#define RNDADJ ({"big", "tough", "strong", "ugly", "menacing"})
#define RNDADJ2 ({"scaly","grinning","hunchbacked","smelly","powerful"})
#define RNDWEP ({"g_spear2","g_club2","g_axe2","g_sword2"})[random(4)]

create_monster()
{

   set_race_name("gith");
   set_adj(RNDADJ2[random(5)]);
   add_adj(RNDADJ[random(5)]);
   set_long("Gith are a strange Athasian race akin to goblins.  There "
   	+"aren't many physical similarities between two, though.  This "
	+"creature looks to be about seven feet tall when standing up "
	+"straight, but thankfully, its hunched disfigured frame only "
	+"allows it to stand five feet tall.  Scaly brownish green skin "
	+"covers its emaciated body, but beneath the surface, rippling "
	+"muscles are obvious.  Small, coal, black eyes stare at you "
	+"from beneath its thick brow.  This is truly a fearsome creature.\n");
   set_aggressive(1);
   set_alignment(-200);
   set_stats(({120,155,150,90,90,110}));
   set_skill(SS_WEP_POLEARM,80);
   set_skill(SS_WEP_SWORD,80);
   set_skill(SS_WEP_AXE,80);
   set_skill(SS_WEP_CLUB,80);
   set_skill(SS_PARRY,60);
   set_skill(SS_AWARENESS,50);
   set_skill(SS_DEFENCE,75);
   set_act_time(6);
   add_act("say That last caravan had lots of goodies.");
   add_act("say Try something, I dare ya.");
   add_act("grin evilly");
   add_act("cackle maniacally");
   add_act("emote twirls his spear lazily.");
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
   clone_object(GITH_WEP+ RNDWEP)->move(TO);
   command("wield all");
   clone_object(GITH_ARM+ "g_body2")->move(TO);
   clone_object(GITH_ARM+ "g_helm2")->move(TO);
   clone_object(GITH_ARM+ "g_shield")->move(TO);
   command("wear all");
}

