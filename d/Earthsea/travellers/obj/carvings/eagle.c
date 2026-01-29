#pragma strict_types

#include "../../guild.h"

inherit TRAVELLERS_CARVING_STD;

public void
create_carving()
{
    add_name("eagle");
    set_short("wooden carving of an eagle");
    set_long("This seems to be an eagle, swift and proud. It is upon some " +
        "sort of drift wood. It seems rather small, though it is intricately " +
        "carved. On the bottom is an inscription of two crossed axes over a " +
        "map of the world.\n");
}
