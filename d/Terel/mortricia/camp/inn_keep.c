/*  This is an NPC named "Csir".  He is called by inn.c, and exists
 * to serve and watch over the Inn.  If killed, the Inn is useless.
 */
inherit "/std/monster";

#include "/sys/ss_types.h"
#include "/sys/macros.h"
#include <money.h>
#include <ss_types.h>
#include <stdproperties.h>

create_monster()
{
   if (!IS_CLONE) 
	return;

   set_name("Csir");
   set_race_name("gypsy");
   set_adj("stout");
   set_long("He is a very stout gypsy.\n");

   default_config_npc(40);
   set_all_hitloc_unarmed(25);
   set_skill(SS_DEFENCE, 40);
   set_skill(SS_UNARM_COMBAT, 40);

   set_gender(0);
   add_prop(LIVE_I_NEVERKNOWN, 1);
   add_prop(LIVE_I_QUICKNESS, 50);

   set_chat_time(5);
   add_chat("Welcome my friend! What would you like to eat?\n");
   add_chat("Why don't you try the soup today?\n");
}
