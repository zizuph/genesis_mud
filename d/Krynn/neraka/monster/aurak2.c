/* created by Aridor 04/19/94 */ 
#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/solamn/splains/local.h"
#include <money.h>
#include <ss_types.h>

inherit AURAK;
inherit AUTO_TEAM
inherit "/lib/unique";

#define SPLAINS "/d/Krynn/solamn/splains/obj/"
#define NERAKA  "/d/Krynn/neraka/obj/"
#define LAKE    "/d/Krynn/solace/lake/obj/"
#define AWEP    "/d/Ansalon/common/wep/"
#define ARMOUR "/d/Krynn/solamn/splains/obj/"

#define WEP1 "/d/Ansalon/common/wep/pole/roncone"
#define WEP2 "/d/Krynn/common/weapons/light_halberd"
#define WEP3 "/d/Krynn/neraka/weapons/bknife"
#define ARM1 ARMOUR + "barmour1"
#define ARM2 ARMOUR + "bleggings"
#define ARM3 ARMOUR + "bheavyboots"
#define ARM4 ARMOUR + "brobe"
#define ARM5 ARMOUR + "bhelmet"

void
create_aurak()
{
   set_pick_up_team(({"aurak","sivak","bozak","kapak", "priest"}));
   set_max_team_size_auto_join(6);
   
   set_stats(({140,140,140,140,140,140}));

   int i = 30 + random(40);

   set_skill(SS_DEFENCE,     i);
   set_skill(SS_PARRY,       i);
   set_skill(SS_WEP_SWORD,   i);  
   set_skill(SS_2H_COMBAT,   i);
   set_skill(SS_WEP_KNIFE,   i);
   set_skill(SS_WEP_CLUB,    i);
   set_skill(SS_WEP_POLEARM, i);
   set_skill(SS_WEP_AXE,     i);
   set_skill(SS_AWARENESS, 100);
   
   set_all_hitloc_unarmed(20);
   
   set_act_time(3);
   add_act("emote looks at you suspiciously.");
   add_act("emote snarls: What have we here?");
   add_act("emote hisses: How did you find us?");
   
   set_cact_time(10);
   add_cact("shout DIE THEN SCUM!");
   add_cact("shout Soldiers! To me!");
   arm_draconian_called = 1;

    /* Necessary so that we don't automatically wield
       standard draconian equipment */

  object weapon = clone_unique(WEP1, 5);

  if (!weapon)
  {
      weapon = clone_unique(WEP3, 7, WEP2);
  }

  equip(({ weapon, ARM1, ARM2, ARM3, ARM4, ARM5 }));
  set_color("blue");
}


void
init_living()
{
   init_team_pickup();
   ::init_living();
}

