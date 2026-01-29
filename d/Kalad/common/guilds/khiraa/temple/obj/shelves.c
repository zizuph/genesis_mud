/* 
 * /d/Kalad/common/guilds/khiraa/temple/obj/shelves.c
 * Purpose    : Some shelves to hold stuff
 * Located    : ~khiraa/temple/rooms/temple_study
 * Created By : Sarr 12.Mar.97
 * Modified By: 
 */ 

#pragma save_binary
#pragma strict_types

inherit "/std/container.c";
inherit "/lib/keep.c";

#include "/d/Kalad/defs.h"
#include "/d/Kalad/common/guilds/khiraa/khiraa_defs.h"

public void
create_container()
{
    set_name("shelves");
    set_adj("black");
    add_adj("wooden");

    set_short("set of black wooden shelves");
    set_pshort("sets of black wooden shelves");
    set_long("These are a set of tall shelves made of strong black "+
    "oak from the forest of shadows. They are crafted to hold "+
    "many kinds of items, but most usefully, vials, jars and "+
    "other such things.\n");

    add_prop(CONT_I_RIGID,          0);
    add_prop(CONT_I_WEIGHT,     10000);
    add_prop(CONT_I_VOLUME,     10000);
    add_prop(CONT_I_MAX_WEIGHT, 90000);
    add_prop(CONT_I_MAX_VOLUME, 90000);
    add_prop(OBJ_M_NO_GET,1);
}
