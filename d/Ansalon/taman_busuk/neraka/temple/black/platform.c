#pragma strict_types

#include "../defs.h"

inherit TEMPLE + "std_platform.c";

void
create_temple_room()
{
    object door;
    

    ::create_temple_room();

     set_short("Black Highlord's platform");
    set_long("This platform is made of stone and and is semi-circular. " +
        "At the centre of the platform stands a large carved chair and " +
        "behind it, on the wall above the entrance, hangs the standard " +
        "of the Blue Dragonarmy. Some steps lead down from the " +
        "platform to the floor of the Great Hall of Audience.\n");

    add_item(({"standard", "standard of the Black Dragonarmy"}),
        "This standard shows the silhouette of a dragon in profile, " +
        "rearing up and clawing in the air. It is embroided with " +
        "thick silver thread on a deep-black velvet background. " +
        "The edges are trimmed with silver fringes and the standard " +
        "hangs from a large two-handed battleaxe.\n");

    add_item(({"seat", "suede seat"}),
        "This seat is soft and covered in black suede.\n");

    door = clone_object( DOOR + "bkaplatf2.c" );
    door->move(this_object());
}


