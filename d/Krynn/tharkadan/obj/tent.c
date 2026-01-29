#include <stdproperties.h>
#include "../local.h"

inherit "/d/Krynn/que/plains/obj/tent";

void
create_tent()
{
    add_adj("hide");
    add_adj("chum");
    add_name("chum");

    set_packed_short("hide tent bundle");
    set_packed_long("This is a bundle of a animal hides and leathers. " +
		    "Apparently it can be set up into a tent.\n");

    set_unpacked_short("hide chum tent");
    set_unpacked_long("Before you stands a tent consisting of elk hides " +
            "sewn together and wrapped around wooden poles organised in " +
            "a circle - a nomadic chum of Abanasinian design tailored " +
            "to much colder conditions. From a hole in the top of the " +
            "chum escapes a thin stream of smoke.\n");

    add_item(({"elk hides","hides","hide","wooden poles","poles"}),
            "The chum before you is of simple design, with wooden poles " +
            "wrapped in elk hides sewn together.\n");
    add_item(({"smoke","stream of smoke","hole"}),
            "A small hole in the top of the chum allows smoke to escape " +
            "it.\n");

    add_prop(OBJ_I_VALUE, 600);
    add_prop(OBJ_M_NO_GET, "The bundle is too awkward to carry by " +
            "yourself.\n");

    set_tent_inside(TOBJ + "tent_inside");
}
