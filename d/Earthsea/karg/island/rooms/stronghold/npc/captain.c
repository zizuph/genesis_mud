#include "defs.h"

inherit STRHOLD_STD+"std_npc";

#include <stdproperties.h>
#include <ss_types.h>

void create_stronghold_karg()
{
 string adj1,adj2;

 set_level(3);
 set_alignment(-900);
 set_auto_reteam(1);

 set_name("captain");
 add_name("guard");
 set_adj("tough");
 add_adj("important-looking");
 add_adj("karg");
 set_short("tough important-looking karg captain");
 set_long("This is captain of guards. He is commander of all guards "+
   "of the stronghold. He looks prety tough , as he might have taken "+
   "part in lots of combats around Earthsea.\n");

 set_stats(({170,180,170,140,140,120}));

 set_skill(SS_WEP_SWORD,100);
 set_skill(SS_WEP_AXE,100);
 set_skill(SS_2H_COMBAT,100);
 set_skill(SS_DEFENCE,100);
 set_skill(SS_PARRY,100);
 set_skill(SS_AWARENESS,75);
 set_skill(SS_BLIND_COMBAT,90);

 clone_object(STRHOLD_WEP+"sword1")->move(TO);
 clone_object(STRHOLD_WEP+"axe1")->move(TO);

 clone_object(STRHOLD_ARM+"plate1")->move(TO);
 clone_object(STRHOLD_ARM+"helm")->move(TO);
 clone_object(STRHOLD_ARM+"bands")->move(TO);
 clone_object(STRHOLD_ARM+"leggings")->move(TO);

 command("wield all");
 command("wear all");
}

