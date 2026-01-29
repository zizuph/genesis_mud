#pragma save_binary

inherit "/std/weapon";
#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>
#include <formulas.h>
#include "/d/Shire/common/defs.h"

#define WEP_TYPE    W_KNIFE
#define HIT            13
#define PEN            13
#define HANDS          W_LEFT
#define DAMAGE         W_SLASH | W_IMPALE

void
create_weapon()
{
   set_name("knife");
   add_name(({"gauche"}));
   add_adj(({"sharp"}));
   set_short("sharp gauche");
   set_long("This is a sharp gauche, used by the smaller orcs, you can see "+
        "the shoddy craftsmanship all over it. Looks like it might "+
        "do some damage, though.\n");
   set_default_weapon(HIT,PEN,WEP_TYPE,DAMAGE, HANDS, 0);
   add_prop(OBJ_I_WEIGHT,F_WEIGHT_DEFAULT_WEAPON(PEN, WEP_TYPE));
   add_prop(OBJ_I_VALUE,F_VALUE_WEAPON(HIT,PEN));
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
