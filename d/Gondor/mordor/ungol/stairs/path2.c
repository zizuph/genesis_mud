#pragma strict_types

inherit "/d/Gondor/common/room.c";

#include "/d/Gondor/defs.h"

public void 
create_room()
{
    set_short("a narrow path in the Morgul vale");
    set_long(BSN(
        "The narrow path has reached the top of a great hump of bare rock " +
        "here. It continues around a small bay in the valleyside to the " +
        "northeast. To the south, across the stream, Minas Morgul commands " +
        "the view."));

    add_item(({"path","valleyside","bay"}), BSN(
        "The path winds its way upwards on the northern side of the valley. " +
        "Here is has reached the top of a great hump of bare rock. Ahead is " +
        "a bay in the valleyside, and round the head of this the path goes on, " +
        "no more than a wide ledge with a chasm on the right; across the sheer " +
        "southward face of the mountains in crawls upwards, until it disappears " +
        "into the blackness above."));
    add_item(({"hump","rock","top"}), BSN(
        "This hump of rock on the northern valleyside is almost level with the " +
        "walls of Minas Morgul on the other side of the river."));
    add_item(({"valley","vale","morgul vale","imlad morgul"}), BSN(
        "To the east, the Imland Morgul narrows to a dark cleft in the " +
        "mountain-range. A foul-smelling stream runs in the middle of the " +
        "valley, and the walls of Minas Morgul stand upon a hill on the " +
        "other side, almost level with this rock top."));
    add_item(({"stream","river","morgulduin"}), BSN(
        "The water is silently flowing, but vapour is rising from it, " +
        "curling and twisting about the bridge that spans across the river."));
    add_item(({"hill","minas morgul","city","walls","tower"}), BSN(
        "Across the river, on a hill in the valley stands Minas Morgul, the " +
        "city of the ringwraiths, the Tower of Black Sorcery. " +
        "All is dark about the city and the tower on the hill, but it is lit " +
        "with a pale light from within."));
    add_item(({"meadows","meadow","mead","meads"}), BSN(
        "Wide flats lie on either bank of the Morgulduin, shadowy meadows filled " +
        "with pale white flowers. "));
    add_item(({"road", "morgul road"}), BSN(
        "To the southwest, the Morgul road makes a turn. Southward, it crosses " +
        "the stream on a white bridge, while to the west, it runs along the northern " +
        "bank of the stream towards the green fields and forests of Ithilien."));
    add_item(({"bridge"}), 
        "The bridge connects the wide flats on either bank of the stream.");

    add_exit(STAIRS_DIR+"path1","southwest",0,2);
    add_exit(STAIRS_DIR+"path3","northeast",0,3);
}
