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
    set_short("black steel breastplate");
    set_adj("black");
    add_adj("steel");
    set_long("This is a solid, heavy steel breastplate. It is black "+  
    "and has a large, red grim-looking skull on the chestpiece.\n");
    set_ac(38);
    set_at(A_TORSO);
    KVARM(10);
    KWARM(10);
    KVOL(steel);
}
