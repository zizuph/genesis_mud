#include "../default.h"
inherit (STD + "weapon");

#include <wa_types.h>

void
create_weapon()
{
    ::create_weapon();

    set_name("dagger");
    set_adj("vicious");
    set_long("A brutal thug's dagger. The edge is extremely sharp, "+
      "probably sharp enough to slice off a man's fingers as easily as a "+
      "hot knife through butter.\n");
    set_hit(12);
    set_pen(10);
    set_wt(W_KNIFE);
    set_dt(W_IMPALE);
    add_prop(OBJ_I_VALUE,200);
    add_prop(OBJ_I_WEIGHT,1500);
    add_prop(OBJ_I_VOLUME,1500);
}
