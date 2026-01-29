#pragma save_binary

inherit "/std/room";

#include <stdproperties.h>

#include "defs.h"

#include S_DOMAIN_SYS_CONFIG

object ship, sign;

void add_ship();
void add_sign();

void
create_room()
{
    set_short("Berth 4 - Circle Route");
    set_long("\n"+
      "This is the west pier of Sparkle harbour.\n" +
      "Looking out over the Pensea you see the waves break in" +
      " the wind. You would need a ship to cross. West of here" +
      " is the market square and the smell of fresh fish tickles" +
      " your nose.\nThere is a sign here that reads: Berth 4 -" +
      " Circle Route.\n");

    add_item(({"waves" }),"Rather wild and not ideal to swim in.\n"+
      "");
    add_item(({"harbour" }),"The harbour is the prime source of income for a village like\n"+
      "Sparkle. Here, traders and merchant ships come in to sell their\n"+
      "cargos and draft new crews. The sailors spend their gold in the\n"+
      "pub and shop while the village people hide their daughters.\n"+
      "");

    add_prop(ROOM_I_INSIDE, 0);
    add_prop(ROOM_I_TYPE, ROOM_NORMAL);

    add_sign();

    add_exit(S_DOMAIN_PIERS_DIR + "sparkle/shire","north");
    add_exit("square","west");
    add_exit(S_DOMAIN_PIERS_DIR + "sparkle/terel","south");

    set_alarm(1.0, 0.0, add_ship);
}

void
add_ship()
{
#if S_ENABLE_SHIPS
  seteuid(getuid(this_object()));
  if (!ship)
  {
    ship = clone_object(S_AREA_OBJ_DIR + S_AREA_SHIP + "ship");
    ship->start_ship();
  }
#endif
}

void
add_sign()
{
    seteuid(getuid(this_object()));
    if (!sign)
    {
        sign = clone_object(S_LOCAL_OBJ_DIR + "sign");
        sign->move(this_object());
    }
}

