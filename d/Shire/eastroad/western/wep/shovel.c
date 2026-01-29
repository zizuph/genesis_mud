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
#define DAMAGE         W_BLUDGEON | W_IMPALE

void
create_weapon()
{
   set_name("polearm");
   add_name(({"shovel"}));
   add_adj(({"sturdy"}));
   set_short("sturdy shovel");
   set_long("This sturdy shovel is made of an iron shovel-head and "+
        "oak pole. It might be used as a weapon.\n");
   set_default_weapon(HIT,PEN,WEP_TYPE,DAMAGE, HANDS, 0);
   add_prop(OBJ_I_WEIGHT,F_WEIGHT_DEFAULT_WEAPON(PEN,WEP_TYPE));
   add_prop(OBJ_I_VALUE,F_VALUE_WEAPON(HIT,PEN));
   add_prop(OBJ_I_VOLUME,F_VOLUME_WEAPON);

}
