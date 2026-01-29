inherit "/std/weapon";
#include "/d/Shire/common/defs.h"
#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>
#include <formulas.h>

#define WEP_TYPE    W_POLEARM
#define HIT            19
#define PEN            25
#define HANDS          W_BOTH
#define DAMAGE         W_SLASH | W_IMPALE

void
create_weapon()
{
   set_name("polearm");
   add_name(({"pitchfork"}));
   add_adj(({"spiked"}));
   set_short("spiked pitchfork");
   set_long("This spiked pitchfork has many sharp tines "+
        "and is quite strong. You wouldn't want to be hay if "+
        "this thing were around!\n");
   set_default_weapon(HIT,PEN,WEP_TYPE,DAMAGE, HANDS, 0);
   add_prop(OBJ_I_WEIGHT,F_WEIGHT_DEFAULT_WEAPON(HIT,PEN));
   add_prop(OBJ_I_VALUE,F_VALUE_WEAPON(HIT,PEN));
   add_prop(OBJ_I_VOLUME,F_VOLUME_WEAPON);

}
