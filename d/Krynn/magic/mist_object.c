/*
 * A mist object for the mist spell.
 */

inherit "/std/object";
inherit "/d/Krynn/rastlin/open/spells2/magic.object.c";

#include <stdproperties.h>

create_spell_object()
{
    add_prop(OBJ_I_LIGHT, -15000);
}

create_object()
{
    create_spell_object();

    set_no_show();
}

public void
init_spell()
{
    query_me()->add_prop(ROOM_S_DARK_LONG, "You are standing in a very " +
		   "foggy room. Here isn't much you can see due to " +
		   "the heavy mist.\n");

    query_me()->add_prop(ROOM_S_DARK_MSG, "The fog is too thick here to");
}

public
notify_spell_dispel(object ob)
{
    tell_room(query_me(), "The fog slowly blows away.\n");

    query_me()->remove_prop(ROOM_S_DARK_LONG);
    query_me()->remove_prop(ROOM_S_DARK_MSG);
}






