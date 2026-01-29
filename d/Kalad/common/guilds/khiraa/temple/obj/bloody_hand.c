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


string gRace;
string
query_race()
{
    return gRace;
}
void
set_race(string str)
{
    gRace = str;
}
void
create_object()
{
    set_name("hand");
    set_adj("bloody");
    add_adj("dismembered");
    set_short("bloody dismembered hand");

    set_long("This is a hand that looks to have been cut off someone. It "+
    "is bloody and ugly.\n");

    add_prop(OBJ_I_WEIGHT,300);
    add_prop(OBJ_I_VOLUME,100);
    add_prop(OBJ_I_VALUE,0);
}

