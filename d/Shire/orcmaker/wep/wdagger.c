#pragma save_binary

inherit "/std/weapon";
#include "/d/Shire/common/defs.h"
#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>
#include "/d/Shire/common/defs.h"
#include <formulas.h>

#define WEP_TYPE    W_KNIFE
#define HIT            8
#define PEN            8
#define HANDS          W_ANYH
#define DAMAGE         W_SLASH | W_IMPALE

void
create_weapon()
{
   set_name("knife");
   add_name(({"dagger"}));
   add_adj(({"jagged"}));
   set_short("jagged dagger");
   set_long("This is a jagged dagger, used by the smaller orcs, you can see "+
        "the shoddy craftsmanship all over it. Looks like it might "+
        "do some damage, though.\n");
   set_default_weapon(HIT,PEN,WEP_TYPE,DAMAGE, HANDS, 0);
   add_prop(OBJ_I_VALUE,F_VALUE_WEAPON(PEN,WEP_TYPE));
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
