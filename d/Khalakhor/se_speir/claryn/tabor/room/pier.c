/*
 * pier.c
 *
 * This is the small pier at Tabor Sogh - not much here initially
 *
 * Zima - March 16, 1998
 */
#pragma strict_types
inherit "/d/Khalakhor/std/room";
 
#include <macros.h>
#include "/d/Khalakhor/sys/defs.h"
#include "room.h"
#define  PIER_COORDS ({0, 5})
 
object   npc;
 
// room coordinate functions
public int * query_local_coords()  { return PIER_COORDS;    }
public int * query_global_coords() { return VILLAGE_COORDS; }
 
public void check_npc()
{
   if (objectp(npc)) return;
   npc = clone_object(NPC+"sailor");
   npc->arm_me();
   npc->move(TO);
   tell_room(TO,QCTNAME(npc)+" climbs out of the sea onto the pier.\n");
}
 
public void reset_room()
{
   check_npc();
}
 
public void create_khalakhor_room() {
    set_short("small wooden pier");
    set_long("   You are standing on a small wooden pier which jutts "+
        "out over the waters of Lear Min, the great southern sea. "+
        "To the east is the sleepy fishing village called Tabor Sogh, "+
        "a small settlement of stone buildings with thatched roofs. "+
        "You see a dusty dirt road that runs north and south along the "+
        "rocky shoreline, lined with the homes and other buildings of the "+
        "village along its east side. The waves of the sea lap endlessly "+
        "against the rotting wooden poles which hold the pier above "+
        "the cold waters. The pier has just been extended a bit to the west.\n");
 
    add_item("pier",
        "It is an old pier made simply of logs bound together, supported "+
        "by large wooden poles which hold it above the sea's cold "+
        "waters. It seems old and rotten, but strangely sturdy.\n");
    add_item("poles",
        "Large wooden poles, made of the trunks of thick trees, stand "+
        "straight out of the sea and hold up the pier. Constantly "+
        "battered by the waves of the sea, they look rather water-logged "+
        "and rotten, though strangely sturdy.\n");
    add_item("road",
        "To the east is a dusty dirt road, hardpacked by years of "+
        "trodding feet and wagon wheels. It runs along the shoreline "+
        "to the north and south, fronting the small stone buildings "+
        "of the village. You can step off the pier onto it to the "+
        "east.\n");
    add_item(({"town","settlement","village","tabor sogh","Tabor Sogh"}),
        "Tabor Sogh is an old fishing village, but has never " +
        "grown much beyond a handful of homes and a few " +
        "necessities for fishing. The village consists of " +
        "a single road upon which all buildings are built " +
        "of dark grey stone.\n");
    add_item(({"sky"}),
        "Looking up, you see the sky is partially overcast, " +
        "with thick grey clouds drifting through an " +
        "otherwise blue sky.\n");
    add_item(({"clouds","thick clouds", "grey clouds",
        "thick grey clouds"}),
        "Thick clouds drift lazily across the sky high above " +
        "your head.\n");
    add_item(({"buildings","stone buildings","low buildings","homes"}),
        "A number of buildings occupy the village, most " +
        "look pretty much identical with stone walls and " +
        "thatched roofs.\n");
    add_item(({"wall","walls"}),
        "The walls of all the buildings are are made " +
        "in a similar fashion, of thin plates of dark " +
        "grey stone which have been neatly stacked together. " +
        "No mortar or packing is evident, but the walls " +
        "appear quite sturdily built regardless.\n");
    add_item(({"stones","blocks"}),
        "The stones which make up the walls of most of " +
        "the buildings here are thin plates of dark grey " +
        "stone, carefully stacked to form walls for the " +
        "buildings.\n");
    add_item(({"shore","shoreline"}),
        "It is a rocky shoreline which disappears into the distance "+
        "to the north and south, lapped by the colds waters of the sea.\n");
    add_item(({"water","sea","Lear Min","lear min","waves"}),
        "The waters of Lear Min are are slate grey in colour, " +
        "with white caps topping the larger of the waves in " +
        "the choppy waters as far as the eye can see.\n");
    reset_room();
    add_exit(ROOM + "road_1_5", "east");
    add_exit("pier2", "west");
}
