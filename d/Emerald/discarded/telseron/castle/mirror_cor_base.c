/*
 * Corridor base file for castle in Telseron
 * By Finwe, November 1996
 */
 
inherit "/std/room";
 
#include "/d/Emerald/defs.h"
#include "/d/Emerald/telseron/castle/default.h"
 
void create_mirror_corridor()
{
} 
void reset_room();
void create_room()
{
    add_prop(ROOM_I_INSIDE, 1);
    reset_room();
    set_short("A mirror corridor");
    set_long("   The corridor is wide and beautiful. Deep, " +
        "luxurious carpets cover the floor. The lower third of " +
        "the walls are faced with mother of pearl. The upper two " +
        "thirds are covered with polished steel. The surface has " +
        "been polished to a bright sheen and mirrors everything in " +
        "the hallway. The hallway is crowned with a richly decorated " +
        "ceiling. A large crystal chandelier hangs from the ceiling, " +
        "filling the room with light.\n\n");
 
    add_item(({"up", "ceiling"}),
        "The ceiling is richly decorated with floral designs.\n");
    add_item(({"wall", "walls"}),
        "You see yourself reflected in the wall.\n");
    add_item(({"floor", "ground", "down", "rug", "rugs",
               "carpet", "carpets"}),
        "The carpets are a rich forest green. Intricate designs of " +
        "leaves decorate the carpet in burgandy, royal blue, gold, " +
        "and dark brown.\n");
    add_item(({"design", "designs", "floral designs"}),
        "The designs are of large flowers twining across the " +
        "wall. They are made of inlaid emerald and other precious " +
        "gems.\n");
  add_item("chandelier",
        "The chandelier is enormous. It's multi-tiered and covered " +
        "with diamonds. Candles burn brightly, filling the " +
        "room with light. The diamonds move slightly, catching the " +
        "candlelight and throwing it onto the walls in a " +
        "rainbow of patterns.\n");
 
    create_mirror_corridor(); 
 
}
 
void
reset_room()
{
}
