/* Ashlar, 21 Aug 98
   Dragons' landing (for the Dragonarmy)
 */

#include "/d/Ansalon/common/defs.h";
#include "../local.h";

inherit INNER_OUT;

void
create_neraka_room()
{
    set_short("on the roof of a tower");
    set_extra_long("This is the roof of a tall tower in Neraka. The roof " +
    "is much wider than the tower itself, and there are no railings of any " +
    "kind guarding the edges. Thick wooden planks, scratched and worn, cover " +
    "the roof. An opening, set a bit off the center, leads down.");

    add_exit(NINNER + "tower", "down");

    add_item("roof","You are standing on the roof of the tower. Thick " +
    "wooden planks cover the roof.\n");

    add_item("tower","You cannot see anything of the tower from here, " +
    "unless you were to lean far over the edge, but that is not advisable.\n");

    add_item(({"planks","wooden planks","thick planks"}),
    "The planks bear scratch marks of large claws, and are weathered and " +
    "worn.\n");

    add_item("opening","The opening is set a small distance off the center " +
    "of the roof. It leads down into the tower.\n");

    add_item(({"railing","railings"}),"I specifically told you there were " +
    "no railings. Listen up!\n");

    add_item(({"edge","edge of the roof"}),"It is safer to stay away from " +
    "the edge, the tower is quite tall!\n");

}




