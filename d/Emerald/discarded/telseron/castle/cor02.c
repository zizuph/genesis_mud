/*
 * The corridor #3 of the castle in Telseron
 * By Finwe, November 1996
 */
 
inherit "/std/room";
 
#include "/d/Emerald/defs.h"
#include "/d/Emerald/telseron/castle/default.h"

void reset_room();
 
void
create_room()
{
    add_prop(ROOM_I_INSIDE, 1);
    reset_room();
    set_short("A corridor");
    set_long("   This corridor is wide and spacious. Light flows " +
        "in from the north brightening the area. Many elves pass " +
        "by you headed to different areas of the castle. The walls " +
        "are smooth and pure white. They are decorated with floral " +
        "designs suggesting the Queen's love for gardens. The floors " +
        "are covered with rich carpets which dampen most of the " +
        "noise. They look comfortable and are luxurious. The ceiling " +
        "is domed shaped, and beautifully decorated. A fragrant " +
        "aroma drifts from the south. The corridor runs east and " +
        "west, north is the inner court and south is the Great " +
        "Hall.\n\n");
 
    add_item(({"up", "ceiling", "dome"}),
        "The ceiling is a medium sized cupola. The domed " +
        "interior has been richly painted with various scenes. They " +
        "depict the coming of the elves to Telseron.\n");
    add_item(({"wall", "walls"}),
        "The walls are pearly white. They shine brilliantly as they " +
        "are covered with mother of pearl. The surface so perfectly " +
        "covered that you don't detect any seams. The walls have been "+
        "polished and are smooth to the touch.\n");
    add_item(({"floor", "ground", "down", "rug", "rugs", 
               "carpet", "carpets"}),
        "The carpets are a rich forest green. Intricate designs of " +
        "leaves decorate the carpet in burgandy, royal blue, gold, " +
        "and dark brown.\n");
    add_item(({"design", "designs", "floral designs"}),
        "The designs are of large flowers twining across the " +
        "wall. They are made of inlaid emerald.\n");
 
    add_exit( TCASTLE_DIR + "in_court", "north");
    add_exit( TCASTLE_DIR + "g_hall",   "south");
    add_exit( TCASTLE_DIR + "cor03",     "east");
    add_exit( TCASTLE_DIR + "cor01",     "west");
}

void
reset_room()
{
}
