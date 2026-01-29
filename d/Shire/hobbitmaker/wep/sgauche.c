inherit "/std/weapon";
#include "/d/Shire/common/defs.h"
#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>
#include <formulas.h>

#define WEP_TYPE    W_KNIFE
#define HIT            15
#define PEN            24
#define HANDS          W_ANYH
#define DAMAGE         W_IMPALE

void
create_weapon()
{
   set_name("knife");
   add_name(({"gauche"}));
   add_adj(({"sharp"}));
   set_short("sharp gauche");
   set_pshort("sharp gauches");
   set_long("This sharp gauche is old and worn, probably an heirloom "+
        "from days gone by.\n");
   set_default_weapon(HIT,PEN,WEP_TYPE,DAMAGE, HANDS, 0);
   add_prop(OBJ_I_WEIGHT,F_WEIGHT_DEFAULT_WEAPON(PEN,WEP_TYPE));
   add_prop(OBJ_I_VALUE,F_VALUE_WEAPON(HIT,PEN));
   add_prop(OBJ_I_VOLUME,F_VOLUME_WEAPON);

}
