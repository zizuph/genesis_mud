inherit "/std/weapon";
inherit "/lib/keep";

#include "../local.h"
#include "/d/Ansalon/common/defs.h"

#include <stdproperties.h>
#include <wa_types.h>

#define HIT 30
#define PEN 32

void
create_weapon()
{
    set_name("sword");
    set_adj(({"narrow","sharp"}));
    add_adj("metal");  /* it is, isn't it? -Gorboth */
    
    set_short("narrow sharp sword");
    set_long("The narrow sword looks sharp and deadly. The hilt is bound " +
    "in strips of leather and provides a good grip.\n");
    
    set_hit(HIT);
    set_pen(PEN);
    set_wt(W_SWORD);
    set_hands(W_ANYH);
    set_dt(W_IMPALE | W_SLASH);
    
    add_prop(OBJ_I_WEIGHT, 3000);
    add_prop(OBJ_I_VOLUME, 2000);
    
}

