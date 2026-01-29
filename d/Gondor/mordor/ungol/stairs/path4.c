#pragma strict_types

inherit "/d/Gondor/common/room";

#include "/d/Gondor/defs.h"

public void 
create_room()
{
    set_short("a narrow path in the Morgul vale");
    set_long(BSN(
        "The narrow path follows a small bay in the valleyside here, " +
        "no more than a wide ledge between the sheer mountain face and " +
        "a chasm. "));

    add_item(({"ledge","path","valleyside","bay"}), BSN(
        "The path winds its way upwards on the northern side of the valley. " +
        "Here it follows a small bay in the valleyside, no more than a " +
        "wide ledge between the sheer mountain face to the north and a chasm " +
        "to the south. To the east the mountainside swells out, and the path " +
        "runs around it, so it is hidden from view where it continues. "));
    add_item(({"face","mountain face","mountains","mountain","chasm"}), BSN(
        "The path crawls upwards on the southward face on the mountains " +
        "that are north of the Morgul vale. Both above and below the path, " +
        "the mountain rises like a sheer cliff as far as one can see."));
    add_item(({"valley","vale","morgul vale","imlad morgul"}), BSN(
        "To the east, the Imland Morgul narrows to a dark cleft in the " +
        "mountain-range. The walls of Minas Morgul stand upon a hill on the " +
        "other side."));
    add_item(({"hill","minas morgul","city","walls","tower"}), BSN(
        "Across the river, on a hill in the valley stands Minas Morgul, the " +
        "city of the ringwraiths, the Tower of Black Sorcery. " +
        "All is dark about the city and the tower on the hill, but it is lit " +
        "with a pale light from within."));

    add_exit(STAIRS_DIR+"straight_bottom","east",0,3);
    add_exit(STAIRS_DIR+"path3","northwest",0,2);
}
