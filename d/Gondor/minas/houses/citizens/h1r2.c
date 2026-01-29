inherit "/d/Gondor/minas/houses/citizens/house.c";

#include <stdproperties.h>
#include <macros.h>
#include "/d/Gondor/defs.h"

void
create_room()
{
    set_short("small kitchen");
    set_long(BSN(
        "This small kitchen is dim and lightless. There are no windows " +
        "in here, and an unlit torch hangs on the wall. You can dimly " +
        "make out a sink and a cupboard in here. The exit to the south " +
        "leads back to the main room."));
    add_item(({"torch","unlit torch"}), BSN(
        "This torch hangs in a sconce on the wall, which is blackened " +
        "where the torch flames have played against it."));
    add_item(({"sink","lead sink"}), BSN(
        "This sink is made of lead and is very old and battered. " +
        "The lampwright must be poor, indeed, if he must settle for " +
        "such an old sink."));
    add_item(({"cupboard","wooden cupboard"}), BSN(
        "You cannot see much about the cupboard in this light, but " +
        "you can tell that it is made of rather thin and cheap wood."));

    add_prop(ROOM_I_INSIDE, 1);


    set_wealth(1);
    set_side("north");
    set_circle("First Circle");

    add_walls("You can barely make out the walls in this poor light.");
    add_ceiling("The ceiling is barely visible in this room.");
    add_floor("The floor is very dirty.");

    add_exit(MINAS_DIR + "houses/citizens/h1r1sn2crc1","south",0,0);
}

int
do_light(string str)
{
    if (!strlen(str) || (str != "torch" && str != "unlit torch"))
    {
        NFN("Light what?");
        return 0;
    }

    NFN("The torch is so high on the wall that it is out of reach.");
    return 0;
}

void
init()
{
    ::init();

    add_action(do_light, "light", 0);
}


