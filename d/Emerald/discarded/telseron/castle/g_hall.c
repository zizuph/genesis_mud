/*
 * The Great Hall in the castle in Telseron
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
    set_short("The Great Hall");
    set_long("   You stand in the Great Hall of Telseron. It has " +
        "been said that this room has seen more gatherings than " +
        "any other place in the city. This is entirely possible " +
        "as all important functions are held in this great hall. " +
        "The Hall is the largest room anywhere. It is often " +
        "filled with jubilant elves but for now, the walls are " +
        "silent in anticipation. Tables, chairs, and benchs are " +
        "scattered around the room. Braziers are scattered around " +
        "the room, warming the room and filling it with the " +
        "fragrance of forests. A large reflecting pool sits in the " +
        "center of the room. Beautiful fish can be seen swimming " +
        "under the surface.\n\n");
 
   add_item(({"table", "tables"}),
        "Mahagony tables are scattered around the room. They are " +
        "handcrafted and polished to a deep shine.\n");
    add_item(({"chairs", "chair"}),
        "The chairs are large and solid looking. They are " +
        "handcrafted of mahogany and well used.\n");
    add_item(({"benches", "bench"}),
        "The benches are handcrafted of mahogany.\n");
    add_item(({"up", "ceiling", "dome"}),
        "The ceiling is richly painted with floral designs. A giant " +
        "dome crowns the room. with in the dome, various frescos " +
        "have been painted. They depict the joyous times of the " +
        "Elven nation.\n");
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
    add_item(({"pool", "pond", "water", "reflecting pool"}),
        "The reflecting pool is crystal clear and clean. You see a " +
        "mosaic in the bottom of the king and queen. The water " +
        "reflects your image but is broken as fish rise to the " +
        "surface anxious to be fed.\n");
    add_item("fish",
        "Different sized fish swim contendly around the pool. " +
        "They are beautiful. Some are pearl while, orange, golden, " +
        "and red.\n");
    add_item("braziers", 
        "These metal containers are warm to the touch. Elves pass " +
        "by, tending them and filling the braziers with more " +
        "fragrant pine chips.\n");
 
    add_exit( TCASTLE_DIR + "cor02",      "north");
    add_exit( TCASTLE_DIR + "med_room",   "east");
    add_exit( TCASTLE_DIR + "music_room", "west");
}
 
void
reset_room()
{
}
