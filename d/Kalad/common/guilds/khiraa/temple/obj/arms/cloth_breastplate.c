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
    set_name("tunic");
    set_short("black cloth tunic");
    set_adj("black");
    add_adj("cloth");
    set_long("This is a finely crafted cloth tunic. It is completely "+
    "black, except for the center, where a picture of a white "+
    "grim-looking skull stare out.\n");
    set_ac(3);
    set_at(A_TORSO);
    KVARM(10);
    KWARM(10);
    add_prop(OBJ_I_VOLUME, 50);
}
