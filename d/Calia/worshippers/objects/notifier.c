
inherit "/std/object";

#include <stdproperties.h>

public
create_object()
{
    set_name("notifier");
    set_short("bla");
    set_long("bla.\n");
    add_prop(OBJ_I_INVIS,100);
    add_prop(OBJ_I_NO_GET,1);
}

init()
{
    ::init();
    if (find_player("jaacar"))
    {
        tell_object(find_player("jaacar"),this_player()->query_name()+" just arrived at the ENTRANCE!\n");
}
}
