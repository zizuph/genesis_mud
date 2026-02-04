/*
 * farm_base.c
 *
 * New base room for farm houses.
 * Lucius - Feb 2021
 */
#include "farm.h"

inherit STDROOM;
inherit STDHSEARCH;

public mapping counts = ([]);
public int max_pick = 5 + random(10);

public void
reset_terel_room()
{
    counts = ([]);
    max_pick = 5 + random(10);
}

public void
add_field_herbs()
{
    set_up_herbs(({ one_of_list(ANY_HERBS),
                    one_of_list(ANY_HERBS),
                    one_of_list(ANY_HERBS),
                 }), ({"field","fields"}), 3);
}

public void
add_pebbles()
{
    FIX_EUID;
    add_cmd_item(({"rocks","rock","pebble","pebbles"}),
                 ({"collect","gather","get"}), "@@get_pebble");
}

public int
get_pebble()
{
    object pebble;
    int num = counts[QRN];

    if (num < max_pick)
    {
        object pebble = clone_object(CALATHIN_DIR + "houses/obj/pebble");

        if (pebble->move(TP))
        {
            pebble->move(TO);
            write("You find a pebble from the ground.\n");
            say(QCTNAME(TP) + " finds a pebble on the ground.\n");
        }
        else
        {
            write("You pick up a pebble from the ground.\n");
            say(QCTNAME(TP) + " reaches down and picks up a pebble.\n");
        }

        counts[QRN] = num + 1;
        return 1;
    }

    write("You cannot find any pebbles to pick up.\n");
    return 1;
}
