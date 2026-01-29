#include "defs.h"

inherit STRHOLD_STD+"std_npc";

#include <stdproperties.h>
#include <ss_types.h>

void create_stronghold_karg()
{
 string adj1,adj2;

 set_auto_reteam(1);
 set_alignment(-200);

 set_name("guard");
 adj1=MERC_ADJ1[random(sizeof(MERC_ADJ1))];
 adj2=MERC_ADJ2[random(sizeof(MERC_ADJ2))];
 set_adj(adj1);
 add_adj(adj2);
 add_adj("karg");
 set_short(adj1+" "+adj2+" karg guard");
 set_long("This is one of guards that guard the stronghold. He looks "+
   "well-built and according to his battle-scarred looks might have "+
   "fought in many combats for the glory of Karg Empire.\n");

 set_stats(({95+random(16),115+random(11),95+random(16),70,
   95+random(11),90}));

 set_skill(SS_WEP_SWORD,90);
 set_skill(SS_WEP_AXE,90);
 set_skill(SS_DEFENCE,80);
 set_skill(SS_PARRY,60);
 set_skill(SS_AWARENESS,60);
 set_skill(SS_BLIND_COMBAT,55);

 clone_object(WEP3[random(sizeof(WEP3))])->move(TO);

 clone_object(STRHOLD_ARM+"plate1")->move(TO);
 clone_object(STRHOLD_ARM+"helm")->move(TO);
 clone_object(STRHOLD_ARM+"bands")->move(TO);
 clone_object(STRHOLD_ARM+"leggings")->move(TO);
 clone_object(STRHOLD_ARM+"shield")->move(TO);

 command("wield all");
 command("wear all");
}

