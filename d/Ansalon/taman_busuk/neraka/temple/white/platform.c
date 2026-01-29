#pragma strict_types

#include "../defs.h"

inherit TEMPLE + "std_platform.c";

void
create_temple_room()
{
    object door;
    

    ::create_temple_room();

     set_short("White Highlord's platform");
    set_long("This platform is made of stone and and is semi-circular. " +
        "At the centre of the platform stands a large carved chair and " +
        "behind it, on the wall above the entrance, hangs the standard " +
        "of the White Dragonarmy. Some steps lead down from the " +
        "platform to the floor of the Great Hall of Audience.\n");

    add_item(({"standard", "standard of the White Dragonarmy"}),
        "The standard is mounted on a large halberd which hangs " +
        "horizontally above the entrance. It shows an ancient white " +
        "dragon in flight above three spiked maces. All embroidered " +
        "with white silk upon bright blue velvet. The edges are " +
        "trimmed with silver fringes.\n");

    add_item(({"seat", "suede seat"}),
        "This seat is soft and covered in white suede.\n");

    door = clone_object( DOOR + "waplatf2.c" );
    door->move(this_object());
}


