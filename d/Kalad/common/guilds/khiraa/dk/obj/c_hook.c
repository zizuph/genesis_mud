/* 
 * /d/Kalad/common/guilds/khiraa/dk/obj/c_hook.c
 * Purpose    : This is a large iron hook to hook things on.
 * Located    : Can be bought by vile the smith
 * Created By : Sarr 12.Apr.97
 * Modified By: 
 */ 

inherit "/std/object";
#include "/d/Kalad/defs.h"

void
create_object()
{
    set_name("hook");
    add_adj(({"iron","large"}));
    set_short("large iron hook");
    set_long("This is a large, nasty hook made of iron. It is curved, "+
    "and has a very sharp point at the end. The other end of it has "+
    "an equally sharp point, good for sticking it into things.\n");
    add_prop(OBJ_I_WEIGHT,60);
    add_prop(OBJ_I_VOLUME,30);
    add_prop(OBJ_I_VALUE,0);
}

