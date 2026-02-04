/* Modified Leah for /pubs/big_pub.c  -- Tomas  Nov. 1999
* 
*/
inherit "/std/monster";
inherit "/d/Terel/include/log_asks";

#include "/sys/ss_types.h"
#include "/sys/macros.h"
#include <money.h>
#include "/d/Terel/include/Terel.h"


create_monster()
{
    /* We ignore the master object 
     */
    if (!IS_CLONE) 
        return;

   set_name("leah");
   set_race_name("human");
   set_adj("pretty");
   set_long("Leah is quite pretty. Yet, looks confident enough behind " +
      "the bar.\n");

    /* Average stat: 20 
     */
   default_config_npc(30);

    set_all_hitloc_unarmed(15);
   set_gender(1);
   set_chat_time(1);
   add_chat("Might I suggest the Sinvon. Its quite good!");
   
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
