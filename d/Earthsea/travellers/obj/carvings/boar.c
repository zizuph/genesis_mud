#pragma strict_types

#include "../../guild.h"

inherit TRAVELLERS_CARVING_STD;

public void
create_carving()
{
    add_name("boar");
    set_short("wooden carving of a boar");
    set_long("This is a carving of a wild boar. It stands, head lowered, " +
        "ready to charge. Two tusks protrude from the head of the boar, " +
        "surprisingly sharp. Though it seems small, it is intricately " +
        "carved. On the belly of the boar is an inscription of two crossed " +
        "axes over a map of the world.\n");
}
