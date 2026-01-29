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
inherit "/d/Cirath/athas/gladiator/obj/cuirasss";
//inherit "/d/Cirath/athas/gladiator/log/manager.c";
//#pragma save_binary

#include "/d/Cirath/athas/gladiator/defs.h"

#include <stdproperties.h>
#include <macros.h>

#define CHEST_ROOM GLAD_ROOM+"gldchest.c"
#define TPISCOUNCIL (QUERY_COUN_MEMB(lower_case(TP->query_name())) > -1)
#define IS_GLAD_OVERSEER "_is_glad_overseer_"
void
create_rack()
{
   set_rack_guild_occ("Gladiator guild");
   set_rack_file("/d/Cirath/athas/gladiator/log/rack_state");
   set_rack_log_file("/d/Cirath/athas/gladiator/log/rack_log");
   set_name("chest");
   add_name("_gladiator_chest");
   set_adj("huge");
   add_adj("stone");
   set_short("huge stone chest");
   set_long("This rack is used to hold equipment for the "+
            "Gladiators so they can keep themselves supplied. As this "+
            "saves their master Kalak money, he encourages them to use, "+
            "supply, and defend it as they see fit. "+
            "The rack radiates powerful magic.\n");
 
   add_prop(CONT_I_MAX_WEIGHT, 9000000000);
   add_prop(CONT_I_MAX_VOLUME, 9900000000);
   add_prop(CONT_I_RIGID, 1);
   add_prop(OBJ_I_NO_GET, "Even a half-giant couldn't lift this thing.\n");
   
   seteuid(getuid());
}

int
query_admin_access(object ob)
{
   ob = TP;
   if (TP->query_prop(IS_GLAD_OVERSEER))
if (TP->query_wiz_level() > -1)
 /* if (TP->query_name() != "Lanjelin") */
return 0;
}

int
query_drop_access(object ob,object it)
{
    return test_guild_membership(ob);
}

int
query_loot_access(object ob,object it)
{
    return test_guild_membership(ob);
}
