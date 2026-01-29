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
    set_name("breastplate");
    add_name("plate");
    set_short("black iron breastplate");
    set_adj("black");
    add_adj("iron");
    set_long("This is a solid, heavy iron breastplate. It is black "+  
    "and has a large, red grim-looking skull on the chestpiece.\n");
    set_ac(34);
    set_at(A_TORSO);
    KVARM(10);
    KWARM(10);
    KVOL(iron);
}
