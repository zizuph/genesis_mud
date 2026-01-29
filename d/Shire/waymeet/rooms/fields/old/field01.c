/*
    /d/Shire/waymeet/rooms/fields/field01.c

    Field in the farm north of Waymeet
    Perrigrine, February 2019
*/

#pragma save_binary
#pragma strict_types

#include "defs.h"

inherit WAYM_LIB_DIR + "base_field.c";
void reset_shire_room();

void create_field()
{

    area = "near"; /* Distance from areaname */
    areaname = "Waymeet";
    land = "the Shire";
    areatype = 4;
    areadesc = "vegetable field";

    extraline = "These large vegetable fields provide produce for the village " +
        "of Waymeet. You see cabbages, beets, carrots, and other essentials " +
        "spread around in careful rows. Amongst the rows you notice rather large " +
        "pawprints.";

    reset_shire_room();

    add_exit(WAYM_FIELD_DIR + "field09","south");
    add_exit(WAYM_FIELD_DIR + "field02","east");

}

void reset_shire_room()
{

}