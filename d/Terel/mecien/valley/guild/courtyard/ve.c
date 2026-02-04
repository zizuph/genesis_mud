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
    object door;

    set_short("Vineyard Entrance");
    set_long(BSN(
        "A beautiful old stone building stands here, set against the outer "
       +"wall of the shrine courtyard. Its roof rises high, thatched and "
       +"layered over many times. Its walls made of craggy old feldstone. "
       +"Two oblong windows of smokey glass adorn its front. A path of "
       +"white stones leads north from here, through a gate. Through the "
       +"gate a small vineyard spreads out, lush and earthy. A path leads "
       +"southeast into a thick hedge of evergreens."
    ));

    door = clone_object(VINEYARD + "wd1");
    door->move(TO);
    door->set_key(31313);

    add_item("gate", "It is a simple gate, made of reddish wood.\n");
    add_item("windows", "They are oblong and of dark smokey glass.\n");
    add_item("vineyard", "It is thick and plush, growing and rich.\n");
    add_item("hedges", "They are to the southeast.\n");
    add_item("path", BSN(
	"One leads north into a vineyard. The other southeast "
       +"into a hedge of evergreens."));
    add_item("building", BSN(
	"It is a stone building, its front has two "
       +"dark windows. It has a thatched roof and craggy walls."));
    add_item("roof", "It is thatch.\n");
    add_item("thatch", "It appears to be straw mixed with pine branches.\n");

    add_exit(VINEYARD + "g4a", "southeast", 0);
    add_exit(VINEYARD + "v1",  "north", "@@gate");
}

int
gate()
{
    write("You open the gate.\n");
    return 0;
}
