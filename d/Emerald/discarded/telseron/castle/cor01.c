/*
 * A corridor in the castle in Telseron
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
        "in from windows on the western wall. Many elves pass " +
        "by you headed to different areas of the castle. The walls " +
        "are smooth and pure white. They are decorated with floral " +
        "designs suggesting the Queen's love for gardens. The floors " +
        "are covered with rich carpets which dampen most of the " +
        "noise. They look comfortable and are luxurious. The ceiling " +
        "is richly decorated with frescoes. The corridor runs east to " +
        "a corridor and south to music room.\n\n");

    add_item(({"fresco", "frescoes"}),
        "The frescoes are painted in rich colors. They depict the " +
        "courtship of the King and Queen.\n");
    add_item(({"up", "ceiling"}),
        "The ceiling has been richly painted with various scenes. They " +
        "depict the marriage of the king and queen of Telseron.\n");
    add_item(({"wall", "walls"}),
        "The walls are pearly white. They shine brilliantly as they " +
        "are covered with mother of pearl. The surface is so perfectly " +
        "covered you don't detect any seams. The walls have been "+
        "polished and are smooth to the touch.\n");
    add_item(({"floor", "ground", "down", "rug", "rugs", 
               "carpet", "carpets"}),
        "The carpets are a rich forest green. Intricate designs of " +
        "leaves decorate the carpet in burgandy, royal blue, gold, " +
        "and dark brown.\n");
    add_item(({"design", "designs", "floral designs"}),
        "The designs are of large flowers twining across the " +
        "wall. They are made of inlaid emerald.\n");
    add_item(({"window", "windows"}), 
        "The windows are expansive and fill the corridor with " +
        "light. They are arch shaped.\n");
 
    add_exit( TCASTLE_DIR + "music_room", "south");
    add_exit( TCASTLE_DIR + "cor02",       "east");
}

void
reset_room()
{
}
