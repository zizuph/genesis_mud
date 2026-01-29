/*
 * Goblin village barman
 * TAPAKAH 05/2005
 */

#pragma strict_types

#include <ss_types.h>
#include <money.h>
#include <stdproperties.h>
#include <const.h>
#include <macros.h>

#include "/d/Khalakhor/sys/defs.h";

#include "../../daenbraigh.h"
#include "../../village/village.h"
#include "../../faction.h"

inherit "/d/Khalakhor/std/monster";
inherit DAENBRAIGH_NPC;

void equip_me();
     
void
create_khalakhor_monster()
{
  if(! IS_CLONE)
    return;
  ::create_khalakhor_monster();

  set_name("Grugh");
  add_name("barman");
  set_race_name("goblin");
  set_adj("fat");
  add_adj("greedy");
  set_long("This is " + VILLAGE_NAME + " barman. He runs the pub and "+
	   "looks very content. He is lovingly polishing the bottles "+
	   "that are on the shelves of the pub, while the glasses and "+
	   "the plates stand dirty and untouched. Sometimes you notice "+
	   "him throwing a look at a top shelf where there are no bottles.\n"
	   );
  set_gender(G_MALE);
  
  set_base_stat(SS_STR,100,10);
  set_base_stat(SS_DEX,80,10);
  set_base_stat(SS_CON,90,10);
  set_base_stat(SS_INT,60,10);
  set_base_stat(SS_WIS,60,10);
  set_base_stat(SS_DIS,80,10);

  set_skill(SS_WEP_CLUB,70);
  set_skill(SS_DEFENSE,50);
  set_skill(SS_PARRY,40);

  set_alignment(0);
  set_aggressive(0);
  set_faction(FACTION_DAENBRAIGH,FCT_VALUE_CRAFTSMAN);
  set_alarm(0.5,0.0,equip_me);

  set_chat_time(10);
  add_chat("Nothing beats a nice whisky.");
  add_chat("I wish I could get to that distillery, "+
	   "but the humans won't let me in."
	   );
  add_chat("We might be running out of beer.");

  set_default_answer("You want a drink or what?\n");

  add_ask(({"pub","bar","drink","bottle"}),
	  "say Read the menu and see what I've got.\n",
	  1);
  add_ask(({"whisky","whiskey","distillery"}),
	  "say There is a distillery in the fields north "+
	  "of Port Macdunn, but the guards won't let me in. Care to bring "+
	  "me some whisky?\n",
	  1);
  add_ask(({"beer"}),
	  "say We need another keg of beer urgently.",
	  1);
}

void
equip_me()
{
  setuid();
  seteuid(getuid());

  clone_object(V_HAMMER)->move(TO);
  clone_object(V_SHIRT)->move(TO);
  clone_object(V_BREECHES)->move(TO);
  command("wear all");
  command("wield all");
  add_prop(OBJ_M_HAS_MONEY,V_GOBLIN_MON*20);
  
}
