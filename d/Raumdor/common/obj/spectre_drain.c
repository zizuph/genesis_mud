/* drains strength for a time, Sarr 
 * 
 * 2021-03-03 - Cotillion
 * - Fixed throw and redid stat change, set time to 30 sec
 */
#include "defs.h"
inherit "/std/object";

#define DURATION 30 

public void
create_object()
{
    set_name("_spectre_drain");

    add_prop(OBJ_I_WEIGHT,  0);
    add_prop(OBJ_I_VOLUME,  0);
    add_prop(OBJ_M_NO_DROP, 1);

    set_no_show();
}


void
apply_effect(object target, int remove)
{
    int amount = 35 * (remove ? 1 : -1);

    target->set_stat_extra(SS_STR, target->query_stat_extra(SS_STR) + amount);
    target->set_stat_extra(SS_CON, target->query_stat_extra(SS_CON) + amount);
}


public void
remove_object()
{
    E(TO)->catch_tell( "You feel yourself regaining your strength and vigor.\n");
    apply_effect(E(TO), 1);
    ::remove_object();
}

public void
do_drain()
{
    object player = E(TO);

    if (!living(player))
    {
        remove_object();
        return;
    }

    player->catch_tell("You feel your strength and vigor drain rapidly!\n");
    tell_room(E(player), QCTNAME(player) +" looks much weaker.\n", player);

    apply_effect(player, 0);

    set_alarm(itof(DURATION), 0.0, remove_object);
}
