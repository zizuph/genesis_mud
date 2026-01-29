#pragma strict_types
inherit "/std/weapon.c";
inherit "/lib/keep";
#include <stdproperties.h>
#include <wa_types.h>
#include <ss_types.h>
#include <tasks.h>
#include <formulas.h>

void
create_weapon()
{
    set_name("knife");
    add_name("_labals_knife_");
    set_adj("dull");
    set_short("dull carving knife");
    set_long("This is a small little carving knife. " +
        "It looks very dull and cant be much of a use.\n");
    set_hit(5);
    set_pen(5);
    set_wt(W_KNIFE);
    set_dt(W_SLASH | W_BLUDGEON);
    set_hands(W_ANYH);
    set_wf(this_object());

 }
