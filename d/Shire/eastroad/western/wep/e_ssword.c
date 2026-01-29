inherit "/std/weapon";
#include "/d/Shire/common/defs.h"
#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>
#include <formulas.h>
 
#define WEP_TYPE W_SWORD
#define HIT            27
#define PEN            23
#define HANDS          W_ANYH
#define DAMAGE         W_SLASH | W_IMPALE
 
void
create_weapon()
{
   set_name("sword");
   add_name(({"shortsword"}));
   add_adj(({"elven","short"}));
   set_short("elven shortsword");
   set_pshort("elven shortswords");
   set_long("This elven weapon is either a long knife or a "+
   "shortsword. You think it is probably a shortswod. It is "+
   "well-maintained and seems like it could possibly be a "+ 
   "deadly weapon.\n");
   set_default_weapon(HIT,PEN,WEP_TYPE,DAMAGE, HANDS, 0);
    add_prop(OBJ_I_WEIGHT,F_WEIGHT_DEFAULT_WEAPON(PEN,WEP_TYPE));
   add_prop(OBJ_I_VALUE,F_VALUE_WEAPON(HIT,PEN));
   add_prop(OBJ_I_VOLUME,F_VOLUME_WEAPON);
}
