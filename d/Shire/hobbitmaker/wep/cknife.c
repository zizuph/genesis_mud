inherit "/std/weapon";
#include "/d/Shire/common/defs.h"
#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>
#include <formulas.h>

#define WEP_TYPE    W_KNIFE
#define HIT            20
#define PEN            13
#define HANDS          W_ANYH
#define DAMAGE         W_SLASH

void
create_weapon()
{
    set_name("knife");
    add_name(({"knife"}));
    add_adj(({"curved"}));
    set_short("curved knife");
    set_pshort("curved knives");
    set_long("This is a curved knife, probably used for carving"+
      "wood or other similar semi-tough objects.\n");
    set_default_weapon(HIT,PEN,WEP_TYPE,DAMAGE, HANDS, 0);
    add_prop(OBJ_I_WEIGHT,F_WEIGHT_DEFAULT_WEAPON(PEN,WEP_TYPE));
    add_prop(OBJ_I_VALUE,F_VALUE_WEAPON(HIT,PEN));
    add_prop(OBJ_I_VOLUME,F_VOLUME_WEAPON);

}
