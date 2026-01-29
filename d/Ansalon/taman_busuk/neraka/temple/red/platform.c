#pragma strict_types

#include "../defs.h"

inherit TEMPLE + "std_platform.c";

void
create_temple_room()
{
    object door;
    

    ::create_temple_room();

     set_short("Red Highlord's platform");
    set_long("This platform is made of stone and and is semi-circular. " +
        "At the centre of the platform stands a large carved chair and " +
        "behind it, on the wall above the entrance, hangs the standard " +
        "of the Red Dragonarmy. Some steps lead down from the " +
        "platform to the floor of the Great Hall of Audience.\n");

    add_item(({"standard", "standard of the Red Dragonarmy"}),
        "The standard is mounted on a fauchard which hangs " +
        "horizontally above the entrance. It shows a sitting red " +
        "dragon with a scorched body clutched in its talons. " +
        "It is beautifully embroidered with silk on a cream white " +
        "velvet background. The edges are trimmed with red silk " +
        "fringes.\n");

    add_item(({"seat", "suede seat"}),
        "This seat is soft and covered in red suede.\n");

    door = clone_object( DOOR + "raplatf2.c" );
    door->move(this_object());
}


