inherit "/d/Gondor/minas/houses/citizens/house.c";

#include <stdproperties.h>
#include <macros.h>
#include "/d/Gondor/defs.h"

void
create_room()
{
    set_short("bedroom");
    set_long(BSN("This is the bedroom of this house. There is a " +
        "single bed sitting in the room, and beside it stands " +
        "a small table. A passage leads east into the main room."));
    add_item(({"bed","large bed"}), BSN(
        "This rather large bed dominates the room. It would " +
        "easily sleep two people. There are two pillows and many " +
        "blankets on the bed."));
    add_item(({"pillows"}), BSN(
        "These soft blue pillows rest at the head of the bed."));
    add_item(({"blankets","covers"}), BSN(
        "These blankets cover the bed in successive layers. They " +
        "make the bed appear very warm and quite comfortable!"));
    add_item(({"table","small table"}), BSN(
        "This small table stands next to the bed. Upon it is an " +
        "earthenware cup."));
    add_item(({"cup","earthenware cup"}), BSN(
        "This cup is short and broad and holds some water."));
    add_item(({"water"}), BSN(
        "The water in this cup is tepid. Apparently it has stood " +
        "here for some time."));
    add_item(({"fresco"}), BSN(
        "The fresco is a portrayal of Isildur stealing a branch from " +
        "Nimloth the Fair in the Court of Armenelos. It is faded and " +
        "looks to be quite old."));

    add_prop(ROOM_I_INSIDE, 1);

    set_wealth(1);
    set_side("north");
    set_circle("Second Circle");

    add_walls("The walls are decorated with a crude but pleasant " +
        "fresco.");
    add_ceiling();
    add_floor("The floor is rather worn - it seems that this is among " +
        "the eldest of the houses of the Second Circle.");

    add_lamp();

    add_exit(MINAS_DIR + "houses/citizens/h5r1sn3crc2","east",0,0);
}
