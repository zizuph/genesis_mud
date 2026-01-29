#include "defs.h"

inherit "/std/object";

public void
create_object()
{
    set_name("pillar");
    set_pname("_foo_bar");
    add_name("obelisk");
    add_name("stone");
    set_adj("black");
    add_adj("stone");
    set_short("black stone pillar");
    set_long("The pillar is tall and dark, carved precisely " +
        "from some unknown, black stone. It looks like it " +
        "was probably rectangular in shape, originally, " +
        "but time and the elements have taken their toll, " +
        "and the obelisk now appears to be more of a " +
        "cone-capped cylinder roughly twice the size of " +
        "a man, both in girth and height.\n");

    add_prop(OBJ_I_VALUE, 0);
    add_prop(OBJ_I_WEIGHT, 2000000);
    add_prop(OBJ_I_VOLUME, 200000);
    add_prop(OBJ_M_NO_GET, "There's no way you're going to move " +
        "one of these things.\n");

    set_no_show_composite(1);
}
