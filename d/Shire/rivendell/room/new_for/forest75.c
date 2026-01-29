/*
 * Forest near Rivendell
 * By Finwe, August 1998
 */
 
#pragma strict_types
 
#include "local.h"
 
inherit FOREST_BASE;
 
void
create_forest_room()
{
    set_vbfc_extra(forest_desc3);
    reset_shire_room();

    add_exit(FOREST_DIR + "forest70", "north",check_person(0),4,check_person(0));
    add_exit(FOREST_DIR + "forest76", "east", check_person(0),4,check_person(0));
    add_exit(FOREST_DIR + "forest71", "northeast", check_person(2),4,check_person(2));
    add_exit(RIVER_DIR  + "path03", "southwest",check_person(2),4, check_person(2));

}

void reset_shire_room()
{
}
