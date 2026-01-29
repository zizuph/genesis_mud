/* created by Aridor 07/06/93 */

inherit "/std/object";

#include "../local.h"
#include <stdproperties.h>

create_object()
{
    set_name("spark");
    set_long("It is a spark which could easily cause a fire.\n");
    add_prop(OBJ_I_VALUE, 0);
    add_prop(OBJ_I_WEIGHT, 0);
    add_prop(OBJ_I_VOLUME, 2);
    add_prop(OBJ_I_HAS_FIRE, 1);
    add_prop(OBJ_M_NO_GET,"You try for a while, but the spark is too " +
        "flimsy to be caught.\n");
    wear_off();
}

remove_spark()
{
    seteuid(getuid(this_object()));
    tell_room(environment(this_object()),"The spark burns out.\n");
    this_object()->remove_object();
}


wear_off()
{
    set_alarm(itof(random(10) + 15),0.0,"remove_spark");
}

come_flying()
{
    tell_room(environment(this_object()),"A spark of fire comes flying in.\n");
}
