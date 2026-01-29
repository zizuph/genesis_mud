inherit "/d/Gondor/common/room";

#include "/d/Gondor/defs.h"

void create_room()
{
    set_short("A narrow path in the Morgul vale");
    set_long(BSN(
        "The narrow path winds its crooked way up into the northern " +
        "sides of the Morgul vale, climbing above the meads that lie on " +
        "both sides of the stream."));

    add_item(({"path","ground","floor"}), BSN(
        "The narrow path winds its crooked way up into the northern " +
        "sides of the Morgul vale. It is covered with small rocks and " +
        "stones. "));
    add_item(({"valley","vale","morgul vale","imlad morgul"}), BSN(
        "The Imlad Morgul, or Vale of Black Sorcery, continues further east, " +
        "narrowing to a dark cleft in the mountain-range. A foul-smelling " +
        "stream runs in the middle of the valley, and the walls of Minas " +
        "Morgul stand upon a hill on the further side."));
    add_item(({"stream","river","morgulduin"}), BSN(
        "The stream radiates a foul smell almost unbearable to breathe in. " +
        "The water is silently flowing, but the vapour rising from it, " +
        "curling and twisting about the bridge that spans across the river " +
        "not far south from here, is deadly cold."));
    add_item(({"hill","minas morgul","city","walls","tower"}), BSN(
        "Across the river, on a hill in the valley stands Minas Morgul, the " +
        "city of the rangwraiths, the Tower of Black Sorcery. " +
        "All is dark about the city and the tower on the hill, but it is lit " +
        "with a pale light from within."));
    add_item(({"meadows","meadow","mead","meads"}), BSN(
        "Wide flats lie on either bank of the Morgulduin, shadowy meadows filled " +
        "with pale white flowers. "));
    add_item(({"road", "morgul road", "wall"}), BSN(
        "Just south of here a stone wall runs between the path and the Morgul " +
        "road. The road makes a turn southward there to cross the stream on a " +
        "white bridge. There is a gap in the wall through which one can reach " +
        "the road."));
    add_item(({"bridge"}), 
        "The bridge connects the wide flats on either bank of the stream.");

    add_exit(STAIRS_DIR+"path2","northeast",0,3);
    add_exit(MORGUL_DIR +"road/mrd3","south",0,2);
}
