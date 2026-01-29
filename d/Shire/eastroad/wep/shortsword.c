inherit "/std/weapon";
#include "/d/Shire/common/defs.h"
#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>
#include <formulas.h>

#define WEP_TYPE W_SWORD
#define HIT            25
#define PEN            21
#define HANDS          W_ANYH
#define DAMAGE         W_SLASH | W_IMPALE

void
create_weapon()
{
   set_name("sword");
   add_name(({"shortsword"}));
   add_adj(({"serrated","short"}));
   set_short("serrated shortsword");
   set_pshort("serrated shortswords");
   set_long("This serrated shortsword looks like a nasty weapon, "+
        "but quite old nonetheless. It is well-maintained and seems "+
        "like a trophy weapon.\n");
   set_default_weapon(HIT,PEN,WEP_TYPE,DAMAGE, HANDS, 0);
   add_prop(OBJ_I_WEIGHT,F_WEIGHT_DEFAULT_WEAPON(HIT,PEN));
   add_prop(OBJ_I_VALUE,F_VALUE_WEAPON(HIT,PEN));
   add_prop(OBJ_I_VOLUME,F_VOLUME_WEAPON);

}
