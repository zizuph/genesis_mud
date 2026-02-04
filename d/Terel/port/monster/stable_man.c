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
   if (!IS_CLONE) 	return;

   ::create_monster();
   set_name("skolla");
   set_race_name("human");
   set_adj(({"dirty", "horse-smelling"}));
   set_long("He is a horse-smelling human. He definately needs to wash off\n"+
            "the dirt.\n");

   default_config_npc(40);
   set_all_hitloc_unarmed(25);
   
   set_skill(SS_DEFENCE,      40);
   set_skill(SS_UNARM_COMBAT, 40);

   set_gender(MALE);
   add_prop(LIVE_I_NEVERKNOWN, 1);
   add_prop(LIVE_I_QUICKNESS, 50);

   set_chat_time(5);
   add_chat("Welcome my friend!");
   add_chat("Why don't you buy yourself a horse?");
}
