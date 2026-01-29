
inherit "/std/object";

#include <stdproperties.h>
#include <macros.h>

create_object()
{
    set_name("decanter");
    add_name("_worship_decanter_");
    set_short("decanter");
    set_long("It is a crystal decanter filled with a glowing "+
        "liquid of some sort.  You could probably drink from it.\n");

    add_prop(OBJ_M_NO_SELL,1);
    add_prop(OBJ_M_NO_DROP,"You don't dare let go of the decanter.\n");
    add_prop(OBJ_M_NO_STEAL,1);
    if (IS_CLONE)
        set_alarm(240.0,0.0,remove_object);
}

init()
{
    ::init();
    add_action("drink","drink");
}

int
drink(string str)
{
    if (str != "from decanter")
    {
        notify_fail("Drink from what?\n");
        return 0;
    }
    if (!this_player()->drink_alco(30,1))
    {
        write("You cannot drink more from the decanter.\n");
        return 1;
    }
    this_player()->drink_alco(30);
    write("You drink from the decanter.\n");
    say(QCTNAME(this_player())+" drinks from a decanter.\n");
    return 1;
}

public void
remove_object()
{
    tell_object(environment(this_object()),"The decanter becomes "+
        "liquid and evaporates.\n");
    ::remove_object();
}
