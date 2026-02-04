/*  This is an NPC named "mogue".  He is called by pub.c, and exists
 * primarilly to keep the customers company.  In the future, he 
 * can give small hints to area quests.
 *
 * Coded by Vader on 6/27/92
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

   set_name("mogue");
   set_race_name("human");
   set_adj("ancient");
set_long("This is a very old human, who seems to spend all of his "
 + "time here.\n");

    /* Average stat: 20 
     */
   default_config_npc(12);

    /* But we want it to have more hitpoints
     */
   set_hp(150);

    set_all_hitloc_unarmed(15);

   set_chat_time(2);
   add_chat(break_string("In my day, we didn't have these nice swords!!!  We "
    + "killed monsters with our BARE HANDS!!!!", 47));
     add_chat("Oh, how my back hurts!!!");
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
