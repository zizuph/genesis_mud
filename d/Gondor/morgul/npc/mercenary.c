/*
 *	/d/Gondor/morgul/npc/mercenary.c
 *
 *	Olorin, July 1993
 *	Bumped up the weapon, parry and defence skills defined in
 *	/d/Gondor/morgul/npc/man Dunstable, Feb 94
 *	General revision: Olorin, February 1996
 */
#pragma strict_types

inherit "/d/Gondor/morgul/npc/ithil_man.c";

#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"

#define WEP_ARRAY1 ({MORGUL_DIR + "obj/waraxe", MORGUL_DIR + "obj/battleaxe", MORGUL_DIR + "obj/spear"})
#define ARM_ARRAY1 ({MORGUL_DIR + "obj/ltunic", MORGUL_DIR + "obj/ithil_cloak"})
#define ARM_ARRAY3 ({MORGUL_DIR + "obj/blackcap"}) 

public void
create_ithil_man()
{
   add_adj("strong");
   remove_adj("swarthy");
   
   set_long(BSN(CAP(LANG_ADDART(implode(query_adjs()," "))) + 
         " man from the plains between the inland sea " +
         "of Rhun and the Ash Mountains. Like many of his kind, he is a " +
         "mercenary in the service of the Lord of Morgul. He has long black " +
         "hair, bound into a think plait at the back of his head. "));
   set_short("strong mercenary");
   set_pshort("strong mercenaries");
   set_name("mercenary");
   set_pname("mercenaries");
   remove_name("haradrim");
   remove_name("southron");
   add_name("easterling");
   add_name("plainsman");
   add_adj("easterling");
   remove_adj("swarthy");
   
   set_base_stat(SS_STR, 65+random(15));
   set_base_stat(SS_DEX, 70+random(10));
   set_base_stat(SS_CON, 65+random(5));
   set_skill(SS_WEP_SWORD, 75);
   set_skill(SS_DEFENCE, 75);
   set_skill(SS_WEP_AXE, 75);
   set_skill(SS_WEP_POLEARM, 75);
   set_skill(SS_WEP_CLUB, 75);
   set_skill(SS_DEFENCE, 75);
   set_skill(SS_PARRY, 75);
   set_skill(SS_AWARENESS, 60);
   remove_prop(LIVE_I_SEE_DARK);
   
   set_chat_time(15+random(15));
   add_chat("Did you ever see the Sea of Rhun?");
   add_chat("I serve him who pays best.");
   add_chat("We need wains and horses! I hate fighting on foot!");
   add_chat("They make great weapons for us in Lugburz!");
   add_chat("This waiting stinks! I want to loot Minas Tirith now!");
   add_chat("I heard, the Chief brought in some of the Olog-hai!");
   
   set_cchat_time(5+random(10));
}

static void
set_arm_arrays()
{
   ::set_arm_arrays();
   Wep1 = WEP_ARRAY1;
   Arm1 = ARM_ARRAY1;
   Arm3 = ARM_ARRAY3;
}

