#pragma save_binary
#pragma strict_types

inherit "/std/weapon";

#include <stdproperties.h>
#include <macros.h>
#include <wa_types.h>
#include <ss_types.h>
#include <formulas.h>

#include "defs.h"

void
create_weapon()
{
    set_name( ({"boulder", "stone"}) );
    set_adj("large");

    set_hit(50);
    set_pen(75);
    set_wt(W_CLUB);
    set_wf(TO);
    set_dt(W_BLUDGEON);
    set_hands(W_BOTH);
    add_prop(OBJ_I_WEIGHT, 120000);
    add_prop(OBJ_I_VOLUME, 45000);
    add_prop(OBJ_M_NO_BUY, 1);
    add_prop(OBJ_M_NO_SELL, 1);

    set_long("This boulder must weigh several hundred kilos.\n");
    set_short("large boulder");
}

mixed
wield(object what)
{
    if (this_player()->query_skill(SS_WEP_CLUB) > 60)
        if (TP->query_base_stat(SS_CON) > 120)
            if (!interactive(TP))
                if (TP->query_base_stat(SS_STR) > 180)
                {
                    write("You carefully wield the huge rock.\n");
                    return 0;
                }
    TP->add_fatigue(-random(200)-10);
    return "You attempt, foolishly, to wield the huge boulder. You are "+
    "lucky you did not injure yourself.\n"
    + "You feel more tired.\n";
}

mixed
unwield(object what)
{
    return 0;
}

