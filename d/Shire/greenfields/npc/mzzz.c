inherit "/d/Shire/orcmaker/orcmaker";
inherit "/lib/unique";
 
#include "/d/Shire/common/defs.h"
#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>
#include <formulas.h>
#include "/d/Shire/common/make_money.h"
#include "/d/Shire/private/shire_admin.h"


/* Hzzz, orc, wielder of Leech, leader of camp in Hsqwin Mountain
   5 April 1994 by Mayhem  
 */

/* No, it's actually the lieutenant, Grushkir. Dunstable, June 1994 */
void create_monster()
{
  ::create_monster();
  remove_adj(query_adj());
  remove_adj(query_adj());
  set_adj(({"lanky","evil-eyed"}));
  set_living_name("grushkir");
  set_name("grushkir");
  set_race_name("orc");
  set_long("This lanky, evil-eyed orc has an air of insolence about "+
    "him. He seems to despise you and everyone else equally. "+
    "He clearly projects power and the impression of haughtiness and "+
    "strength.\n");
  set_alignment(-300-random(101));
  set_attack_chance(0);
  default_config_npc(70+random(6));
  set_base_stat(SS_STR,140+random(21));
  set_base_stat(SS_CON,110+random(21));
  set_base_stat(SS_DEX,140+random(11));
  set_base_stat(SS_DIS,110+random(16));

  set_skill(SS_WEP_POLEARM,90+random(5));
  set_skill(SS_DEFENCE,80+random(5));
  set_skill(SS_PARRY,75+random(16));
  set_skill(SS_AWARENESS,60+random(11));
  set_skill(SS_2H_COMBAT,75+random(26));
  set_skill(SS_BLIND_COMBAT,70+random(31));

  MAKE_MONEY;
  MAKE_MONEY;
  make_gold(3);
  set_alarm(1.0,0.0,"arm_me");

  TELL_ADMIN("Grushkir has been cloned " + ctime(time()));

}

void arm_me()
{
  object key, wep, arm;
  seteuid(getuid(TO));

  key=clone_object(GREEN_DIR + "obj/mchest_key");
  key->move(TO);
  arm = clone_object(GREEN_DIR + "arm/mhelm");
  arm->move(TO);
  arm = clone_unique(GREEN_DIR + "arm/mmail", MAX_UNIQUE_ITEMS, GREEN_DIR + "arm/hplate");
  arm->move(TO);
  command("wear all");
  wep=clone_object(ORCMAKER_DIR + "wep/ghalberd");
  wep->move(TO);
  command("wield all");
 command("say Prepare to meet DEATH! DIE!");
  set_alarm(0.5,0.0,"do_chest");
}

void do_chest()
{
  command("get chest");
//  command("unlock chest with key");
//  command("open chest");
  command("put coins in chest");
  command("close chest");
  command("lock chest with key");
//  command("drop chest");
}


void attacked_by (object ob)
{
    ::attacked_by(ob);
    TELL_ADMIN("Grushkir was attacked by " + ob->query_cap_name() + 
        " ("+ob->query_average_stat()+") at " + ctime(time()));
}
