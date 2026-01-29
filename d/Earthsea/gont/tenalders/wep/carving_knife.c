#pragma strict_types

inherit "/std/weapon";

#include <wa_types.h>
#include <stdproperties.h>

public void
create_weapon()
{
    set_name("knife");
    add_name("_killian_carving_knife_");
    set_short("carving knife");
    set_long("A sharp knife for carving wood.\n");
    set_adj(({"carving","sharp"}));
    set_hit(8);
    set_pen(6);
    set_wt(W_KNIFE);
    set_dt(W_SLASH | W_IMPALE);
    set_hands(W_ANYH);
}
