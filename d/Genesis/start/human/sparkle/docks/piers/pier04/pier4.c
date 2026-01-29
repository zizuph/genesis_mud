#pragma save_binary

inherit "/std/room";

#include <stdproperties.h>

#include "../defs.h"

object ship, sign;

void add_ship();
void add_sign();

void
create_room()
{
    set_short("Berth 4, west pier");
    set_long("\n"+
      "This is the west pier of Sparkle harbour.\n"+
      "Looking out over the Pensea you see the waves break in the wind.\n"+
      "You would need a ship to cross. West of here is the market square\n"+
      "and the smell of fresh fish tickles your nose.\n"+
      "");

    add_item(({"pier" }),"You're standing on it.\n"+
      "");
    add_item(({"waves" }),"Rather wild and not ideal to swim in.\n"+
      "");
    add_item(({"daughter","daughters" }),"You degenerate, why would you possibly want to do that.\n"+
      "");
    add_item(({"harbour" }),"The harbour is the prime source of income for a village like\n"+
      "Sparkle. Here, traders and merchant ships come in to sell their\n"+
      "cargos and draft new crews. The sailors spend their gold in the\n"+
      "pub and shop while the village people hide their daughters.\n"+
      "");

    add_prop(ROOM_I_INSIDE, 0);
    add_prop(ROOM_I_TYPE, ROOM_NORMAL);

    add_my_desc("There is a sign here marked 'Berth 4'\n");
    add_sign();

    add_exit(TOWN_DIR + "pier3","north");
    add_exit(TOWN_DIR + "square","west");
    add_exit(TOWN_DIR + "pier5","south");

    set_alarm(1.0, 0.0, add_ship);
}

void
add_ship()
{
    seteuid(getuid(this_object()));
    if (!ship)
    {
	ship = clone_object("/d/Genesis/start/human/obj/ship");
	ship->start_ship();
    }
}

void
add_sign()
{
    seteuid(getuid(this_object()));
    if (!sign)
    {
	sign = clone_object("/d/Genesis/start/human/obj/sign");
	sign->move(this_object());
    }
}
