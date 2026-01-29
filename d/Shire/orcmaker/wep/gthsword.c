#pragma save_binary

inherit "/std/weapon";
inherit "/lib/keep";

#include <wa_types.h>
#include "/d/Shire/common/defs.h"
#include <stdproperties.h>
#include <macros.h>
#include <formulas.h>

#define WEP_TYPE    W_SWORD
#define HIT            40
#define PEN            40
#define HANDS          W_BOTH
#define DAMAGE         W_SLASH

void
create_weapon()
{
   set_name("sword");
   add_adj(({"two","sharp","handed","two-handed"}));
   set_short("sharp two-handed sword");
   set_long("This is a "+short()+", used mostly by orcs, but is of "+
        "excellent craftsmanship. It looks like it would "+
        "do tremendous damage.\n");
   set_default_weapon(HIT,PEN,WEP_TYPE,DAMAGE, HANDS, 0);
   add_prop(OBJ_I_WEIGHT,F_WEIGHT_DEFAULT_WEAPON(PEN,WEP_TYPE));
   add_prop(OBJ_I_VOLUME, F_VOLUME_WEAPON);
   add_prop(OBJ_I_VALUE,F_VALUE_WEAPON(HIT,PEN));
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
