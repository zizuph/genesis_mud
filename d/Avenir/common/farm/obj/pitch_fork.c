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
    set_name("pitch fork");
    add_name("_pitch_fork");
    add_name("fork");
    set_adj("old");
    set_short("old pitch fork");
    set_long("It is an old pitch fork created for work on a farm.\n");
    set_hit(10);
    set_pen(10);
    set_wt(W_POLEARM);
    set_dt(W_SLASH | W_BLUDGEON);
    set_hands(W_BOTH);
    set_wf(this_object());
    setuid();
    seteuid(getuid());
}

