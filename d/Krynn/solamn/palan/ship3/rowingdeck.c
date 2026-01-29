inherit "/d/Krynn/std/cabin";
#include "local.h"
#include <stdproperties.h>

load_slave()
{
    clone_object(SHIP_D + "slave")->move_living("xx", this_object());
}

void
reset_cabin()
{
    int    i;

    if (!present("slave", this_object()))
	for (i = 0; i < 4; i++)
	  set_alarm(itof(random(30)),0.0,"load_slave");
}

void
create_cabin()
{
    set_short("The rowingdeck");
    set_long("This is the rowingdeck. Here several minotaurs " +
	"work to keep the ship going. A small drum keeps the pace.\n");

    add_item("drum", "This is a small drum giving a booming sound.\n");

    add_exit(SHIP_D + "deck", "up", 0);
    set_cabin_sound("@@sounds");

    add_prop(ROOM_I_INSIDE, 1);
    reset_room();
}

sounds()
{
/*    if (file_name(environment(ship)) == TDIR + "lake1" ||
            file_name(environment(ship)) == TDIR + "sea1")
        return "The ship shakes incredibly hard and you hear a big splash!\n";*/

    switch(random(4))
      {
	case 0: return "The ship sways slightly in the wind.\n";
	case 1: return "The ship makes a turn back into the wind.\n";
	case 2: return "The ship turns gracefully out of the wind.\n";
	case 3: return "The ship is rocking gently with the waves.\n";
	default: return "The ship moves in the wind.\n";
      }
}

