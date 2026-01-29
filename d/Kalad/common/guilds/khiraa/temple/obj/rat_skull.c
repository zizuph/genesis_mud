inherit "/std/object";
#include "/d/Kalad/defs.h"
#pragma strict_types
#pragma save_binary

/*
 * /d/Kalad/common/guilds/khiraa/temple/obj/rat_skull.c
 * Purpose    : A spell component for 'lfungus'.
 * Located    : Created through a ritual sacrifice in the sacrifice room
 * Created By : Sarr 6.Mar.97
 * Modified By: 
 */


void
create_object()
{
    set_name("skull");
    add_name("ratskull");
    set_adj("rat");
    add_adj("marked");
    set_short("marked rat skull");

    set_long("This is a small skull from a rat. It is marked with many "+
    "strange symbols in blood. An aura of death surrounds it, and within "+
    "its small eyeholes, tiny red lights glow. It looks very eerie and "+
    "somewhat magical.\n");

    add_prop(OBJ_I_WEIGHT,50);
    add_prop(OBJ_I_VOLUME,20);
    add_prop(OBJ_I_VALUE,0);
}

