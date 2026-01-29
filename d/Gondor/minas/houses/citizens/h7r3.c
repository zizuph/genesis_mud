inherit "/d/Gondor/minas/houses/citizens/house.c";

#include <stdproperties.h>
#include <macros.h>
#include "/d/Gondor/defs.h"

void
create_room()
{
    set_short("filthy kitchen");
    set_long(BSN(
        "The first thing you notice upon entering this kitchen is a " +
        "foul and powerful smell, as of old food left to sit. There " +
        "is a small cooking stove in the corner, and a sink basin " +
        "in the middle of the room. Dirty crockery and utensils " +
        "are everywhere in this room."));
    add_item(({"stove","cooking stove","small stove"}), BSN(
        "This wood burning stove has a large flat surface for the " +
        "cooking of meals. The surface is stained with spilled food " +
        "and sauces which have burned and hardened onto the iron."));
    add_item(({"sink","basin","sink basin"}), BSN(
        "This basin holds water for washing and cooking. It is full " +
        "of water and dirty plates and bowls. Bits of food and " +
        "grease have collected around the side of the basin at the " +
        "surface of the water."));
    add_item(({"water","dirty water"}), BSN(
        "The water is quite dirty. It seems to have some sauces mixed " +
        "in with it, as it is murky and not quite clear. In addition, " +
        "small pieces of food are floating within the water."));
    add_item(({"crockery","utensils","plates","bowls"}), BSN(
        "These eating and cooking items are scattered across the room " +
        "and covered with half eaten food. The disgusting odor comes " +
        "from the food left on these items."));

    add_prop(ROOM_I_INSIDE, 1);

    set_wealth(1);
    set_side("south");
    set_circle("Third Circle");

    add_window("The window is greasy and hard to see through.");
    add_walls("The walls have food stains upon them.");
    add_ceiling("The ceiling is in a poor condition.");
    add_floor("The floor has scattered bits of food upon it.");

    add_lamp();

    add_exit(MINAS_DIR + "houses/citizens/h7r1ss3crc3","south",0,0);
}
