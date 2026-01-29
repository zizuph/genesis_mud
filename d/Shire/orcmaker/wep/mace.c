#pragma save_binary

inherit "/std/weapon";
#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>
#include <formulas.h>
#include "/d/Shire/common/defs.h"

#define WEP_TYPE    W_CLUB
#define HIT            17
#define PEN            17
#define HANDS          W_ANYH
#define DAMAGE         W_BLUDGEON | W_IMPALE

void
create_weapon()
{
   set_name("mace");
   add_name(({"club"}));
   add_adj(({"iron"}));
   set_short("iron mace");
   set_pshort("iron maces");
   set_long("This is a rusty iron mace, wielded by malicious orcs, you can see "+
        "how the mace is shaped to fit the hand of an orc. Looks like it would "+
        "knock your lights out, though.\n");
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
