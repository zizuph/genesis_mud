/*
 * Shore of river Bruinen
 * By Finwe, August 1998
 */
 
#pragma strict_types
#include "/d/Shire/sys/defs.h" 
#include "local.h"
 
inherit SHORE_BASE;
 
void
create_shore_room()
{
    set_area("next to");
    set_areaname("the River Bruinen");
    set_land("Eriador");
    set_areatype(7);
    set_areadesc("riverbank");
    set_grass("sparse, dry");
    set_treetype("conifer");


    set_vbfc_extra(shore_desc);

    add_exit(RIVER_DIR +   "shore02", "north",0,4);
    add_exit(TROLLSH_DIR + "rivend9", "west",0,4);
//    add_exit(RIVER_DIR + "path01", "northeast",0,4, check_person);


    reset_shire_room();

}

void
reset_shire_room()
{
/*
    object cigar;

    seteuid(getuid());

    if (!present("_shire_cigar_",TO))
    {
        cigar = clone_object("/d/Shire/scav_hunt/cigar");
        cigar->add_prop(OBJ_I_HIDE, 10 + random(10));
        cigar->move(TO);
    }
*/
}
