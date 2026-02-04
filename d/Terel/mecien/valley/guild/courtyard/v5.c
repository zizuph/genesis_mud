/* Creative rights reserved to Mecien(Jeff Babcock) and team. */
inherit "/std/room";

#include <stdproperties.h>
#include <macros.h>

#define GUILD_DIR    "/d/Terel/mecien/valley/guild/"
#define VINEYARD     (GUILD_DIR + "courtyard/")
#define TP           this_player()
#define TO           this_object()
#define BSN(xx)      (break_string(xx, 72) + "\n")
#define NO_OF_GRAPES 10

int ngrapes;

void
reset_room()
{
    ngrapes = NO_OF_GRAPES;
}

void
create_room()
{

    set_short("Vineyard");
    set_long(BSN(
	"This trail ends in the heart of the vinyard. Magnificent " +
	"and wondrous, filled with robust vines of radiant life. " +
	"Tremendous vines grow on both sides of the trail. The trail is " +
	"going north from here."
    ));

    add_item("vineyard", "It is thick and plush, growing and rich.\n");
    add_item(({"vines"}), "The vines are full of clusters of grapes.\n");
    add_item("trail", "It is just a passage between two rows of vines.\n");
    add_item(({"grapes"}), BSN(
	"The grapes here seem to be mature enough for picking."));
    add_cmd_item(({"grapes", "grape"}), "pick", "@@do_pick");

    add_exit(VINEYARD + "v3",  "north", 0);
    reset_room();
}

string
do_pick()
{
    object grapes;

    if (ngrapes < 1) return "There are no grapes left.\n";

    seteuid(getuid());
    grapes = clone_object(GUILD_DIR + "obj/grapes");
    if (grapes->move(TP)) {
        grapes->move(TO);
        write("The grapes slip out of your hand.\n");
        say(QCTNAME(TP) + " drops some grapes.\n");
    } else {
        write("You pick some grapes.\n");
        say(QCTNAME(TP) + " picks some grapes.\n");
    }
    ngrapes--;
    return "";
}
