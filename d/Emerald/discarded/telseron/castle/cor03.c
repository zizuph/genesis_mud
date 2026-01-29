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
    set_long("   The corridor is wide and beautiful. Large windows " +
        "in the eastern wall fill the room with light. The light " +
        "reflects off the mother of pearl walls filling the room " +
        "with a brilliant aura. Deep, luxurious carpets cover the " +
        "floor. The walls are plain but beautiful. They contrast " +
        "sharply with the ceiling which is richly decorated. In the " +
        "center of the ceiling is a medium sized dome.\n\n");
 
    add_item(({"up", "ceiling", "dome"}),
        "The ceiling has been richly painted with various scenes. They " +
        "depict the history of Telseron.\n");
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

 
    add_exit( TCASTLE_DIR + "med_room", "south");
    add_exit( TCASTLE_DIR + "cor02",       "west");
}
 
void
reset_room()
{
}
