#include "/d/Terel/include/Terel.h"

inherit STDOBJECT;

object owner;
string glyph_exit;

public void
create_object()
{
    set_name("a glyph");
    set_long("a glyh.\n");
}

set_owner(object player)
{
    owner = player;
}

set_glyph(string exit, object room)
{
    glyph_exit = exit ;
}

trigger()
{
    TP->catch_msg("A strange feeling passes over you.\n");
    owner->catch_msg(QCTNAME(TP) + " triggered the glyph.\n");
    set_alarm(300.0, -1.0, "remove_object");
}

public void
remove_object()
{
    int index;
    mixed exits;
    object room = environment();

    exits = room->query_exit();
    if ((index = member_array(glyph_exit, exits)) > -1)
    {
        room->remove_exit(glyph_exit);
        room->add_exit(exits[index-1], glyph_exit);
    }
    ::remove_object();
}
