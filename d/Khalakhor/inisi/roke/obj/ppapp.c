/*
 * ppapp.c
 *
 * Used in npc/beggar.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Khalakhor by Glindor, Nov 2001.
 */

#pragma save_binary
#pragma strict_types

inherit "/std/object";

#include <stdproperties.h>

string
mylong()
{
    string s;

    s = "This is a piece of paper that looks completely useless.\n"+
        "It has been torn apart, and the text is unreadable.\n";

    if (objectp(this_player()) && present("sppapp", this_player()))
        return s + "It looks a little like the other paper you are carrying.\n"+
            "Perhaps is it possible to append this one to it.\n";
    return s;
}

void
create_object()
{
    set_short("old paper");
    set_long("@@mylong");

    set_name("paper");
    set_adj("old");
    add_name("ppapp");

    add_prop(OBJ_I_VALUE, 2);
}
