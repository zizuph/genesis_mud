inherit "/std/object";
/* drains strength for a time, Sarr */
#include "/d/Raumdor/defs.h"

public void
create_object()
{
    set_name("spector_drain");

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
drain(object victim)
{
    victim->catch_tell("You feel your strength and vigor drain rapidly!\n");
    tell_room(E(victim), QCTNAME(victim) +" looks much weaker.\n", victim);

    victim->add_tmp_stat(0,-35,1);
    victim->add_tmp_stat(2,-35,1);

    set_alarm(25.0, 0.0, remove_object);
}