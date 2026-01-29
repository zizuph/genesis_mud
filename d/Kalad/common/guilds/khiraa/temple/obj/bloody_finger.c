inherit "/std/object";
#include "/d/Kalad/defs.h"
#pragma strict_types
#pragma save_binary

/*
 * /d/Kalad/common/guilds/khiraa/temple/obj/bloody_hand.c
 * Purpose    : Used for rituals and spell components.
 * Located    : Can but cut from corpses by members of the Khiraa
 * Created By : Sarr 6.Mar.97
 * Modified By: 
 */


void
create_object()
{
    set_name("finger");
    set_adj("bloody");
    add_adj("dismembered");
    set_short("bloody dismembered finger");

    set_long("This is a finger that looks to have been cut off someone. It "+
    "is bloody and ugly.\n");

    add_prop(OBJ_I_WEIGHT,80);
    add_prop(OBJ_I_VOLUME,20);
    add_prop(OBJ_I_VALUE,0);
}

