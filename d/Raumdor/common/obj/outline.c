#include "defs.h"
#define RAUMDOR_TRACED_GLYPH "_raumdor_traced_glyph"
inherit "/std/object";

void
create_object()
{
    set_name("outline");
    set_adj("door-shaped");
    set_long("It looks like some sort of magical entrance leading " +
        "behind the waterfall.\n");
    set_no_show_composite(1);
    add_prop(OBJ_I_NO_GET, 1);
}

public int
check_seen(object for_obj)
{
    if (for_obj->query_prop(RAUMDOR_TRACED_GLYPH))
        return ::check_seen(for_obj);
    return 0;
}

