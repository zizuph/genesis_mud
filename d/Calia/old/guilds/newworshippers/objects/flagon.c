/*
    This is a flagon containing water that Worshippers can get
    from their water elemental.

    The code is old, just added strict_types and header, Bishop July 2003.
*/

#pragma strict_types

inherit "/std/object";

#include <stdproperties.h>
#include <macros.h>

void
create_object()
{
    set_name("flagon");
    add_name("_worship_flagon_");
    set_short("flagon");
    set_long("It is a crystal flagon filled with a glowing "+
        "liquid of some sort.  You could probably drink from it.\n");

    add_prop(OBJ_M_NO_SELL,1);
    add_prop(OBJ_M_NO_STEAL,1);
    if (IS_CLONE)
        set_alarm(480.0,0.0,remove_object);
}

void
init()
{
    ::init();
    add_action("drink","drink");
}

int
drink(string str)
{
    int maxdrink;
    if (str != "from flagon")
    {
        notify_fail("Drink from what?\n");
        return 0;
    }
    maxdrink = (this_player()->query_prop("_live_i_max_drink")/15);
    if (!this_player()->drink_soft(maxdrink))
    {
        write("You cannot drink more from the flagon.\n");
        return 1;
    }
    this_player()->drink_soft(maxdrink);
    write("You drink from the flagon.\n");
    say(QCTNAME(this_player())+" drinks from a flagon.\n");
    return 1;
}

public void
remove_object()
{
    tell_object(environment(this_object()),"The flagon becomes "+
        "liquid and evaporates.\n");
    ::remove_object();
}
