inherit "/d/Gondor/minas/houses/citizens/house.c";

#include <stdproperties.h>
#include <macros.h>
#include "/d/Gondor/defs.h"

void
create_room()
{
    set_short("sitting room");
    set_long(BSN(
        "This is a large sitting room. About this room stand an " +
        "armchair, a couch, and a desk and chair. A lamp hangs " +
        "above the desk for better illumination. Upon the south wall " +
        "there is a window, and in the east wall is a hearth."));
    add_item(({"armchair"}), BSN(
        "This stuffed chair looks very comfortable. The arm rests " +
        "are quite soft, and the foot rest looks somewhat worn " +
        "but very relaxing."));
    add_item(({"couch","sofa"}), BSN(
        "This couch is of medium size, and looks to seat three " +
        "people comfortably. The upholstery is in a floral pattern, " +
        "depicting the rare seregon flower."));
    add_item(({"desk","chair","desk and chair"}), BSN(
        "This desk and chair set is made for reading and writing. " +
        "The surface of the desk is sloped gradually toward the " +
        "seat to aid reading. The woodwork on both chair and " +
        "desk is very nice and matches well."));
    add_item(({"hearth","fireplace"}), BSN(
        "This fireplace is made of stone from the White Mountains. " +
        "The fire burns cheerily, warming you and adding to the " +
        "soft illumination of the lamp."));

    add_prop(ROOM_I_INSIDE, 1);

    set_wealth(1);
    set_side("south");
    set_circle("Fourth Circle");

    add_window("The window gives you an excellent view.");
    add_walls("The east wall contains a large fireplace.");
    add_ceiling("The ceiling is peaked in this part of the house.");
    add_floor("The floor is bare here.");

    add_lamp();

    add_exit(MINAS_DIR + "houses/citizens/h8r1salleycrc4","north",0,0);
}
