#include "defs.h"

inherit STRHOLD_STD+"std_npc";

#include <stdproperties.h>
#include <ss_types.h>

void create_stronghold_karg()
{
 string adj1,adj2;

 set_level(2);
 set_alignment(-700);
 set_auto_reteam(1);

 set_name("lieutenant");
 add_name("guard");
 adj1=OFFICER_ADJ1[random(sizeof(OFFICER_ADJ1))];
 adj2=OFFICER_ADJ2[random(sizeof(OFFICER_ADJ2))];
 set_adj(adj1);
 add_adj(adj2);
 add_adj("karg");
 set_short(adj1+" "+adj2+" karg lieutenant");
 set_long("This officer is one of many officers here, who responsable "+
   "for guards and mecrenaries. He is tough looking and must be "+
   "good opponent in combat , otherwise he wouldn't be an officer "+
   "of glorious Karg empire.\n");

 set_stats(({130+random(11),140+random(21),125+random(11),100,
   110+random(15),125}));

 set_skill(SS_WEP_SWORD,100);
 set_skill(SS_WEP_AXE,100);
 set_skill(SS_DEFENCE,100);
 set_skill(SS_PARRY,80);
 set_skill(SS_AWARENESS,70);
 set_skill(SS_BLIND_COMBAT,80);

 clone_object(WEP2[random(sizeof(WEP2))])->move(TO);

 clone_object(STRHOLD_ARM+"plate1")->move(TO);
 clone_object(STRHOLD_ARM+"helm")->move(TO);
 clone_object(STRHOLD_ARM+"bands")->move(TO);
 clone_object(STRHOLD_ARM+"leggings")->move(TO);
 clone_object(STRHOLD_ARM+"shield")->move(TO);

 command("wield all");
 command("wear all");
}

