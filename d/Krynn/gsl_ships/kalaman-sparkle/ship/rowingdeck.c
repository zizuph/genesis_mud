#include <stdproperties.h>

#include "/d/Genesis/gsl_ships/ships.h"
#include "../ship.h"

inherit STDSHIPROOM;

load_slave()
{
    clone_object(SLAVE)->move_living("xx", this_object());
}

void
reset_room()
{
    int    i;

    if (!present("slave", this_object()))
      for (i = 0; i < 4; i++)
        set_alarm(itof(random(30)),0.0,"load_slave");
    ::reset_room();
}

void
create_room()
{
  ::create_shiproom();
    set_short("The rowingdeck");
    set_long("This is the rowingdeck. Here several minotaurs " +
             "work to keep the ship going. A large drum keeps the pace.\n");

    add_item("drum", "This is a large drum giving a deep booming sound.\n");

    add_exit(DECK, "up", 0);
    set_cabin_sound("@@sounds");

    add_prop(ROOM_I_INSIDE, 1);
    reset_room();
}

sounds()
{
    if (random(2))
        return "The ship sways slightly in the wind.\n";

    return "The ship is rocking gently with the waves.\n";
}

