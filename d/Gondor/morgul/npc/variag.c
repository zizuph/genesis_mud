/*
 *	/d/Gondor/morgul/npc/variag.c
 *
 *	Olorin, July 1993
 *	General revision: Olorin, February 1996
 */
#pragma strict_types

inherit "/d/Gondor/morgul/npc/ithil_man.c";

#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"

#define WEP_ARRAY1 ({MORGUL_DIR + "obj/waraxe", MORGUL_DIR + "obj/battleaxe", MORGUL_DIR + "obj/spear"})
#define WEP_ARRAY2 ({MORGUL_DIR + "obj/maingauche", MORGUL_DIR + "obj/shield"})
#define ARM_ARRAY1 ({MORGUL_DIR + "obj/ltunic", MORGUL_DIR + "obj/ithil_cloak"})
#define ARM_ARRAY3 ({MORGUL_DIR + "obj/blackcap"}) 

public void
create_ithil_man()
{
  set_short("swarthy variag");
  set_pshort("swarthy variags");
  set_name("variag");
  set_name("variags");
  add_name("soldier");
  remove_name("haradrim");
  add_name("plainsman");

  set_long(CAP(LANG_ADDART(implode(query_adjs()," "))) + 
    " variag, one of the men from Khand, the far land " +
    "south of Mordor, beyond the Sea of Nurnen. The rulers of Khand serve " +
    "the Dark Lord and they send men to Mordor to fill its armies. The variag " +
    "has thick plaits of hair braided with gold. His face and his arms are " +
    "full of scars, and he looks like he has served in many a campaign. ");
    
  set_base_stat(SS_DEX, 90+random(15));
  set_base_stat(SS_CON, 95+random(5));
  remove_adj("swarthy");

  set_chat_time(15+random(15));
  add_chat("Did you ever see the Sea of Nurnen?");
  add_chat("I serve only the Dark Lord.");
  add_chat("I want booze, and perhaps a few girls!");
  add_chat("When will this damned war start?");
  add_chat("I need to kill a few tarks soon!");
  add_chat("Give me a few mumakil, and we won't need Grond!");
  add_chat("This waiting stinks! I want to loot Minas Tirith now!");

  set_cchat_time(5+random(10));
  set_hp(query_max_hp());
}

static void
set_arm_arrays()
{
  ::set_arm_arrays();
  Wep1 = WEP_ARRAY1;
  Arm1 = ARM_ARRAY1;
  Arm3 = ARM_ARRAY3;
}

