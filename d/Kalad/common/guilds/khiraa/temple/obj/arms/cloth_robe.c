inherit "/d/Kalad/std/armour.c";
#include "/d/Kalad/defs.h"

/*
 * /d/Kalad/common/guilds/khiraa/temple/obj/arms/steel_breastplate.c
 * Purpose    : Full, black enameled steel helm.
 * Located    : Vile, the armour makes them.
 * Created By : Sarr 17.Feb.97
 * Modified By: 
 * First Modif: 
 */


void
create_armour()
{
    ::create_armour();
    set_name("robe");
    set_short("black cloth robe");
    set_adj("black");
    add_adj("cloth");
    set_long("This finely crafted robe is made of jet-black cloth. "+
    "It covers your body and legs easily. A small, white grim-looking "+
    "skull is etched on the top part of the hood.\n");
    set_ac(3);
    set_at(A_ROBE);
    KVARM(10);
    KWARM(10);
    add_prop(OBJ_I_VOLUME, 30);
}
