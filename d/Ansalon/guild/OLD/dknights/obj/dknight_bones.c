#include "/d/Ansalon/common/defs.h"
#include <wa_types.h>
#include <macros.h>
#include <ss_types.h>
#include <tasks.h>
#include <cmdparse.h>
inherit "/lib/keep";

inherit "/std/object";

void
remove_bones()
{
    write("The "+short()+" turns into dust and disappears in the wind.\n");
    this_object()->remove_object();
}

void
create_object()
{
    set_name("pile");
    set_name("bones");
    set_short("charred pile of human bones");
    set_long("This is a pile of human bones. Pieces of rotten flesh and "+
             "skin still covers some of the bones.\n");

    add_prop(OBJ_I_VOLUME, 6000);
    add_prop(OBJ_I_WEIGHT, 7000);
    add_prop(OBJ_I_VALUE, 0);

    set_alarm(200.0, 0.0, &remove_bones());
}
