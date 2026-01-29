inherit "/d/Gondor/minas/houses/citizens/house.c";

#include <stdproperties.h>
#include <macros.h>
#include "/d/Gondor/defs.h"

void
create_room()
{
    set_short("bedroom");
    set_long(BSN(
        "This very small room is the bedroom of the house. You see three " +
        "mattresses with blankets on top of them and a small window. " +
        "There seems to be no other furnishing in this tiny room."));
    add_item(({"mattress","mattresses","bed","beds"}), BSN(
        "These mattresses are made from straw enclosed by a rough, " +
        "burlap-like cloth. They are covered with blankets, but they " +
        "do not look particularly comfortable."));
    add_item(({"blanket","blankets","covers"}), BSN(
        "These woolen blankets are quite old and rather dirty. There " +
        "are some holes worn in them and the edges are frayed."));
    add_item(({"hole","holes"}), BSN(
        "These holes have been worn into the blankets by years of use " +
        "and poor maintenance."));

    add_prop(ROOM_I_INSIDE, 1);

    add_exit(MINAS_DIR + "houses/citizens/h3r1ss2crc1","north",0,0);

    set_wealth(1);
    set_side("south");
    set_circle("First Circle");

    add_window("This small window is the only source of light in this room.");
    add_walls("The walls seem very sturdy.");
    add_ceiling("The ceiling is low here, as in the rest of this house.");
    add_floor("Upon the floor are three mattresses.");
}
