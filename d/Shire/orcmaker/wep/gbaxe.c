#pragma save_binary

inherit "/std/weapon";
inherit "/lib/keep";

#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>
#include <formulas.h>
#include "/d/Shire/common/defs.h"

#define WEP_TYPE    W_AXE
#define HIT            33
#define PEN            35
#define HANDS          W_BOTH
#define DAMAGE         W_SLASH

void
create_weapon()
{
   set_name("axe");
   add_name(({"axe"}));
   add_adj(({"broad"}));
   set_short("broad axe");
   set_pshort("broad axes");
   set_long("This is a broad axe, wielded by bigger orcs, you can see "+
        "how the axehead makes a wicked curve at the top. Looks like it would "+
       "do some wicked damage though.\n");
   set_default_weapon(HIT,PEN,WEP_TYPE,DAMAGE, HANDS, 0);
   add_prop(OBJ_I_VALUE,F_VALUE_WEAPON(HIT,PEN));
   add_prop(OBJ_I_VOLUME,F_VOLUME_WEAPON);
   add_prop(OBJ_I_WEIGHT,F_WEIGHT_DEFAULT_WEAPON(PEN,WEP_TYPE));
   set_keep();
}
   
string query_recover()
{
    return MASTER + ":" + query_wep_recover();
}

void
init_recover(string arg)
{
    init_wep_recover(arg);
}
