#pragma strict_types

#include "../defs.h"

inherit TEMPLE + "std_platform.c";

void
create_temple_room()
{
    object door;
    

    ::create_temple_room();

     set_short("Blue Highlord's platform");
    set_long("This platform is made of stone and and is semi-circular. " +
        "At the centre of the platform stands a large carved chair and " +
        "behind it, on the wall above the entrance, hangs the standard " +
        "of the Blue Dragonarmy. Some steps lead down from the " +
        "platform to the floor of the Great Hall of Audience.\n");

    add_item(({"standard", "standard of the Blue Dragonarmy"}),
        "Two crossed two-handed swords hold up the standard of the " +
        "Blue Dragonarmy. It shows a blue dragon sitting with its " +
        "wings spread wide. Beneath the dragon are two crossed " +
        "lightning bolts. The dragon is embroided with rich dark " +
        "blue silk and the bolts are of the finest silver. The " +
        "background is made of pale dark green velvet and the edges " +
        "are trimmed with blue silk fringes.\n");

    add_item(({"seat", "suede seat"}),
        "This seat is soft and covered in blue suede.\n");
    door = clone_object( DOOR + "baplatf2.c" );
    door->move(this_object());
}


