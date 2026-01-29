inherit "/d/Gondor/minas/houses/citizens/house.c";

#include <stdproperties.h>
#include <macros.h>

#include "/d/Gondor/defs.h"

void
create_room()
{
    set_short("kitchen");
    set_long(BSN(
        "This is the kitchen of this large house. A large stove " +
        "dominates this room. There are cupboards and a counter " +
        "along the walls, and a hand pump in the corner. The " +
        "delicious smells of foodstuffs meet your nose."));
    add_item(({"stove","wood stove","large stove"}), BSN(
        "This massive stove radiates a powerful heat. You grow " +
        "uncomfortably hot just by standing near the stove. It " +
        "seems that this is the source of the cooking heat and " +
        "the household heat in general. Nothing is cooking on the " +
        "stove right now."));
    add_item(({"cupboards", "cupboard","pantry"}), BSN(
        "The cupboards hold utensils, crockery, and foodstuffs " +
        "in wait for the preparation of meals. They are large and " +
        "hold a great volume of materials; you can see that great " +
        "meals are prepared here."));
    add_item(({"counter"}), BSN(
        "The counter runs the length of the west wall. It is " +
        "well used, as is apparent from the many stains and " +
        "marks upon its surface. It is quite large and looks " +
        "capable of holding a banquet ready for service."));
    add_item(({"pump","hand pump","water pump"}), BSN(
        "This pump pumps water into a basin. You cannot tell whence " +
        "the water comes. Perhaps it is an outdoor reservoir of " +
        "rainwater, or maybe even an underground spring?"));
    add_item(({"basin","water basin"}), BSN(
        "This basin sits here and catches the water which is " +
        "released from the hand pump. It is empty right now, and " +
        "it smells fresh, as if it has been recently meticulously " +
        "cleaned."));

    add_prop(ROOM_I_INSIDE, 1);

    set_wealth(1);
    set_side("south");
    set_circle("Fourth Circle");

    add_window("The window is rather small.");
    add_walls("The walls bear cupboards and a counter.");
    add_ceiling("The ceiling on this side of the house " +
        "slopes westward.");
    add_floor("The floor has been polished recently.");

    add_lamp();

    add_exit(MINAS_DIR + "houses/citizens/h8r1salleycrc4","east",0,0);
}
