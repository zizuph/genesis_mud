inherit "/std/weapon";
#include "/d/Shire/common/defs.h"
#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>
#include <formulas.h>

#define WEP_TYPE W_SWORD
#define HIT            17
#define PEN            18
#define HANDS          W_ANYH
#define DAMAGE         W_SLASH | W_IMPALE

void
create_weapon()
{
   set_name("sword");
   add_name(({"rapier"}));
   add_adj(({"rusty"}));
   set_short("rusty rapier");
   set_pshort("rusty rapiers");
   set_long("This rusty rapier looks to be an heirloom of a "+
        "sea-going sailor, as evidenced by the salt corrosion.\n");
   set_default_weapon(HIT,PEN,WEP_TYPE,DAMAGE, HANDS, 0);
   add_prop(OBJ_I_WEIGHT,F_WEIGHT_DEFAULT_WEAPON(PEN,WEP_TYPE));
   add_prop(OBJ_I_VALUE,F_VALUE_WEAPON(HIT,PEN));
   add_prop(OBJ_I_VOLUME,F_VOLUME_WEAPON);

}
