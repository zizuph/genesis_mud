/* This comment tells emacs to use c++-mode -*- C++ -*- */

#include "/d/Terel/include/Terel.h"
inherit STDMONSTER;

#include <money.h>
#include <ss_types.h>

/*
 * Function name: create_monster
 * Description:   Create the monster. (standard)
 */
public void
create_monster()
{
   if (!IS_CLONE) return;

   ::create_monster();
   set_name("boy");
   set_race_name("human");
   set_adj(({"dirty", "fish-smelling"}));
   set_long("He is a fish-smelling young lad. " +
	    "He definitely needs to wash off the dirt.\n");

   default_config_npc(15);
   set_all_hitloc_unarmed(10);
   
   set_skill(SS_DEFENCE,      10);
   set_skill(SS_UNARM_COMBAT, 10);

   set_gender(MALE);
   add_prop(LIVE_I_NEVERKNOWN, 1);
   add_prop(LIVE_I_QUICKNESS, 50);

   set_chat_time(5);
   add_chat("Hi!");
   add_chat("Have you been to the beach? Lotsa fun there!");
   add_chat("The beach is east of the village");

   seteuid(getuid());
   MONEY_MAKE_CC(3)->move(TO, 1);
}
