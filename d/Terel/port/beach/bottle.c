/* An empty bottle. Mortricia Dec 94  */
inherit "/std/object";
#include <stdproperties.h>
#include <macros.h>

#define ADJS ({"green", "transparent", "blue", "yellow"})

public void
create_object()
{
    string adj;

    adj = ADJS[random(sizeof(ADJS))];

    set_name("bottle");
    set_adj(adj);
    set_long("This " + adj + " bottle looks very old. It's empty.\n");
    add_prop(OBJ_I_VALUE, 10 + random(4));
    add_prop(OBJ_I_WEIGHT, 100);
    add_prop(OBJ_I_VOLUME, 100);
}
