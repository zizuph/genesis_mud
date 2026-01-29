inherit "/std/object";
#include "/d/Kalad/defs.h"
#pragma strict_types
#pragma save_binary

/*
 * /d/Kalad/common/guilds/khiraa/temple/obj/glowing_skull.c
 * Purpose    : A skull that glows to make light.
 * Located    : Created through a skull sacrifice in the sacrifice room
 * Created By : Sarr 6.Mar.97
 * Modified By: 
 */


void
create_object()
{
    set_name("skull");
    set_adj("grotesque");
    add_adj("glowing");
    set_short("grotesque glowing skull");

    set_long("This is what looks like a human skull. It is twisted and "+
    "deformed, with many ancient magical marks carved in the bone. "+
    "It is glowing with a bright, purple light.\n");

    add_prop(OBJ_I_LIGHT,1);
    add_prop(OBJ_I_WEIGHT,600);
    add_prop(OBJ_I_VOLUME,210);
    add_prop(OBJ_I_VALUE,0);
}

