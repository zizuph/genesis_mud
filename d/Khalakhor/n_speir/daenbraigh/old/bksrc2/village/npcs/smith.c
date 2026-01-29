/*
 * Goblin village barman
 * TAPAKAH 05/2005
 */

inherit "/d/Khalakhor/std/monster";
#include "../../nspeir.h"
#include "../../village/village.h"
#include "/d/Khalakhor/sys/defs.h";

inherit "../../base";
inherit "/d/Khalakhor/lib/weapon_repairs.c";

#include <ss_types.h>
#include <money.h>
#include <stdproperties.h>
#include <const.h>
#include <macros.h>

void equip_me();

#define SHARPEN_COST 16
#define WAX_COST     14

void
create_khalakhor_monster()
{
  if(! IS_CLONE)
    return;
  ::create_khalakhor_monster();

  set_name("Foryn");
  set_race_name("dwarf");
  set_adj("grim");
  add_adj("sweaty");
  set_long(BSN("This is " + VILLAGENAME + " smith. His story is unclear "+
	       "and the rumours say he was lured by the money and decided " +
	       "to leave his people and come to work as a smith here for "+
	       "the goblin garrison and for the elder. He looks unhappy with "+
	       "his choice but he is determined not to return to the mines."
	       ));
  set_gender(G_MALE);
  
  set_base_stat(SS_STR,180,10);
  set_base_stat(SS_DEX,120,10);
  set_base_stat(SS_CON,190,10);
  set_base_stat(SS_INT,90,10);
  set_base_stat(SS_WIS,110,10);
  set_base_stat(SS_DIS,180,10);

  set_skill(SS_WEP_AXE,100);
  set_skill(SS_DEFENSE,90);
  set_skill(SS_PARRY,90);

  add_prop(GV_VILLAGER,1);
  set_alignment(VILLAGERALIGN);
  set_aggressive(0);
  set_alarm(0.5,0.0,equip_me);

  set_chat_time(10);
  add_chat("The goblins pay alright.");
  add_chat("Sometimes I miss the good dwarven pub. The one here stinks.");
  add_chat("I haven't heard from the mines for a long while...");

  set_default_answer("Do you want your weapon repaired?\n");

  add_ask(({"repair","polish","wax","sharpen"}),
	  BS(QCTNAME(TO) + " says: I can fix your weapon for a reasonable price.\n"));
  add_ask(({"price"}),
	  BS(QCTNAME(TO) + " says: My prices reflect the quality of my work.\n"));

  set_repair_base_cost(20);
  set_repair_incr_cost(5);
}
void
equip_me()
{
  setuid();
  seteuid(getuid());

  clone_object(SMHAMMER)->move(TO);
  clone_object(SMMAIL)->move(TO);
  clone_object(SMBOOTS)->move(TO);
  command("wear all");
  command("wield all");
  add_prop(OBJ_M_HAS_MONEY,VILLAGERFIN*24);
  
}
void
init_living()
{
  ::init_living();

  init_smith_repairs();
  
}
