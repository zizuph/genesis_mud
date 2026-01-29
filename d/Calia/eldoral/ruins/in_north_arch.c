#include "defs.h"

inherit STDROOM;

void
create_room()
{
    set_short("inside the southern archway of " + CASTLE_NAME);
    set_long("About you rises the heavy stone-lined walls of the northern " +
        "archway into " + CASTLE_NAME + ". Time has taken a brutal toll " +
        "on the stone, and the archway has in fact become more of " +
        "a large gash in the wall, as it has long since collapsed " +
        "and the stone which once stood over it now lies scattered " +
        "on the ground. To the north, you can see the " +
        "thick needles and dark trunks of the surrounding evergreen " +
        "forest, and to the south lies the northern courtyard of the " +
        "ruins.\n\n");

    add_item(({"walls"}),
        "The walls on either side of you are the crumbling remains of " +
        "what once were walls standing on either side of an archway. " +
        "Now they are walls standing on either side of little more " +
        "than a large hole in the wall.\n");
    add_item(({"sky", "mist"}),
        "Above your head, a thick white mist billows in the sky, " +
        "obscuring anything beyond.\n");
    add_item(({"ground", "floor"}),
        "The ground beneath you is covered in the rubble which " +
        "used to be a ceiling here.\n");
    add_item(({"rubble", "chunks", "chunks of stone"}),
        "Broken chunks of stone and silt now cover the ground, " +
        "fallen from it's original placement as the roof of an " +
        "archway here.\n"); 
    add_item(({"forest", "trees"}),
        "To the north, a deep forest of evergreens spreads out, " +
        "thick enough to quickly conceal anything that lies " +
        "even just within its edge.\n");
    add_item(({"courtyard"}),
        "To the south, a large courtyard spreads out before you.\n");

    add_exit(FOREST + "n_forest_9", "north");
    add_exit(RUIN + "ne_court_ne", "south");
}
