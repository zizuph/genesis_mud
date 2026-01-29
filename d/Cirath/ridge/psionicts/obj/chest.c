/* The gladiator chest: Godfire.
 * Corrupted by Serpine on 4-24-95
 *
 * File: /d/Cirath/athas/gladiator/obj/chest.c
 *
 * Comments: 14 juli 2001 - Makeing the chest autosaving, and a log file included +
 *                          some new features that can be found on help rack. Lanjelin
 *           23 juli 2001 - Makeing the chest bigger, and more chests/racks. Lanjelin
 */

inherit "/lib/guild_rack";
//#pragma save_binary

//inherit "/std/container";
#include "defs.h"
#include <stdproperties.h>
#include <macros.h>

#define CHEST_ROOM PSION_ROOM+"gldchest.c"
 
void
create_rack()
{
   set_rack_guild_occ("Psionict guild");
   set_rack_file(PSION_LOG + "rack_state");
   set_rack_log_file(PSION_LOG + "rack_log");
   set_name("chest");
   add_name("_gladiator_chest");
   set_adj("huge");
   add_adj("stone");
   set_long("This rack is used to hold equipment for the "+
            "Gladiators so they can keep themselves supplied. As this "+
            "saves their master Kalak money, he encourages them to use, "+
            "supply, and defend it as they see fit. "+
            "The rack radiates powerful magic.\n");
 
   add_prop(CONT_I_MAX_WEIGHT, 800000000);
   add_prop(CONT_I_MAX_VOLUME, 1400000000);
   add_prop(CONT_I_RIGID, 1);
   add_prop(OBJ_I_NO_GET, "Even a half-giant couldn't lift this thing.\n");
   
//   seteuid(getuid());
}

int
query_admin_access(object ob)
{
//    return test_guild_leadership(ob);
      return call_other(MANAGER, "query_overseer");
}


/*public int
kick_chest()
{
 object *inv, env, x;
 int i,size,num;

 inv = all_inventory();
 env = environment();
 num = 0;

 size = sizeof(inv);

 for(i = 0; i < size; i++)
 {
  x = inv[i];

  if(x->check_recoverable() != 1)
  {
   x->move(env);
   num++;
  }
 }

 return num;
}*/