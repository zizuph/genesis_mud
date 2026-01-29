/*  This is an NPC named "Jenna".  She is called by inn.c, and exists
 * to serve and watch over the Inn.  If killed, the Inn is useless.
 *
 * Coded by Vader on 7/2/92
 *
*/
inherit "/std/monster";

#include "/sys/ss_types.h"
#include "/sys/macros.h"
#include <money.h>


create_monster()
{
    /* We ignore the master object 
     */
    if (!IS_CLONE) 
	return;

   set_name("jenna");
   set_race_name("human");
   set_adj("long-haired");
   set_long("She is a very outgoing girl, with VERY long hair.\n");

    /* Average stat: 20 
     */
   default_config_npc(30);

    set_all_hitloc_unarmed(15);
   set_gender(1);
   set_chat_time(1);
   add_chat("My beaver stew is from an ancient recipe handed down "
    + "from my mother.");
   add_chat("How would you like some Jerky for the road?");
}
/*
 * Find some player somewhere and go there
 */
find_someone(name)
{
    object ob;

    ob = find_player(name);

    if (!ob)
	return 0;

    move_living("X",environment(ob));
    return 0;
}
