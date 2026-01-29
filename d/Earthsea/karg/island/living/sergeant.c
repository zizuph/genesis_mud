#include <ss_types.h>

#include "defs.h"

inherit ISLAND_STD+"karg";

void create_karg()
{
 set_name("sergeant");
 set_adj("karg");
 set_short("karg sergeant");
 set_long("This is Karg Empire sergeant, he is officer's assistant. "+
   "As every sergeant, he's battle scared , weather-beaten ,old "+
   "and tough.\n");

 set_alignment(-400);

 set_stats(({110,130,115,70,75,105}));
 
 set_skill(SS_WEP_CLUB,80);
 set_skill(SS_DEFENCE,75);
 set_skill(SS_PARRY,65);
 set_skill(SS_AWARENESS,60);
 set_skill(SS_LOC_SENSE,50);
 set_skill(SS_TRACKING,50);
 set_skill(SS_BLIND_COMBAT,60);

 clone_object(ISLAND_WEP+"club")->move(TO);
 clone_object(ISLAND_ARM+"plate")->move(TO);
 clone_object(ISLAND_ARM+"helm")->move(TO);
 clone_object(ISLAND_ARM+"shield")->move(TO);
 clone_object(ISLAND_ARM+"bands")->move(TO);
 clone_object(ISLAND_ARM+"leggings")->move(TO);

 command("wear all");
 command("wield all");
}

