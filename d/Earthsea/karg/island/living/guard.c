#include <ss_types.h>

#include "defs.h"

#define WPS ({ISLAND_WEP+"sword",ISLAND_WEP+"axe"})

inherit ISLAND_STD+"karg";

void create_karg()
{
 set_name("guard");
 set_adj("karg");
 set_short("karg guard");
 set_long("This is one of the Karg Empire mercenaries that were "+
   "hired to invade Gont. He looks very experienced and battle "+
   "scarred.\n");

 set_alignment(-200);

 set_stats(({100,120,100,70,70,100}));
 
 set_skill(SS_WEP_SWORD,75);
 set_skill(SS_WEP_AXE,75);
 set_skill(SS_DEFENCE,70);
 set_skill(SS_PARRY,50);
 set_skill(SS_AWARENESS,50);
 set_skill(SS_LOC_SENSE,50);
 set_skill(SS_TRACKING,50);
 set_skill(SS_BLIND_COMBAT,50);

 clone_object(WPS[random(2)])->move(TO);
 clone_object(ISLAND_ARM+"plate")->move(TO);
 clone_object(ISLAND_ARM+"helm")->move(TO);
 clone_object(ISLAND_ARM+"shield")->move(TO);
 clone_object(ISLAND_ARM+"bands")->move(TO);
 clone_object(ISLAND_ARM+"leggings")->move(TO);

 command("wear all");
 command("wield all");
}

