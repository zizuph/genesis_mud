/* drains strength for a time, Sarr */
#include "defs.h"
inherit "/std/object";

#define DURATION 3

void
create_object()
{
    set_name("_wraith_drain");
    add_prop(OBJ_I_WEIGHT,0);
    add_prop(OBJ_I_VOLUME,0);
    add_prop(OBJ_M_NO_DROP,1);
    set_no_show();
}

void
remove_object()
{
    E(TO)->catch_tell("You feel yourself regaining your strength.\n");
    ::remove_object();
}


void
do_drain()
{
    object player = E(TO);
    if (!interactive(player))
        throw("Player expected to be interactive");

    player->catch_msg("You feel your strength drain.\n");
    tell_room(E(player), QCTNAME(player) +" looks weaker.\n", player);
    TP->add_tmp_stat(0, -20, DURATION);
    set_alarm(itof(DURATION * F_INTERVAL_BETWEEN_HP_HEALING), 0.0,
      remove_object);
}


