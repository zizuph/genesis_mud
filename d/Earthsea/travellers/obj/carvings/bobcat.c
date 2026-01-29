#pragma strict_types

#include "../../guild.h"

inherit TRAVELLERS_CARVING_STD;

public void
create_carving()
{
    add_name("bobcat");
    set_short("wooden carving of a bobcat");
    set_long("This cat most closely resembles a bobcat, vicious and " +
             "cunning. It is rather small, though it is intricately " +
             "carved. A small inscription of two crossed axes over a map " +
             "of the world can be seen on the bottom.\n");
}
