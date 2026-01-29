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

public int
go_vis(string str)
{
    if (strlen(str))
    {
        return 0;
    }

    if (obf->query_invis_on())
    {
        obf->fade_in();
    }
    else
    {
    }

    return 1;
}

public int
go_invis(string str)
{
    if (strlen(str))
    {
        return 0;
    }

    if (!obf->query_invis_on())
    {
        obf->fade_out();
    }
    else
    {
    }

    return 1;
}

public void
init()
{
    ::init();

    add_action(go_vis, "ovis");
    add_action(go_invis, "oinvis");
}
