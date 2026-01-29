#pragma strict_types

#include "../defs.h"

inherit TEMPLE + "std_platform.c";

void
create_temple_room()
{
    object door;
    

    ::create_temple_room();

     set_short("Green Highlord's platform");
    set_long("This platform is made of stone and and is semi-circular. " +
        "At the centre of the platform stands a large carved chair and " +
        "behind it, on the wall above the entrance, hangs the standard " +
        "of the Green Dragonarmy. Some steps lead down from the " +
        "platform to the floor of the Great Hall of Audience.\n");

    add_item(({"standard", "standard of the Green Dragonarmy"}),
        "The standard hangs from two spears pointing in opposite " +
        "directions. It shows the head of a green dragon in profile " +
        "set on a mustard yellow background. It is embroidered with " +
        "silk thread on velvet and the edges are trimmed with darker " +
        "yellow silk fringes.\n");

    add_item(({"seat", "suede seat"}),
        "This seat is soft and covered in green suede.\n");

    door = clone_object( DOOR + "gaplatf2.c" );
    door->move(this_object());
}


