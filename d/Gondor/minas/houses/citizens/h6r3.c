inherit "/d/Gondor/minas/houses/citizens/house.c";

#include <stdproperties.h>
#include <macros.h>
#include "/d/Gondor/defs.h"

void
create_room()
{
    set_short("bedroom");
    set_long(BSN(
        "This is the bedroom of this pleasant home, as shown by the " +
        "three beds which stand in the room. There is a small chest of " +
        "drawers in the corner and a large candle which is mounted on " +
        "the wall."));
    add_item(({"beds", "bed"}), BSN(
        "These beds look quite comfortable. There is a larger one, " +
        "seemingly for two people, and two smaller beds."));
    add_item(({"large bed","larger bed"}), BSN(
        "This large bed is covered with quilted blankets and " +
        "even sports two pillows. The varnished wood headboard " +
        "bears a bas-relief family seal and a scene of Amandil " +
        "sending his son Elendil from Numenor before the King " +
        "Ar-Pharazon doomed it to destruction."));
    add_item(({"blankets","quilted blankets"}), BSN(
        "These blankets are very soft and thick. It appears that " +
        "they would keep a person very warm at night."));
    add_item(({"headboard","wood headboard"}), BSN(
        "The headboard bears a scene from the Akallabeth in " +
        "bas-relief of very skilled worksmanship."));
    add_item(({"smaller beds"}), BSN(
        "These smaller beds are apparently made for children. " +
        "You can't imagine a fully grown Man sleeping in these!"));
    add_item(({"chest","chest of drawers"}), BSN(
        "This great mahogany chest holds clothing of all sorts. " +
        "Within its many drawers you find trousers, shirts, " +
        "dresses, hose, cloaks and tunics."));
    add_item(({"clothes","clothing"}), BSN(
        "How rude!"));
    add_item(({"candle","beeswax candle"}), BSN(
        "This beeswax candle is very large. It is quite thick " +
        "and seems to have been used a great deal. It looks as " +
        "if this is the only illumination available in this " +
        "room, as you see no windows."));

    add_prop(ROOM_I_INSIDE, 1);

    set_wealth(1);
    set_side("north");
    set_circle("Third Circle");

    add_walls("The corners of the walls are rounded.");
    add_ceiling("The ceiling is rather low here.");
    add_floor();

    add_exit(MINAS_DIR + "houses/citizens/h6r1sn1crc3.c","east",0,0);
}
