#include "defs.h"

inherit STRHOLD_STD+"std_npc";

#include <stdproperties.h>
#include <ss_types.h>

void create_stronghold_karg()
{
 string adj1,adj2;

 set_level(1);
 set_alignment(-400);
 set_auto_reteam(1);

 set_name("guard");
 adj1=OFFICER_ADJ1[random(sizeof(OFFICER_ADJ1))];
 adj2=OFFICER_ADJ2[random(sizeof(OFFICER_ADJ2))];
 set_adj(adj1);
 add_adj(adj2);
 add_adj("karg");
 add_adj("elite");
 set_short(adj1+" "+adj2+" karg elite guard");
 set_long("This is one of elite guards that guard the stronghold. "+
   "This guard is a veteran who has been through lots of battle "+
   "campains. You guess he's guarding something very important.\n");

 set_stats(({110+random(11),125+random(15),105+random(16),80,
   105+random(16),105}));

 set_skill(SS_WEP_SWORD,100);
 set_skill(SS_WEP_AXE,100);
 set_skill(SS_DEFENCE,90);
 set_skill(SS_PARRY,75);
 set_skill(SS_AWARENESS,65);
 set_skill(SS_BLIND_COMBAT,70);

 clone_object(WEP2[random(sizeof(WEP2))])->move(TO);

 clone_object(STRHOLD_ARM+"plate2")->move(TO);
 clone_object(STRHOLD_ARM+"helm")->move(TO);
 clone_object(STRHOLD_ARM+"bands")->move(TO);
 clone_object(STRHOLD_ARM+"leggings")->move(TO);
 clone_object(STRHOLD_ARM+"shield")->move(TO);

 command("wield all");
 command("wear all");
}

