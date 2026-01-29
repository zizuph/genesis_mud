inherit "/std/object.c";
#include "/d/Emerald/outpost1/defs.h"

void
create_object()
{
    set_name("cot");
    set_adj("wooden");
    add_adj("hay-covered");
    set_short("a hay-covered wooden cot");
    set_long("This cot is made from de-barked wooden logs with a hay " +
        "matress on it. It looks somewhat comforatble but dirty.\n");
    add_prop(OBJ_M_NO_GET, 1);
}
