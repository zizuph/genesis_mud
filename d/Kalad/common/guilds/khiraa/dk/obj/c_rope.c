/* 
 * /d/Kalad/common/guilds/khiraa/dk/obj/c_rope.c
 * Purpose    : This is a piece of rope to hang things from.
 * Located    : Can be bought by vile the smith
 * Created By : Sarr 12.Apr.97
 * Modified By: 
 */ 

inherit "/std/object";
#include "/d/Kalad/defs.h"

void
create_object()
{
    set_name("rope");
    add_name("coil");
    add_adj("short");
    set_short("short coil of rope");
    set_pshort("short coils of rope");
    set_long("This is a short coil of rope, made of blackened "+
    "hemp. Good for tying things up with. It is very sturdy.\n");
    add_prop(OBJ_I_WEIGHT,80);
    add_prop(OBJ_I_VOLUME,50);
    add_prop(OBJ_I_VALUE,1);
}

