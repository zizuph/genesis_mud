/* Candlestick found in Kendermore, Gwyneth, June 1999 */

inherit "/std/object";

#include <macros.h>
#include "/d/Ansalon/common/defs.h"

void
create_object()
{
    set_name("candlestick");
    add_name("stick");
    set_adj("brass");
    set_short("brass candlestick");
    set_long("This candlestick looks like it may have come from an " + 
        "affluent household. It still has wax drippings along its side.\n");
    add_prop(OBJ_I_VALUE, 100);
    add_prop(OBJ_I_WEIGHT, 150);
    add_prop(OBJ_I_VOLUME, 150);
}

