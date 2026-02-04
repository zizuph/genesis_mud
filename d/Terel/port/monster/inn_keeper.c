/* This comment tells emacs to use c++-mode -*- C++ -*- */

/*
 * This is an NPC named "Csir".  He is called by inn.c, and exists
 * to serve and watch over the Inn.  If killed, the Inn is useless.
 */
 
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
   set_name("sirpat");
   set_race_name("human");
   set_adj("stout");
   set_long("He is a very stout human.\n");

   default_config_npc(40);
   set_all_hitloc_unarmed(25);
   
   set_skill(SS_DEFENCE,      40);
   set_skill(SS_UNARM_COMBAT, 40);

   set_gender(MALE);
   add_prop(LIVE_I_NEVERKNOWN, 1);
   add_prop(LIVE_I_QUICKNESS, 50);

   set_chat_time(5);
   add_chat("Welcome my friend! What would you like to eat?");
   add_chat("Why don't you try the soup today?");
}
