/*
 * /d/Gondor/rohan/edoras/rooms/bhallway2.c
 *
 * Modification log:
 * 4-Dec-1997, Gnadnar: General revision.
 */
#pragma strict_types

inherit "/d/Gondor/std/room.c";

#include <macros.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"

public void	create_gondor();

/*
 * Function name:	create_gondor
 * Description	:	set up the room
 */
public void
create_gondor()
{
    set_short("Rohirrim barracks");
    set_long(BSN(
	"A stone hallway leads east into what appears to be a military "+
	"barracks. The floor has seen much use from heavy boots, "+
	"but is in good repair and has been swept clean recently. The "+
	"rough stone walls are unadorned, save for "+
	"some banners to the right of the door in the western wall."));

    add_item(({"barracks","room"}),long);
    add_item(({"banner","banners"}), BSN(
	"The largest of these banners shows a riderless horse galloping "+
	"over a field of green. In the lower right corner there stands a "+
	"golden 'T'. You recognize the standard of the King's Eored of "+
	"the riders of Rohan."));
    add_item(({"slab","slabs","stone","stones","stone slab","stone slabs",
	"floor","ground"}), BSN(
	"The stone slab floor has been worn somewhat low in the center. "+
	"In some places old stone slabs have been replaced by newer ones."));
    add_item(({"boulder","boulders","wall","walls"}), BSN(
	"The walls are made from large boulders, roughly but " +
	"expertly hewn and put together with great skill."));
    add_item(({"hall","hallway","corridor"}), BSN(
	"The large hallway continues east, leading farther into the " +
	"barracks where doors open to both sides of the hallway."));
    add_item(({"stone ceiling","ceiling"}), BSN(
	"The stone ceiling shows some traces of smoke."));
    add_item(({"traces","trace","traces of smoke","smoke"}), BSN(
	"The traces probably are from smoky torches."));

    clone_object(EDORAS_DIR + "rooms/bhw2door")->move(TO);
    clone_object(EDORAS_DIR + "rooms/barrgate")->move(TO);

    add_prop(ROOM_I_INSIDE,1);
    add_prop(ROOM_I_LIGHT,1);
    add_exit(EDORAS_DIR + "rooms/bhallway2", "east", 0, 1);
    add_exit(EDORAS_DIR + "rooms/boffice2", "west", 0, 1, 1);
    add_exit(EDORAS_DIR + "rooms/field", "south", 0, 1, 1);
}
