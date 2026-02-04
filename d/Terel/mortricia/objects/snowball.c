/*
    A snowball. Mortricia 920902.
 */
inherit "/std/object";
#include <stdproperties.h>

init()
{
    add_action("throw", "throw");
    ::init();
}

create_object()
{
    set_name("snowball");
    set_short("snowball");
    set_long(break_string(
        "It's a snowball. Maybe you can throw it?\n",
        70));
    set_adj(({"white", "cold"}));
    add_prop(OBJ_I_VALUE, 1);
    add_prop(OBJ_I_WEIGHT, 50);
    add_prop(OBJ_I_VOLUME, 50);
}

throw(string what)
{
   if (what == "snowball" && present("snowball", this_player()) ) {
        this_object() -> move(environment(this_player()));
        return 1;
    }
    return 0;
}
