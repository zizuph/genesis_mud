/* Calian Name List by Glykron 31. 3.95 */

#include <composite.h>
#include "defs.h"

inherit "std/object";
inherit GLYKRON_SPECIALS + "calian_code";

string *names;

void
long_desc()
{
    restore_object(OBJECT("calians"));

    return
        "It is a scroll with calligraphic writing on it.  " +
        "It says:\n" +
        "Type \"register\" to get your name on this list.  " +
        "Type \"register\" <name> to get another Calian's name on this " +
        "list.  " +
        "Here is a list of the registered Calians:\n" +
        COMPOSITE_LIVE(names) +
        "\n";
}

void
create_object()
{
    set_name( ({ "list", "scroll" }) );
    set_adj( ({ "fancy", "calligraphic" }) );
    set_long("@@long_desc");
}

int
register(string name)
{
    object player = name == "" ? THIS : find_player(name);

    if (!player)
        return 0;

    restore_object(OBJECT("calians"));

    if (!player->is_calian())
    {
        write(capitalize(name) + " is not a Calian.\n");
        return 0;
    }

    if (member(name, names))
    {
        write(capitalize(name) + " has already been registered.\n");
        return 0;
    }

    names += ({ name });
    save_object(OBJECT("calians"));
    write(capitalize(name) + " has been registered.\n");
}

void
init()
{
    ::init();
    add_action("register", "register");
}
