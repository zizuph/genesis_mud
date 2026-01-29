/*
 * Road in Bree
 * By Finwe, June  2001
 */
 
#pragma strict_types

#include "/d/Shire/sys/defs.h" 
#include "defs.h"

inherit ROAD_BASE;

object gate;
 
void
create_road_room()
{
    set_areadesc("large");
    set_area("busy");
    set_areaname("crossroad");
    set_land("Bree");

    add_my_desc("The road winds its way north towards a quieter " +
        "part of Bree, northeast up around the hill, and southwest " +
        "towards the center of Bree. A stone wall lines the west " +
        "side of the road as two tall buildings rise beyond it. An " +
        "ornate steel gate marks the entrance beyond the wall.\n");
    add_item(({"gate", "steel gate", "ornate gate", "ornate steel gate"}),
        "The ornate steel gate is beautifully wrought of polished " +
        "steel. It is forged of polished vertical, steel bars with a " +
        "horizontal bar at the top and bottom of the gate. On top " +
        "of each vertical bar is a round ball.\n");
    add_item(({"round ball"}),
        "The round balls are set on top of each vertical bar of the " +
        "gate. They are fist size and polished.\n");

    set_add_houses();
    set_add_outside_smiths();
    set_add_hill();

//    gate = clone_object(OBJ_DIR + "broad07_gate");
//    gate -> move(this_object());

    add_exit(ROAD_DIR + "broad20", "north");
    add_exit("/d/Shire/guild/smiths/rooms/yard", "west");
    add_exit(ROAD_DIR + "broad06", "southwest");
    add_exit(ROAD_DIR + "broad08", "northeast");
}
