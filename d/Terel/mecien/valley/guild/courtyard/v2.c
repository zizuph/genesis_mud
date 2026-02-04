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
	"The earth here is rich, the soil well cultivated. Vines, radiant " +
	"with bright leaves and shining grapes, grow on both sides of the path."
    ));

    add_item("leaves", "They are brilliant green.\n");
    add_item("vineyard", "It is thick and plush, growing and rich.\n");
    add_item(({"path", "paths"}), BSN(
	"One leads southeast. The other northeast."
    ));
    add_item(({"vines"}), "The vines are full of clusters of grapes.\n");
    add_item(({"grapes"}), BSN(
	"The grapes here do not seem to be mature enough for picking."));
    add_cmd_item("grapes", "pick", "@@do_pick");

    add_exit(VINEYARD + "v1",  "southeast", 0);
    add_exit(VINEYARD + "v3",  "northeast", 0);
}

string
do_pick()
{
    return BSN("As you pick one grape it withers into nothingness. " +
	       "Maybe you should wait until they are ready.");
}
