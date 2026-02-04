/*
    A handful of snow. Mortricia 920902.
 */
inherit "/std/object";
#include <stdproperties.h>

init()
{
    add_action("make", "make");
    ::init();
}

create_object()
{
    set_name("snow");
    set_short("handful of snow");
    set_pshort("piles of snow");
    set_long(break_string(
        "It's a handful of white snow. You feel cold when you touch it.\n",
        70));
    set_adj(({"white", "cold"}));
    add_prop(OBJ_I_VALUE, 1);
    add_prop(OBJ_I_WEIGHT, 50);
    add_prop(OBJ_I_VOLUME, 50);
}

make(string what)
{
    if (what == "snowball" && present("snow", this_player()) ) {
        clone_object("/d/Terel/mortricia/objects/snowball") -> move(this_player());
        this_object() -> remove_object();
        return 1;
    }
    return 0;
}
