#include <stdproperties.h>

inherit "/std/bow";

void create_bow()
{
    string bow = one_of_list(({"longbow", "shortbow"}));
    string adj = one_of_list(({"exotic", "leather-wrapped", "fur-trimmed",
        "fringed"}));
    add_name(bow);
    set_adj(adj);
    set_short(adj + " " + bow);
    set_long("The limbs of this " + bow + " has been wrapped with leather "
        + "and trimmed with fur and fringe, hinting at its Kagonesti origin. "
        + "The bare grip reveals a wood you do not recognize.\n");
    add_prop(OBJ_I_WEIGHT, 4500);
    add_prop(OBJ_I_VOLUME, 2500);
    set_hit(30);
    set_pen(30);
}
