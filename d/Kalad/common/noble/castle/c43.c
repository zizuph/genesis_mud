// Sarr,
// Fysix, recoded, March 1998

#include "default.h"

inherit NOBLE_ROOM;

void
create_noble_room()
{
    set_short("In a hall of the Castle of the High-Lord");
    INSIDE;
    set_long("You now stand on the soft, red carpet that covers "+
    "this long hall leading south. The walls have torches on "+
    "them to give light when needed. A rare stuffed animal stands "+
    "on a stone pedestal here.\n");
    add_item("animal","It is of a giant bird with a long, orange beak. "+
    "Its feathers are the colors of the rainbow. Its eyes are blank "+
    "and lifeless.\n");
    add_item("pedestal","A white stone pedestal holds up the bird above.\n");
    add_item("tapestries","They depict various battle scenes.\n");
    add_item("carpet","The carpet is soft and warm.\n");
    add_item("torches","They hang on the walls.\n");

    add_exit(NOBLE + "castle/c38", "north", 0, 0);
    add_exit(NOBLE + "castle/c48", "south", 0, 0);
}


