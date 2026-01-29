#include "/d/Gondor/defs.h"

#define  TOWER_DIR         (MORGUL_DIR + "tower/")
#define  CELLAR_DIR        (MORGUL_DIR + "cellar/")

#define WALLS \
    add_item(({"wall","walls"}), BSN( \
        "The walls are made of black square stone blocks. The " + \
        "blocks fit so well that there are hardly any seams " + \
        "visible between them. The surface of the blocks has been " + \
        "polished so it is very smooth and it seems to absorb light."));
#define ROOF \
    add_item(({"roof", "ceiling"}), BSN( \
        "The ceiling is high above your head and out of reach for " + \
        "your hands. It is made from the same black stone blocks as the " + \
        "walls and like them seems to absorb light."));
#define NO_ROOF \
    add_item(({"roof","ceiling"}), BSN( \
        "The roof is so high that it is lost to view in utter darkness."));
#define FLOOR \
    add_item(({"floor", "ground"}), BSN( \
        "The floor is made of square black stone slabs. The surface " + \
        "of the slabs has been polished so it is extremly smooth and " + \
        "shows hardly any signs of wear."));
#define STAIRCASE \
    add_item(({"staircase","stairs","spiral staircase","stairway"}), BSN( \
        "The spiral staircase disappears in the floor here, leading down " + \
        "to the ground level of the Tower. Upwards it soon disappears " + \
        "from view, hidden in the unfathomable darkness above."));
