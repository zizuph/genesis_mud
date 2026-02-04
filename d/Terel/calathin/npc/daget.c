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
#include "/d/Terel/include/Terel.h"

#define HUNTING_TREVIN "_i_hunting_trevin"
#define TALKED_TO_INNKEEP "_i_talked_innkeep"

public string
reply_assassin()
{
    if(TP->query_prop(HUNTING_TREVIN))
    {
          command("say Yeah the adventurer said he was searching for "+
                         "a guy.");
          command("say Kept claiming clapping was the key.");
          TP->add_prop(TALKED_TO_INNKEEP,1);
          return "";
    }
    return "";
}


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
    add_ask(({"adventurer","clapping"}), reply_assassin, 1);
    add_chat("Some crazy adventurer came in here not long ago clapping in all the rooms here. Clapping clapping clapping. Silly bastard.");
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
