/* The gladiator chest: Godfire.
 * Corrupted by Serpine on 4-24-95
 *
 * File: /d/Cirath/athas/gladiator/obj/chest3.c
 *
 * Comments: 14 juli 2001 - Makeing the chest autosaving, and a log file included +
 *                          some new features that can be found on help rack. Lanjelin
 *           23 juli 2001 - Makeing the chest bigger, and more chests/racks. Lanjelin
 */

inherit "/lib/guild_rack";
inherit "/d/Cirath/athas/gladiator/log/manager.c";

#include "/d/Cirath/athas/gladiator/defs.h"
#include <stdproperties.h>
#include <macros.h>

#define CHEST_ROOM GLAD_ROOM+"gldchest.c"
#define TPISCOUNCIL (QUERY_COUN_MEMB(lower_case(TP->query_name())) > -1)

void
create_rack()
{
   set_rack_guild_occ("Gladiator guild");
   set_rack_file("/d/Cirath/athas/gladiator/log/rack_state3");
   set_rack_log_file("/d/Cirath/athas/gladiator/log/rack_log");
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
      if (!TPISCOUNCIL)
//      if (!TPISCOUNCIL && !IS_WIZ(TP) && !CIR_WIZ(TP))
      return 1;
//      return call_other(MANAGER, "query_coun_memb");
}
