inherit "/std/object";

#include <macros.h>
#include <stdproperties.h>

void
create_object()
{
    set_name("beeper");
    set_adj("mystic");
    set_long("It looks ... mystical!\n");

    add_prop(OBJ_M_NO_DROP, 1);
}

void
init()
{
    ::init();
    add_action("do_beep", "beep");
}


int
do_beep(string arg)
{
    object ob;

    notify_fail("Beep whom?\n");
    if (!arg || !(ob = find_player(arg)))
        return 0;
    tell_object(ob, "^G");
    write("Ok.\n");
    return 1;
}

string
query_auto_load()
{
    return MASTER;
}
