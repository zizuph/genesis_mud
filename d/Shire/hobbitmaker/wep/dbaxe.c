inherit "/std/weapon";
#include "/d/Shire/common/defs.h"
#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>
#include <formulas.h>

#define WEP_TYPE    W_AXE
#define HIT            20
#define PEN            27
#define HANDS          W_ANYH
#define DAMAGE         W_SLASH

void
create_weapon()
{
    set_name("axe");
    add_name(({"axe"}));
    add_adj(({"large","double-bladed"}));
    set_short("large double-bladed axe");
    set_pshort("large double-bladed axes");
    set_long("This large double-bladed axe is perfect for"+
      "felling a tree or clearing thick underbrush.\n");
    set_default_weapon(HIT,PEN,WEP_TYPE,DAMAGE, HANDS, 0);
    add_prop(OBJ_I_WEIGHT,F_WEIGHT_DEFAULT_WEAPON(PEN,WEP_TYPE));
    add_prop(OBJ_I_VALUE,F_VALUE_WEAPON(HIT,PEN));
    add_prop(OBJ_I_VOLUME,F_VOLUME_WEAPON);

}
