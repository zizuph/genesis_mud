#include "../default.h"
inherit (STD + "weapon");

#include <wa_types.h>

void
create_weapon()
{
    ::create_weapon();

    set_name("knife");
    set_adj("rusty");
    add_adj("metal");  /* added by Gorboth, July 2007 */
    set_short("rusty knife");
    set_long("A large knife that appears weathered, one cause for the "+
      "many rust spots on the blade.\n");
    set_hit(9);
    set_pen(10);
    set_wt(W_KNIFE);
    set_dt(W_IMPALE);
    add_prop(OBJ_I_VALUE,180);
    add_prop(OBJ_I_WEIGHT,1000);
    add_prop(OBJ_I_VOLUME,1000);
}
