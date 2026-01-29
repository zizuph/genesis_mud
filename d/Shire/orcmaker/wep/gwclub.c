#pragma save_binary

inherit "/std/weapon";
#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>
#include <formulas.h>
#include "/d/Shire/common/defs.h"

#define WEP_TYPE    W_CLUB
#define HIT            22
#define PEN            16
#define HANDS          W_ANYH
#define DAMAGE         W_BLUDGEON

void
create_weapon()
{
   set_name("club");
   add_name(({"club"}));
   add_adj(({"wooden"}));
   set_short("wooden club");
   set_pshort("wooden clubs");
   set_long("This is a wooden club, wielded by poorer orcs, you can see "+
        "how the club was carved from a big piece of wood. Looks like it would "+
        "scare some hobbits, though.\n");
   set_default_weapon(HIT,PEN,WEP_TYPE,DAMAGE, HANDS, 0);
   add_prop(OBJ_I_VALUE,F_VALUE_WEAPON(HIT,PEN));
   add_prop(OBJ_I_WEIGHT,F_WEIGHT_DEFAULT_WEAPON(PEN,WEP_TYPE));
   add_prop(OBJ_I_VOLUME,F_VOLUME_WEAPON);

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
