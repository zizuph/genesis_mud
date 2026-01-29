inherit "/std/object";

#include "/d/Gondor/defs.h"

void decay();

void
create_object()
{
    set_name("pair of antlers");
    add_name(({"antlers","rack","horns","rock of horns"}));
    set_pname("pairs of antlers");
    set_adj(({"deer","large"}));
    set_short("pair of deer antlers");
    set_pshort("pairs of deer antlers");

    set_long("The large rack of horns of a grown deer buck.\n");
    set_alarm(1200.0, 0.0, decay);
}

void decay()
{
    tell_object(ENV(TO), "The pair of deer antlers decays, crumbling to dust.\n");
    remove_object();
}

