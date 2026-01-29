inherit "/d/Gondor/minas/houses/citizens/suspect_home";

#include <stdproperties.h>
#include <macros.h>

#include "/d/Gondor/defs.h"

void
create_suspect_room()
{

    add_exit(MINAS_DIR + "houses/citizens/h3r2","south",0,0);

    set_door_id("MT_h3_s2crc1");
    set_door_command(({"n","north"}));
    set_door_name(({"wooden door","door"}));
    set_other_room(MINAS_DIR + "s2crc1");
    set_door_desc(BSN("This door is poorly fitting. It looks as if it has " +
        "been taken from another doorway and somehow made to fit here."));

    set_suspect(2);
    set_wealth(1);
    set_side("south");
    set_circle("First Circle");

    set_short("small room");
    set_long(BSN(
        "This small room seems to hold almost all of the residents' meager " +
        "possessions. You see a battered table, a wooden box, and an iron " +
        "oil-lamp. A pit in the corner contains glowing embers."));
    add_item(({"possessions"}), BSN("There is a table, a box, and a lamp."));
    add_item(({"table","battered table"}), BSN(
        "This small table is very battered; it seems as if the residents of " +
        "this house got it from a garbage dump. It seems to serve as an " +
        "eating surface as well as a place to stack plates and bowls."));
    add_item(({"plates","plate","bowls","bowl"}), BSN(
        "These tin dishes are not very clean; apparently this household " +
        "does not have easy access to water or is just not very " +
        "cleanly."));
    add_item(({"box","wooden box"}), BSN(
        "This box contains the utensils and cooking items of " +
        "this household."));
    add_item(({"utensils","cooking items"}), BSN(
        "These tin utensils are very old and quite worn."));
    add_item(({"pit","firepit","fire pit"}), BSN(
        "This dirt pit contains the glowing remains of a fire. It is quite " +
        "primitive, with only a small hole in the upper corner to " +
        "vent smoke."));
    add_item(({"embers","ember","remains","glowing remains"}), BSN(
        "These faintly glowing embers bathe the room in a dull " +
        "red glow."));

    add_window("This window is so small as to be almost an arrow-slit.");
    add_walls("The walls are very near one another. This is a small room.");
    add_ceiling("The ceiling is low to the ground. Very tall people " +
        "would have to stoop in here.");
    add_floor("The floor is marked by the firepit.");
    add_lamp();

}
