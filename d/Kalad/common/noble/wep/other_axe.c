inherit "/d/Kalad/std/weapon";
#include "/d/Kalad/defs.h"

/* Sarr */


void
create_weapon()
{
    ::create_weapon();
    set_name("battleaxe");
    add_name("axe");
    set_adj("huge");
    add_adj("golden");
    set_short("huge golden battleaxe");
    set_long("A large axe with a huge, deadly looking blade. The "+
    "handle is made of polished white-oak wood, and the blade gleams "+
    "gold-like in the light.\n");
    set_dt(W_SLASH);
    set_wt(W_AXE);
    set_hit(25);
    set_pen(30);
    KVWEP(20);
    KWWEP(30);
    KVOL(steel);
}
