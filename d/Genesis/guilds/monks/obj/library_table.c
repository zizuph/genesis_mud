/*
 * File:     library_table
 * Created:  Cirion, 1998.06.07
 * Purpose:  table for the monk's library
 * Modification Log:
 */
#pragma strict_types

#include "defs.h"
#include <composite.h>
#include <filter_funs.h>
inherit MONK_OBJ + "table";
inherit MONKLIB;

void
create_table()
{
    set_name("table");
    add_name("library_table");
    set_adj(({"low","short","wide","wooden","library","wood"}));
    set_short("short wooden table");
    set_long("This is a low wooden table, held up by four thick, "
        + "unadorned legs. The surface of the table is very "
        + "smooth. Sunlight from the window falls directly on the "
        + "table, making it suitable for reading at.\n");
    set_describe_prefix(" In the center of the room is a short "
        + "and wide wooden table");

}

