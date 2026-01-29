/*
 * Corridor base file for castle in Telseron
 * By Finwe, November 1996
 */
 
inherit "/std/room";
 
#include "/d/Emerald/defs.h"
#include "/d/Emerald/telseron/castle/default.h"
 
void create_corridor()
{
} 
void reset_room();
void create_room()
{
    add_prop(ROOM_I_INSIDE, 1);
    reset_room();
    set_short("A corridor");
    set_long("   The corridor is wide and beautiful. Deep, luxurious " + 
        "carpets cover the floor. The walls are plain but beautiful. "+
        "They are covered with mother of pearl and contrast sharply " +
        "with the richly decorated ceiling. ");
 
    add_item(({"up", "ceiling"}),
        "The ceiling is richly decorated with floral designs.\n");
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
        "wall. They are made of inlaid emerald and other precious " +
        "gems.\n");
    create_corridor(); 
}
 
void
reset_room()
{
}
