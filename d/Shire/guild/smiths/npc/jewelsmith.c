/* 
 * Master Jewelsmith at Smiths Guild 
 * Palmer 12 Aug 2006
 * 
 */


inherit "/std/monster";

#include "/d/Shire/common/defs.h"
#include "/sys/stdproperties.h"
#include "/sys/ss_types.h"
#include "/sys/macros.h"
#include "../smiths.h"

#define NECKLACE SMITHSDIR_OBJ+"npc_neck"

void wield_me();

void
create_monster()
{
   if (!IS_CLONE)
      return;

   set_name(({"celedor","jewelsmith"}));
   set_title("of Grey Havens, Master Jewelsmith");
   set_race_name("grey-elf");
   set_adj("wise");
   set_long("Celedor is the Master Jewelsmith.\n");
   set_living_name("celedor");

             /* STR  DEX CON INT WIS DIS */
   set_stats(({ 170, 150, 160, 150, 170, 190 })); 
/*
   add_ask(({"island", "tolfalas"}),QCTNAME(TO)+" says to you: "+
      "The island Tolfalas is in the Bay of Belfalas. You may reach it by a ship that departs from the river Poros.\n");
   add_ask(({"gem", "enchanted gem"}),QCTNAME(TO)+" says to you: "+
      "I need an enchanted gem found only on an island in the south.\n");
*/
   add_ask(({"jewels","jewel", "gem", "jewlsmith"}),QCTNAME(TO)+" says to you: "+
      "I'm a bit busy now, but yes, I am a Jewelsmith.\n");

   add_ask(({"help","task","quest"}),QCTNAME(TO)+" says to you: "+
      "No.\n");

   //add_ask(({"help","task","quest"}),QCTNAME(TO)+" says to you: "+
   //   "I'm looking for an enchanted gem. Maybe you can get one for me.\n");
   set_alignment(750);
   set_skill(SS_UNARM_COMBAT,80);
   set_skill(SS_DEFENCE,80);

   set_alarm(2.0, 0.0, &wield_me());
}




void
wield_me() {
   object neck;

   seteuid(getuid(this_object()));

   neck = clone_object(NECKLACE);
   neck->set_short("jeweled platinum necklace");
   neck->set_adj("platinum");
   neck->move(this_object());
   command("wear necklace");
}

int
add_introduced(string name) 
{
   set_alarm(1.0, 0.0, &command("introduce me to " + name));
   return 1;
}

