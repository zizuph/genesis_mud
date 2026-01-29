/* The leader's tent, no real difference
 *
 * Aridor 08/97
 */

#include <stdproperties.h>

inherit "/d/Krynn/que/plains/obj/tent";

void
create_tent()
{
    add_adj("fancy");
    add_adj("decorated");

    set_packed_short("fancy tent bundle");
    set_packed_long("This is a fancy bundle of a soft material. Apparently it can " +
		    "be set up into a tent.\n");

    set_unpacked_short("fancy army tent");
    set_unpacked_long("A decorated fancy tent, which can easily hold several " +
		      "people. It is possible to enter the tent through the " +
		      "entrance, but you could also just pack the tent and " +
		      "walk off with it.\n");

    add_prop(OBJ_I_VALUE, 600);

    set_tent_inside("/d/Krynn/que/camp/obj/ltent_inside");
}
