inherit "/std/object";
#include "/sys/stdproperties.h"
#include "/d/Krynn/common/defs.h"
#include <macros.h>

void
create_object()
{
    set_name("note");
    add_name("paper");
    set_short("grease-stained piece of paper");
    set_pshort("grease-stained pieces of paper");
    set_long("A piece of paper so grease-stained " +
        "you can't make out any words on it.\n");
    add_cmd_item("paper", "read", "@@read");
    add_cmd_item("note", "read", "@@read");
}

read() { return query_long(); }
