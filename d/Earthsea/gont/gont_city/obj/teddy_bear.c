#pragma strict_types

inherit "/std/object";

#include <stdproperties.h>
#include <macros.h>

public void
create_object()
{
    set_name("bear");
    set_adj("teddy");
    add_adj("fuzzy");
    set_short("teddy bear");
    set_long("A fuzzy brown teddy bear. It looks very "+
        "cuddly and huggable.\n");
    add_cmd_item((({"bear", "teddy bear"})), "hug", "@@hug_bear");
    add_prop(OBJ_I_WEIGHT, 300);
    add_prop(OBJ_I_VOLUME, 200);
    add_prop(OBJ_I_VALUE, 10);
}

public string
hug_bear()
{
    object tp = this_player();
    tell_room(environment(tp), QCTNAME(tp) + " hugs a fuzzy "+
        "brown teddy bear.\n", ({tp}));
    return "You hug the fuzzy brown teddy bear. The world looks "+
        "much brighter now.\n";
}

public int
query_kerrus_bear()
{
    return 1;
}
