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
	"A grand and beautiful vineyard. Rich vines, covered with "
       +"radiant leaves, grow up all about. Everything seem well kept "
       +"and serene. South from here is a gate, and beyond it you see a "
       +"building."
    ));

    add_item("gate", "It is a simple gate, made of reddish wood.\n");
    add_item("vineyard", "It is thick and plush, growing and rich.\n");
    add_item(({"path", "paths"}), BSN(
	"One leads northwest into a vineyard. The other northeast. "
       +"There are vines on both sides."));
    add_item("building", BSN(
	"It is a stone building, its front has two dark windows."));
    add_item(({"vines"}), "The vines are full of clusters of grapes.\n");
    add_item(({"grapes"}), BSN(
	"The grapes here do not seem to be mature enough for picking."));
    add_cmd_item("grapes", "pick", "@@do_pick");

    add_exit(VINEYARD + "ve",  "south", "@@gate");
    add_exit(VINEYARD + "v2",  "northwest", 0);
    add_exit(VINEYARD + "v4",  "northeast", 0);
}

int
gate()
{
    write("You open the gate.\n");
    return 0;
}

string
do_pick()
{
    return BSN("As you pick one grape it withers into nothingness. " +
	       "Maybe you should wait until they are ready.");
}
