#include <stdproperties.h>

#include "/d/Genesis/gsl_ships/ships.h"
#include "../ship.h"

inherit "/d/Krynn/std/gsl_cabin";

void
reset_cabin()
{
}

void
create_room()
{
  ::create_shiproom();
    set_short("The cruising deck of a ship");
    set_long("Small, leather seats line the walls of the cruising deck. The "
        + "walls are leather padded and dotted with glass viewing ports.\n");

    add_item(({"wall", "walls"}), "The walls have been padded with dark, red "
        + "leather in case of turbulence.\n");
    add_item(({"seat", "seats", "leather seat", "leather seats"}), "Small "
        + "leather seats line the walls for comfort and easy viewing out the "
        + "ports.\n");
    add_item(({"port", "port", "porthole", "portholes", "viewing port",
        "viewing ports", "glass port", "glass ports", "glass viewing ports"}),
        "Glass viewing ports in the walls provide an unprecendented and "
        + "astounding view of the ocean below.\n");

    add_exit(DECK, "up", 0);
    set_cabin_sound("@@sounds");

    add_prop(ROOM_I_INSIDE, 1);
    reset_room();
}

sounds()
{
    if (random(2))
    {
        return "The airship groans as a gust of wind howls across the deck "
            + "above.\n";
    }
  
    return "The airship creaks quietly as it floats effortlessly through "
        + "the sky.\n";
}

