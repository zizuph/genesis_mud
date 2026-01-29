#pragma strict_Types

inherit "/std/scroll";

#include <stdproperties.h>
#include <ss_types.h>

public void
create_scroll()
{
    set_name("parchment");
    add_name("scroll");
    set_adj(({"tattered", "torn"}));
    set_short("tattered parchment");
    set_long("A tattered, torn piece of parchment. " +
        "It looks old and the spidery handwriting is in " +
        "some places unreadable.\n");
    set_file("/d/Earthsea/gont/tenalders/obj/items/ea_script.txt");
    add_prop(OBJ_I_WEIGHT, 20);
    add_prop(OBJ_I_VOLUME, 20);
}

public int
query_the_parchment()
{
    return 1;
}

public int
read_it(string str)
{
    object tp = this_player();

    if(str == "read")
    {
        if(tp->query_skill(SS_LANGUAGE) > 10 &&
            tp->query_stat(SS_WIS) > 5)
        {

            ::read_it("read");
            return 1;
        }

        write("The runes are unfamiliar, and you do not have the " +
            "skill in languages to read it.\n");
        return 1;
    }
}
