inherit "/std/object";
#include "/d/Kalad/defs.h"
#include <cmdparse.h>

string
query_auto_load()
{
    return MASTER;
}

void
create_object()
{
    set_name("rag");
    set_adj("dirty");
    add_adj("damp");
    set_long("This is a small dirty rag, used to clean up around "+
    "a bar or Inn.\n");
    set_short("damp dirty rag");
}


