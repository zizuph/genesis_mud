inherit "/d/Gondor/common/room";

#include "/d/Gondor/defs.h"

void create_room()
{
    set_short("A narrow path in the Morgul vale");
    set_long(BSN(
        "The narrow path follows a small bay in the valleyside here, " +
        "no more than a wide ledge between the sheer mountain face and " +
        "a chasm. "));

    add_item(({"ledge","path","valleyside","bay"}), BSN(
        "The path winds its way upwards on the northern side of the valley. " +
        "Here it follows a small bay in the valleyside, no more than a " +
        "wide ledge between the sheer mountain face to the north and a chasm " +
        "to the south."));
    add_item(({"face","mountain face","mountains","mountain","chasm","cliff"}), BSN(
        "The path crawls upwards on the southward face of the mountains " +
        "that are north of the Morgul vale. Both above and below the path, " +
        "the mountain rises like a sheer cliff as far as one can see."));
    add_item(({"valley","vale","morgul vale","imlad morgul"}), BSN(
        "To the east, the Imland Morgul narrows to a dark cleft in the " +
        "mountain-range. A foul-smelling stream runs in the middle of the " +
        "valley, and the walls of Minas Morgul stand upon a hill on the " +
        "other side, their tops almost level with the path."));
    add_item(({"stream","river","morgulduin"}), BSN(
        "The water is silently flowing, but vapour is rising from it, " +
        "curling and twisting about the bridge that spans across the river."));
    add_item(({"hill","minas morgul","city","walls","tower"}), BSN(
        "Across the river, on a hill in the valley stands Minas Morgul, the " +
        "city of the ringwraiths, the Tower of Black Sorcery. " +
        "All is dark about the city and the tower on the hill, but it is lit " +
        "with a pale light from within."));
    add_item(({"road", "morgul road"}), BSN(
        "Down in the valley, the Morgul road crosses the stream on the bridge, " +
        "running up towards the city, while in the other directions, it follows " +
        "the Morgulduin out of the valley to the green fields and forests of Ithilien."));
    add_item(({"bridge"}), 
        "The bridge connects the wide flats on either bank of the stream.");

    add_exit(STAIRS_DIR+"path2","southwest",0,3);
    add_exit(STAIRS_DIR+"path4","southeast",0,3);
}
