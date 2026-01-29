#pragma strict_types

#include "../../guild.h"

inherit TRAVELLERS_CARVING_STD;

void
create_carving()
{
    add_name("wolf");
    set_short("wooden carving of a wolf");
    set_long("A wolf is depicted by this carving, standing eternal vigil " +
             "on a small cliff carved from wood. Though it is small the " +
             "carving is detailed and intricate. On the bottom is an " +
             "inscription of two crossed axes over a map of the world.\n");
}
