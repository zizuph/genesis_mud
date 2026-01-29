#include "/d/Ansalon/common/defs.h"
#include <macros.h>
#include "/d/Ansalon/goodlund/kendermore/local.h"

inherit KENDERMORE_IN;

void
reset_kendermore_room()
{
}

void
create_kendermore_room()
{
    set_short("Hurtling through time and space");
    set_long("You are moving swiftly through the magic portal. " + 
        "A hazy blue mist surrounds you, clearing every so " + 
        "often to show fantastic scenes, ancient battles, famous " + 
        "heroes, or just a simple peasant farmer trying to stay " + 
        "alive in a war swept world.\n");
    add_item(({"scene", "scenes"}), "They look extremely life-like, " + 
        "almost as if you could touch them.\n");
    add_item(({"mist", "blue mist", "hazy blue mist", "hazy mist"}),
        "It is the deep blue of the sky at dusk. The mist has no " + 
        "feel to it, except a slight cool dampness.\n");
}

public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);
    if (interactive(ob))
        start_room_tells();
}

