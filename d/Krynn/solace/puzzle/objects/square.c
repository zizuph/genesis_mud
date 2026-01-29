/* A wooden square. ~raorblade/puzzle/objects/square */

inherit "/std/object";

#include "/sys/stdproperties.h"

void create_object()
{
    set_name("square");
    set_adj("painted");
    add_adj("wooden");
    set_long("A square wooden block painted a bright green colour.\n");

    add_prop(OBJ_I_VALUE, 15);
    add_prop(OBJ_I_WEIGHT, 150);
    add_prop(OBJ_I_VOLUME, 200);
}
