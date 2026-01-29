/* Quest Dagger, Sarr */
#include "defs.h"

inherit "/std/weapon";

void
create_weapon()
{
    ::create_weapon();
    set_name("dagger");
    set_adj("black");
    add_adj("ceremonial");
    set_short("black ceremonial dagger");
    set_long(
      "This black dagger made of steel is decorated with tiny silver lines. " +
      "On the hilt, you see a grim skull with two tiny green gems for " +
      "eyes.\n");
    set_wt(W_KNIFE);
    set_dt(W_SLASH | W_IMPALE);
    set_pen(10);
    set_hit(12);
    add_prop(OBJ_I_VOLUME, 300);
    add_prop(OBJ_I_WEIGHT, 900);
    add_prop(OBJ_I_VALUE, 100);
}
