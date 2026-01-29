#include "../default.h"
inherit (STD + "weapon");

#include <wa_types.h>

void
create_weapon()
{
    ::create_weapon();

    set_name("sword");
    set_adj("thanar");
    add_adj("long");
    set_long("A finely crafted long sword. Upon the hilt, an image of a "+
      "dark sun has been engraved.\n");
    set_hit(24);
    set_pen(21);
    set_wt(W_SWORD);
    set_dt(W_SLASH);
    add_prop(OBJ_I_VALUE,480);
    add_prop(OBJ_I_WEIGHT,8000);
    add_prop(OBJ_I_VOLUME,8000);
}
