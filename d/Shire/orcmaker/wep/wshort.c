#pragma save_binary

inherit "/std/weapon";
#include "/d/Shire/common/defs.h"
#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>
#include <formulas.h>

#define WEP_TYPE    W_SWORD
#define HIT            14
#define PEN            15
#define HANDS          W_ANYH
#define DAMAGE         W_SLASH

void
create_weapon()
{
   set_name("sword");
   add_name(({"shortsword"}));
   add_adj(({"short"}));
   set_short("shortsword");
   set_long("This is a shortsword, used mostly by orcs, you can see "+
        "the shoddy craftsmanship all over it. Looks like it would "+
        "do some damage, though.\n");
   set_default_weapon(HIT,PEN,WEP_TYPE,DAMAGE, HANDS, 0);
   add_prop(OBJ_I_WEIGHT,F_WEIGHT_DEFAULT_WEAPON(PEN,WEP_TYPE));
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
