inherit "/std/object";

#include <stdproperties.h>

object obf;

public void
create_object()
{
    set_name("obfuscate_cmd");
    set_no_show();
    remove_prop(OBJ_I_WEIGHT);
    remove_prop(OBJ_I_VOLUME);
    add_prop(OBJ_M_NO_DROP, 1);
    add_prop(OBJ_M_NO_STEAL, 1);
    add_prop(OBJ_M_NO_BUY, 1);
    add_prop(OBJ_M_NO_SELL, 1);
}

public void
set_obfuscate_effect(object ob)
{
    obf = ob;
}

public void
go_vis()
{
    if (obf->query_invis_on())
    {
        obf->fade_in();
    }
    else
    {
        write("You are already exposed.\n");
    }
}

public void
go_invis()
{
    if (!obf->query_invis_on())
    {
        obf->fade_out();
    }
    else
    {
        write("You cannot fade out:  you haven't revealed yourself.\n");
    }
}

public int
fade(string str)
{
    if (str == "in")
    {
        go_vis();
        return 1;
    }

    if (str == "out")
    {
        go_invis();
        return 1;
    }

    return 0;
}

public void
init()
{
    ::init();

    add_action(fade, "fade");
    add_action(fade, "fade");
}
