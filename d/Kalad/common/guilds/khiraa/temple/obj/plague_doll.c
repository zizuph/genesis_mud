inherit "/std/object";
#include "/d/Kalad/defs.h"
#pragma strict_types
#pragma save_binary

/*
 * /d/Kalad/common/guilds/khiraa/temple/obj/plague_doll.c
 * Purpose    : A spell component for 'lplague'.
 * Located    : Created through a herb sacrifices and mixtures, enchantments
 * Created By : Sarr 6.Mar.97
 * Modified By: 
 */

int death_count;

void
create_object()
{
    set_name("doll");
    set_adj("plague");
    set_short("plague doll");

    set_long("This is what looks a grotesque doll figure of a female "+
    "insect-humanoid. Ancient marks and symbols cover it, most of "+
    "which seem to be incantations to some diety known as Pazuzu. A "+
    "foul odor drifts from it.\n");

    add_prop(OBJ_I_WEIGHT,300);
    add_prop(OBJ_I_VOLUME,100);
    add_prop(OBJ_I_VALUE,0);
    death_count = 5;
}

void
remove_object()
{
    death_count -= 1;
    if(death_count == 0)
    {
        tell_object(E(TO),"The "+short()+" rots away in your hands.\n");
        ::remove_object();
    }
    else
        tell_object(E(TO),"The "+short()+" glows slightly.\n");
}

