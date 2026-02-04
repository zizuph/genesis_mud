/* Creative rights reserved to Mecien(Jeff Babcock) and team. */
inherit "/std/room";

#include <stdproperties.h>
#include <macros.h>

#define GUILD_DIR    "/d/Terel/mecien/valley/guild/"
#define VINEYARD     (GUILD_DIR + "courtyard/")
#define TP           this_player()
#define TO           this_object()
#define BSN(xx)      (break_string(xx, 72) + "\n")

void
create_room()
{

    set_short("Vineyard");
    set_long(BSN(
	"Plush vines grow up neatly along the edges of this path " +
	"that cuts its way through the rich vinyard. The air is " +  
        "filled with the smells of growth."
    ));

    add_item("vineyard", "It is thick and plush, growing and rich.\n");
    add_item(({"path", "paths"}), BSN(
	"One leads southwest. The other northwest."
    ));
    add_item(({"vines"}), "The vines are full of clusters of grapes.\n");
    add_item(({"grapes"}), BSN(
	"The grapes here do not seem to be mature enough for picking."));
    add_cmd_item("grapes", "pick", "@@do_pick");

    add_exit(VINEYARD + "v1",  "southwest", 0);
    add_exit(VINEYARD + "v3",  "northwest", 0);
}

string
do_pick()
{
    return BSN("As you pick one grape it withers into nothingness. " +
	       "Maybe you should wait until they are ready.");
}
