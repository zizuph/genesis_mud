inherit "/d/Gondor/minas/houses/citizens/house.c";

#include <stdproperties.h>
#include <macros.h>
#include "/d/Gondor/defs.h"

void
create_room()
{
    set_short("bedroom");
    set_long(BSN(
        "This is a modest second floor bedroom. The staircase leads " +
        "north and down to the foyer. A large bed stands in the " +
        "middle of this room, and a chest of drawers sits to one " +
        "side. A lamp hanging from the wall illuminates this " +
        "room."));
    add_item(({"stairs","stairway","staircase"}), BSN(
        "The stairs descend to the first floor. They are made of " +
        "brethil wood."));
    add_item(({"bed","large bed"}), BSN(
        "This very large bed is the sleeping area of the owner of " +
        "this house. It is plush and appears very comfortable."));
    add_item(({"chest","chest of drawers"}), BSN(
        "This chest of drawers holds the clothing of the occupants " +
        "of this house. It is very large and looks as if it would " +
        "hold a great deal of clothing. It is made of the fair wood " +
        "from the region tree."));

    add_prop(ROOM_I_INSIDE, 1);

    set_wealth(1);
    set_side("south");
    set_circle("Fourth Circle");

    add_walls("The walls have been recently cleaned.");
    add_ceiling("The ceiling is very low and peaked here.");
    add_floor("The floor creaks as you stand upon it.");

    add_lamp();

    add_exit(MINAS_DIR + "houses/citizens/h8r1salleycrc4","down",0,0);
}
