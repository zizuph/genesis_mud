/*
 * Goblin village barman
 * TAPAKAH 05/2005
 */

inherit "/d/Khalakhor/std/monster";
#include "../../nspeir.h"
#include "../../village/village.h"
#include "/d/Khalakhor/sys/defs.h";

inherit "../../base";

#include <ss_types.h>
#include <money.h>
#include <stdproperties.h>
#include <const.h>
#include <macros.h>

void equip_me();
     
void
create_khalakhor_monster()
{
  if(! IS_CLONE)
    return;
  ::create_khalakhor_monster();

  set_name("Grugh");
  set_race_name("goblin");
  set_adj("fat");
  add_adj("greedy");
  set_long(BSN("This is " + VILLAGENAME + " barman. He runs the pub and "+
	       "looks very content. He is lovingly polishing the bottles "+
	       "that are on the shelves of the pub, while the glasses and "+
	       "the plates stand dirty and untouched. Sometimes you notice "+
	       "him throwing a look at a top shelf where there are no bottles."
	       ));
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

  add_prop(GV_VILLAGER,1);
  set_alignment(VILLAGERALIGN);
  set_aggressive(0);
  set_alarm(0.5,0.0,equip_me);

  set_chat_time(10);
  add_chat("Nothing beats a nice whisky.");
  add_chat("I wish I could get to that distillery, but the humans won't let me in.");
  add_chat("We might be running out of beer.");

  set_default_answer("You want a drink or what?\n");

  add_ask(({"pub","bar","drink","bottle"}),
	  BS(QCTNAME(TO) + " says: Read the menu and see what I've got.\n"));
  add_ask(({"whisky","whiskey","distillery"}),
	  BS(QCTNAME(TO) + " says: There is a distillery in the fields north "+
	     "of Port Macdunn, but the guards won't let me in. Care to bring "+
	     "me some whisky?\n"));
  add_ask(({"beer"}),
	  BS(QCTNAME(TO) + " says: We need another keg of beer urgently.\n"));
}
void
equip_me()
{
  setuid();
  seteuid(getuid());

  clone_object(CLUB)->move(TO);
  clone_object(SHIRT)->move(TO);
  clone_object(BREECHES)->move(TO);
  command("wear all");
  command("wield all");
  add_prop(OBJ_M_HAS_MONEY,VILLAGERFIN*24);
  
}
