/*
 * Lucius, Jan 2018: ROOM_M_NO_TELEPORT_TO added.
 * Cotillion, Aug 2020: Fixed mantle cloning
 */
inherit "/std/room";

#include <files.h>
#include <money.h>
#include <macros.h>
#include <stdproperties.h>


void
reset_treasure()
{
    object *items = ({});

    if (!present("chainmail"))
	items += ({ clone_object("/d/Terel/mountains/obj/schain") });

    if (!present("sapphire"))
    	items += ({ clone_object("/d/Terel/mountains/obj/sapphire") });

    if (!present("axe"))
	items += ({ clone_object("/d/Terel/mountains/obj/axe") });

    if (!present("mantle"))
	items += ({ clone_object("/d/Terel/mountains/obj/cloak") });

    items->move(this_object());

    items = FILTER_COINS_OBJECTS(all_inventory());
    items->remove_object();

    MONEY_MAKE_HERE_CC(13000);
    MONEY_MAKE_HERE_SC(6000);
    MONEY_MAKE_HERE_GC(500);
}

void
create_room()
{
    set_short("Cave");
    set_long("This smaller cave seems to be a treasure room. "+
	"The walls are encrusted with crystals, making it glitter. "+
	"It is very clean here.\n");

    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_M_NO_TELEPORT_TO, 1);

    add_exit("bottom2", "west");

    reset_room();
}
