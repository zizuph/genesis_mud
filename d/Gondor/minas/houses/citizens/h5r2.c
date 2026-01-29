inherit "/d/Gondor/minas/houses/citizens/house.c";

#include <stdproperties.h>
#include <macros.h>
#include "/d/Gondor/defs.h"

void
create_room()
{
    set_short("kitchen");
    set_long(BSN(
        "This kitchen is as charmingly decorated as the rest of " +
        "the house. Pots and pans are hung on the walls, and a " +
        "pleasant cupboard is mounted on one wall. The sink basin is " +
        "small and quaint, and the stove burns with a steady, " +
        "welcoming heat. A passage leads south back to the main " +
        "room."));
    add_item(({"pots","pans"}), BSN(
        "These pots and pans are hanging from the walls in " +
        "a tasteful arrangement. They are not merely for decoration, " +
        "though, as is clear from the stains of usage which they " +
        "bear."));
    add_item(({"cupboard"}), BSN(
        "This cupboard is mounted on the north wall. It has a " +
        "nice floral design carved into the doors, and the iron " +
        "handles are painted in white."));
    add_item(({"design","floral design"}), BSN(
        "The design is not expertly done, but is pleasant to view, " +
        "nonetheless."));
    add_item(({"handles","iron handles"}), BSN(
        "These handles have been painted a creamy white colour to " +
        "match the light coloured wood of the cabinet."));
    add_item(({"basin","sink","sink basin"}), BSN(
        "This small iron basin holds clear water and serves as the " +
        "sink of this kitchen. It is clean and well maintained."));
    add_item(({"water"}), BSN(
        "The crystal clear water in the basin look cool and " +
        "refreshing, but you decide not to partake of it."));
    add_item(({"stove","wood stove"}), BSN(
        "This small wood stove is painted a dark blue colour. It " +
        "burns merrily, warming the kitchen and providing heat " +
        "for the rest of the house."));
    add_item(({"hole","vent","small hole"}), BSN(
        "This small hole appears to be a vent through which steam and " +
        "smoke can escape. It is blocked at the top lest rain " +
        "and detritus fall into the kitchen."));

    add_prop(ROOM_I_INSIDE, 1);

    set_wealth(1);
    set_side("north");
    set_circle("Second Circle");

    add_window("The window is well cleaned.");
    add_walls("Pots and pans hang on the walls, and a cupboard is " +
        "mounted on the west wall.");
    add_ceiling("There is a small hole in the ceiling.");
    add_floor("The floor is shiny and seems to have been cleaned recently.");

    add_lamp();

    add_exit(MINAS_DIR + "houses/citizens/h5r1sn3crc2","south",0,0);
}
