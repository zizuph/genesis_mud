
#pragma strict_types

inherit "/std/object";
#include <stdproperties.h>
#include <macros.h>
#include "defs.h"

string apprentice_chosen = "";
string apprentice = "";

void
create_object()
{
    set_name("_have_chosen_");
    add_prop(OBJ_I_WEIGHT,0);
    add_prop(OBJ_I_VOLUME,0);
    add_prop(OBJ_I_NO_DROP,1);
    add_prop(OBJ_I_NO_STEAL,1);
    set_no_show();
}

string
query_auto_load()
{
    return MASTER + ":" + apprentice_chosen;
}

int
do_promote(string str)
{
    string name;
    object find_name;
    name = apprentice;
    find_name = find_player(name);

    if (!str || str == "")
    {
        notify_fail("Promote who?\n");
        return 0;
    }

    if (!find_name)
    {
        notify_fail("Your apprentice must be present to promote them!\n");
        return 0;
    }

    if (str != name)
    {
        notify_fail("You can only promote your own apprentice.\n");
        return 0;
    }

    if (!present(find_name, environment(TP)))
    {
        notify_fail("Your apprentice must be present to promote them!\n");
        return 0;
    }

    write("You grant your apprentice " + capitalize(name) +
        "full rights as a Firewalker and relieve yourself of the "+
        "burden of an apprentice.\n");
    return 1;
}

int
set_apprentice(string str)
{
    if (!str || str == "")
    {
        notify_fail("No apprentice set.\n");
        return 0;
    }

    apprentice_chosen = str;
}

string
query_apprentice()
{
    if (!apprentice_chosen)
        return "None";
    else
        return apprentice_chosen;
}

void
init()
{
    ::init();
    add_action("do_promote","fpromote");
}

void
init_arg(string arg)
{
    apprentice_chosen = arg;
}
