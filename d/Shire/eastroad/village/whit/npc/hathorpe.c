/*
The owner of the Whitfurrows Bakery.
* Cloned by ~Shire/eastroad/village/whit/whitbaker
*/
inherit "std/monster";

#include "/sys/ss_types.h"
#include "/sys/macros.h"
#include "/sys/stdproperties.h"
#include "/d/Shire/common/make_money.h"
#include "/d/Shire/common/defs.h"
#include "/d/Shire/prestige.h"

void ready_me();
 
create_monster() {
   if (!IS_CLONE) return;
   set_name("hathorpe");
   set_living_name("_hathorpe_");
   set_title("the Baker of Whitfurrows");
   set_race_name("hobbit"); 
   set_adj(({"tall","handsome"}));
   set_long("Hathorpe is the master baker for Whitfurrows.  "+
      "He is wearing a white apron, dusted with flour, and he has "+
      "a large rolling pin in his hand.  He looks to be well-fed, and "+
      "jovial, as befits a hobbit cook.\n");
   default_config_npc(30);
   set_base_stat(SS_CON, 65);
   set_base_stat(SS_STR,60);
   set_base_stat(SS_DEX,80);
   set_base_stat(SS_DIS,95);
   set_base_stat(SS_INT,50);
   set_base_stat(SS_WIS,50);
   set_gender(0);
   set_alignment(150 + random(50));
   
   set_aggressive(0);
   set_attack_chance(0);
   
   add_prop(CONT_I_WEIGHT, 70000);   /* 70 Kg  */
   add_prop(CONT_I_VOLUME, 70000);   /* 70 Ltr */
   add_prop(LIVE_I_NEVERKNOWN, 1);
   set_alarm(1.0, 0.0, ready_me);
}

void
ready_me()
{
  object pin, apron;
  pin = clone_object("/d/Shire/eastroad/village/whit/wep/rolling_pin");
  pin->move(TO);
  apron = clone_object("/d/Shire/eastroad/village/whit/arm/apron");
  apron->move(TO);
  command("wear all");
  command("wield all");
}
