#pragma save_binary

inherit "/std/weapon";
#include "/d/Shire/common/defs.h"
#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>
#include <formulas.h>

#define WEP_TYPE    W_POLEARM
#define HIT            17
#define PEN            22
#define HANDS          W_BOTH
#define DAMAGE         W_SLASH

void
create_weapon()
{
   set_name("polearm");
   add_name(({"glaive"}));
   add_adj(({"heavy"}));
   set_short("heavy glaive");
   set_long("This is a heavy glaive, is full of evil, you can see "+
        "the evil orc signs all over it. Looks like it would "+
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
