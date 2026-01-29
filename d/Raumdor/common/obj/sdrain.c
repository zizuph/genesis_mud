/* drains strength for a time, Sarr */
#include "../defs.h"
inherit "/std/object";

#define DURATION 1

public void
create_object()
{
    set_name("_spectre_drain");

    add_prop(OBJ_I_WEIGHT,  0);
    add_prop(OBJ_I_VOLUME,  0);
    add_prop(OBJ_M_NO_DROP, 1);

    set_no_show();
}

public void
remove_object()
{
    E(TO)->catch_tell(
      "You feel yourself regaining your strength and vigor.\n");
    ::remove_object();
}

public void
do_drain()
{
    object player = E(TO);
    if (!interactive(player))
        throw("Player expected to be interactive");

    player->catch_tell("You feel your strength and vigor drain rapidly!\n");
    tell_room(E(player), QCTNAME(player) +" looks much weaker.\n", player);

    player->add_tmp_stat(0, -35, DURATION);
    player->add_tmp_stat(2, -35, DURATION);

    set_alarm(itof(DURATION * F_INTERVAL_BETWEEN_HP_HEALING), 0.0,
      remove_object);
}
