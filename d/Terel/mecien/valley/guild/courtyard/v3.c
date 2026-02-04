/* Creative rights reserved to Mecien(Jeff Babcock) and team. */
inherit "/std/room";

#include <stdproperties.h>
#include <macros.h>

#define GUILD_DIR    "/d/Terel/mecien/valley/guild/"
#define VINEYARD     (GUILD_DIR + "courtyard/")
#define TP           this_player()
#define TO           this_object()
#define BSN(xx)      (break_string(xx, 72) + "\n")

void move_here(object who);

object vine_dresser;

void
reset_room()
{
    if (vine_dresser) return;

    vine_dresser = clone_object(VINEYARD + "vine_dresser");
    set_alarm(3.0, -1.0, &move_here(vine_dresser));
}

void
move_here(object who)
{
    who->move_living("xx", TO);
}

void
create_room()
{

    set_short("Vineyard");
    set_long(BSN(
        "Rich and plush, the vines grow very tall here, bounding with " +
	"grapes over the path. The vineyard is vibrant, its aroma almost " +
	"intoxicating. A well worn trail is " +
	"going south from here."
    ));

    add_item("vineyard", "It is thick and plush, growing and rich.\n");
    add_item(({"path", "paths"}), BSN(
	"One leads southwest. The other southeast."
    ));
    add_item(({"vines"}), "The vines are full of clusters of grapes.\n");
    add_item(({"grapes"}), BSN(
	"The grapes here do not seem to be mature enough for picking."));
    add_cmd_item("grapes", "pick", "@@do_pick");
    add_item("trail", "It leads deep into the vinyard.\n");

    add_exit(VINEYARD + "v2",  "southwest", 0);
    add_exit(VINEYARD + "v4",  "southeast", 0);
    add_exit(VINEYARD + "v5",  "south", 0);

    reset_room();
}

string
do_pick()
{
    return BSN("As you pick one grape it withers into nothingness. " +
	       "Maybe you should wait until they are ready.");
}
