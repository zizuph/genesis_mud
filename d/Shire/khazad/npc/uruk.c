inherit "/d/Shire/orcmaker/orcmaker";
#include "/d/Shire/common/defs.h"
#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>
#include <formulas.h>
#include "/d/Shire/common/lib/evilkill.h"
#include "/d/Shire/common/make_money.h"

/* Prototypes */
void arm_me();
 
void create_monster()
{
  ::create_monster();
  remove_adj(query_adj());
  remove_adj(query_adj());
  set_adj(({"muscular","red-eyed"}));
  set_name("urukman");
  set_race_name("uruk");
  set_long("Larger than most orcs you've come across this man-sized "+
           "abomination certainly looks dangerous. His gleaming red "+
           "eyes seem to hint at an evil, devious intelligence you've "+
           "not encountered before among other orcs. His night black "+
           "skin and a yellow-toothed grin add to his unsettling "+
           "visage which is disturbing to say the least.\n");
 
  set_alignment(-500-random(101));
  set_attack_chance(0);
  default_config_npc(70+random(6));
  set_base_stat(SS_STR,150+random(30));
  set_base_stat(SS_CON,150+random(30));
  set_base_stat(SS_DEX,130+random(30));
  set_base_stat(SS_DIS,85+random(10));

  set_skill(SS_WEP_SWORD,70+random(20));
  set_skill(SS_DEFENCE,60+random(20));
  set_skill(SS_PARRY,50+random(20));
  set_skill(SS_AWARENESS,50+random(25));
  set_skill(SS_2H_COMBAT,50+random(15));
  set_skill(SS_BLIND_COMBAT,30+random(15));
  set_skill(SS_WEP_KNIFE, 60 + random(10));
   set_skill(SS_WEP_AXE, 50 + random(15));
   set_skill(SS_WEP_POLEARM, 75 + random(5));

  add_chat("What are you looking at?!");
 
  set_alarm(1.0,0.0,arm_me);
}

void arm_me()
{
  object key,wep,arm;
  seteuid(getuid(TO));

  arm = clone_object("/d/Gondor/morgul/obj/platemail");
  arm->move(TO);
  arm = clone_object("/d/Gondor/morgul/obj/platehelm");
  arm->move(TO);
  arm = clone_object("/d/Shire/orcmaker/arm/cloak");
  arm->move(TO);
  command("wear all");
  wep = clone_object("/d/Gondor/morgul/obj/mattock");
  wep->move(TO);
  command("wield all");
}
