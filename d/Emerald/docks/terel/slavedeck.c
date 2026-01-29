#pragma strict_types

inherit "/d/Emerald/std/room";

#include "../defs.h"
#include <stdproperties.h>
#include <cmdparse.h>

public void
reset_room()
{
    int i;
    reset_euid();
    i = max(0, 4 - sizeof(filter(all_inventory(), &->query_slave())));
    while (i--)
    {
	clone_object(DOCK_DIR + "terel/slave")->move(this_object(), 1);
    }
}

public void
create_emerald_room()
{
    set_short("The slavedeck");
    set_em_long("This is the slavedeck of the great ship. There are "+
      "a number of benches on each side where the slaves sit when they "+
      "are rowing, and there is a large beating drum at the far end of "+
      "the deck that is used to keep the rowers in pace and enforcing "+
      "greater speeds. A rugged brass lantern hangs in the ceiling, "+
      "shedding a dim light so that you can barely see the room.\n");

    add_item("drum", "This is a large drum with a probably deafening sound.\n");
    add_item("benches", "Old, wooden benches. No mahorny here!\n");
    add_item("lantern", "It's an old brass lantern, secured in the ceiling.\n");
    add_exit("cabin", "up");
    add_prop(ROOM_I_INSIDE, 1);
    reset_room();
}
