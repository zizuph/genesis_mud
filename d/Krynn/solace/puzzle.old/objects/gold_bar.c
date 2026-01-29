/* A bar of pure gold. ~solace/puzzle/objects/gold_bar */

inherit "/std/object";

#include "/sys/stdproperties.h"

void create_object()
{
    set_name("gold");
    add_name("bar");
    set_adj("bar of");
    set_long("The gold bar gleams in the light. It looks very expensive.\n");

    add_prop(OBJ_I_VOLUME, 1300);
    add_prop(OBJ_I_WEIGHT, 4000);

    add_prop(OBJ_I_VALUE, 1000 + random(501));
}
