#include <ss_types.h>

#include "defs.h"

inherit ISLAND_STD+"karg";

#define WPS ({ISLAND_WEP+"sword",ISLAND_WEP+"axe"})

void create_karg()
{
 set_name("lieutenant");
 set_adj("karg");
 set_short("karg lieutenant");
 set_long("This is Karg Empire officer who is responsable for "+
   "hired mercenaries. He looks tough, experienced and skilled.");

 set_stats(({120,140,120,80,80,110}));
 
 set_skill(SS_WEP_SWORD,85);
 set_skill(SS_WEP_AXE,85);
 set_skill(SS_WEP_POLEARM,85);
 set_skill(SS_2H_COMBAT,65);
 set_skill(SS_DEFENCE,80);
 set_skill(SS_PARRY,70);
 set_skill(SS_AWARENESS,70);
 set_skill(SS_LOC_SENSE,50);
 set_skill(SS_TRACKING,50);
 set_skill(SS_BLIND_COMBAT,70);

 clone_object(WPS[random(2)])->move(TO);
 clone_object(ISLAND_WEP+"spear")->move(TO);
 clone_object(ISLAND_ARM+"o_plate")->move(TO);
 clone_object(ISLAND_ARM+"helm")->move(TO);

 command("wear all");
 command("wield all");
}

