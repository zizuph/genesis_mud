#include "defs.h"

inherit STRHOLD_STD+"std_npc";

#include <stdproperties.h>
#include <ss_types.h>

void create_stronghold_karg()
{
 string adj1,adj2;

 set_auto_reteam(1);

 set_alignment(-100);

 set_name("mercenary");
 add_name("guard");
 adj1=MERC_ADJ1[random(sizeof(MERC_ADJ1))];
 adj2=MERC_ADJ2[random(sizeof(MERC_ADJ2))];
 set_adj(adj1);
 add_adj(adj2);
 add_adj("karg");
 set_short(adj1+" "+adj2+" karg mercenary");
 set_long("This is one of mecrenaries of Karg Empire. They have been "+
   "hired by Empire to secure building grounds , and when stronghold "+
   "was finished they started to patrol it inside.\n");

 set_stats(({85+random(16),95+random(11),85+random(16),65,
   80+random(11),80}));

 set_skill(SS_WEP_SWORD,80);
 set_skill(SS_WEP_AXE,80);
 set_skill(SS_DEFENCE,70);
 set_skill(SS_PARRY,55);
 set_skill(SS_AWARENESS,50);
 set_skill(SS_BLIND_COMBAT,50);

 clone_object(WEP3[random(sizeof(WEP3))])->move(TO);

 clone_object(STRHOLD_ARM+"plate1")->move(TO);
 clone_object(STRHOLD_ARM+"helm")->move(TO);
 clone_object(STRHOLD_ARM+"bands")->move(TO);
 clone_object(STRHOLD_ARM+"leggings")->move(TO);
 clone_object(STRHOLD_ARM+"shield")->move(TO);

 command("wield all");
 command("wear all");
}

