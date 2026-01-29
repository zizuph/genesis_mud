#include "../local.h"
#include "/d/Ansalon/common/defs.h"

#include <stdproperties.h>
#include <macros.h>

inherit "/std/object";

#define NERAKA_I_GOT_COAT   "_neraka_i_got_coat"
#define COAT_FILE   NOBJ + "overcoat"

void
create_object()
{
    set_name("crate");
    add_name("box");
    set_adj(({"large","wooden"}));
    set_short("large wooden crate");
    set_long("This large wooden crate is stamped with the " +
    "legend: 'SURPLUS DRAGONARMY MATERIAL: COATS, USED'. Within " +
    "you spy a heap of ragged clothings. You can <take a coat> " +
    "from the box, if you want.\n");

    add_prop(OBJ_M_NO_GET, 1);
}

int
coat_take(string str)
{
    object coat;
    
    if (stringp(str) && (str == "coat" || str == "a coat"))
    {
        if (this_player()->query_prop(NERAKA_I_GOT_COAT))
        {
            write("You will have to be satisfied with one coat for now.\n");
            return 1;
        }

        setuid();
        seteuid(getuid());
        
        coat = clone_object(COAT_FILE);
        if (!coat)
        {
            write("Something prevents you from taking a coat. Please leave " +
            "a bugreport.\n");
            return 1;
        }

        if (coat->move(this_player()))
        {
            write("You cannot carry a coat!\n");
            coat->remove_object();
            return 1;
        }

        write("You take a coat from the crate.\n");
        say(QCTNAME(this_player()) + " takes a coat from the crate.\n");
        this_player()->add_prop(NERAKA_I_GOT_COAT, time());
        return 1;
    }
    else
        return 0;
}

void
init()
{
    ::init();

    add_action(coat_take, "take");
}
