inherit "/std/weapon";
#include "/d/Shire/common/defs.h"
#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>
#include <formulas.h>

#define WEP_TYPE    W_CLUB
#define HIT            22
#define PEN            20
#define HANDS          W_ANYH
#define DAMAGE         W_BLUDGEON

void
create_weapon()
{
   set_name("hunk");
   add_name(({"club","hunk of iron"}));
   add_adj(({"long"}));
   set_short("long hunk of iron");
   set_pshort("long hunks of iron");
   set_long("This long hunk of metal is straight and smooth, probably "+
        "made as a weapon from leftover forge-iron.\n");
   set_default_weapon(HIT,PEN,WEP_TYPE,DAMAGE, HANDS, 0);
    add_prop(OBJ_I_WEIGHT,F_WEIGHT_DEFAULT_WEAPON(PEN,WEP_TYPE));
   add_prop(OBJ_I_VALUE,F_VALUE_WEAPON(HIT,PEN));
   add_prop(OBJ_I_VOLUME,F_VOLUME_WEAPON);

}
