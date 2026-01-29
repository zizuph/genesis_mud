#pragma save_binary

inherit "/std/object";
inherit "/cmd/std/command_driver";

#include "../guild.h"
#include <macros.h>
#include <stdproperties.h>
#include <wa_types.h>

#define BITE_SUBLOC "bite_subloc"

static int time_out;

void
create_object()
{
    set_name("_vamp_bite_mark");
    set_no_show();

    remove_prop(OBJ_I_VOLUME);
    remove_prop(OBJ_I_VALUE);
    remove_prop(OBJ_I_WEIGHT);
    add_prop(OBJ_M_NO_GET, 1);
}

string
query_auto_load()
{
    return MASTER + ":" + time_out;
}

void 
init_arg(string arg)
{
    if (strlen(arg))
    {
        if (!sscanf(arg, "%d", time_out))
        {
            remove_object();
        }
    }
}

string
show_subloc(string subloc, object carrier, object for_obj)
{
    if (!this_player()->query_prop(TEMP_SUBLOC_SHOW_ONLY_THINGS) &&
        (subloc == BITE_SUBLOC))
    {
        if (carrier->query_age() > time_out)
        {
            remove_object();
            return "";
        }

        if (carrier == for_obj)
        {  
            return "";    // You cannot see your own neck!
        }

        if (!carrier->query_armour(A_NECK))
        {
            return capitalize(PRO(carrier)) + " has a pair of small " +
                "puncture wounds on " + POS(carrier) + " neck.\n";
        }
    }

    return "";
}

int
collar(string str)
{
    if (strlen(str))
    {
        return 0;
    }

    allbb(" pulls " + POS(this_player()) + " collar up, trying to " +
        "conceal the puncture wounds on " + POS(this_player()) + " neck.");
    write("You pull up your collar, trying to conceal the bite marks.\n");
    return 1;
}

int rub(string str)
{
    if (member_array(str, ({ "neck", "my neck", "bite marks",
          "puncture_wounds" })) < 0)
    {
        return 0;
    }

    allbb(" absentmindedly rubs at the puncture wounds on " + 
        POS(this_player()) + " neck.");
    write("You rub at the puncture wounds on your neck.\n");

    return 1;
}

void init()
{
    ::init();

    add_action(collar, "collar");
    add_action(rub, "rub");

    if (!living(environment()))
    {
        remove_object();
        return;
    }

    if (this_player() != environment())
    {
        return;
    }

    if (!time_out)
    {
        time_out = this_player()->query_age() + 600;
    }

    this_player()->add_subloc(BITE_SUBLOC, TO);

}

void
remove_object()
{
    this_player()->remove_subloc(BITE_SUBLOC);
    ::remove_object();
}
