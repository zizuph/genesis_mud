/*
 * Hammerhands shopkeeper
 * TAPAKAH 10/2005
 */

#pragma strict_types

#include <ss_types.h>
#include <money.h>
#include <stdproperties.h>
#include <const.h>
#include <macros.h>

#include "/d/Khalakhor/sys/defs.h"

#include "../../daenbraigh.h"
#include "../../hhands/hhands.h"
#include "../../faction.h"

inherit "/d/Khalakhor/std/monster";
inherit DAENBRAIGH_NPC;

void
create_khalakhor_monster()
{
  if(! IS_CLONE)
    return;
  ::create_khalakhor_monster();

  set_name(({"shopkeeper","Thyrh"}));
  set_race_name("dwarf");
  set_adj("thick-armed");
  set_long("This dwarf is one of the few that left the dwarven mines "+
	   "in search of a better living through trading with northern "+
	   "goblins and their Hammerhands guild, where he set his shop.\n");
  set_gender(G_MALE);
  
  set_base_stat(SS_STR,150,10);
  set_base_stat(SS_DEX,60,10);
  set_base_stat(SS_CON,160,10);
  set_base_stat(SS_INT,90,10);
  set_base_stat(SS_WIS,90,10);
  set_base_stat(SS_DIS,150,10);

  set_skill(SS_WEP_CLUB,75);
  set_skill(SS_PARRY,50);
  set_skill(SS_DEFENSE,50);
  set_skill(SS_UNARM_COMBAT,40);

  add_prop(HH_MEMBER,HH_ACCESS_MEMBER);
  set_faction(FACTION_DAENBRAIGH,FCT_VALUE_HH_NPC);
  
  add_prop(OBJ_M_NO_ATTACK,"You feel yourself unable to do that.\n");
  add_prop(OBJ_M_NO_MAGIC_ATTACK,"You feel yourself unable to do that.\n");
}

