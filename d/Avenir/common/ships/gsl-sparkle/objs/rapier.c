#pragma strict_types
// name: Rapier  ~Avenir/common/ships/sparkle/rapier.c
// creator(s):   Tepisch  Nov 1994
// purpose:      To be wielded by captain
// last update:  Boriska, Mar 23 1995
//
// * Lucius May 2009: Removed unused bits, cleaned up.
//
inherit "/std/weapon";

#include <wa_types.h>
#include <stdproperties.h>

public void
create_weapon(void)
{
    set_name("rapier");
    set_short("elegant rapier");
    set_pname("rapiers");
    set_pshort("elegant rapiers");
    set_adj("elegant");
    set_long("This is narrow blade is long and slightly flexible.\n"+
      "It is so light in the hand that wielding it for long periods "+
      "is unlikely to cause fatigue.\n");
    set_hit(30);
    set_pen(20);
    set_wt(W_SWORD);
    set_dt(W_IMPALE | W_SLASH);
    set_hands(W_ANYH);
}
