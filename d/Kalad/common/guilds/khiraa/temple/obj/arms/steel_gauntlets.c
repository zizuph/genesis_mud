inherit "/d/Kalad/std/armour.c";
#include "/d/Kalad/defs.h"

/*
 * /d/Kalad/common/guilds/khiraa/temple/obj/arms/steel_helm.c
 * Purpose    : Full, black enameled steel helm.
 * Located    : Vile, the armour makes them.
 * Created By : Sarr 17.Feb.97
 * Modified By: 
 * First Modif: Toby, 970919 (random ac added)
 */


void
create_armour()
{
    ::create_armour();
    set_name("gauntlets");
    set_short("pair of black steel gauntlets");
    set_pshort("pairs of black steel gauntlets");
    set_adj("black");
    add_adj("steel");

    set_long("These are a pair of strong steel gauntlets that "+
    "are completely black. There are tiny skulls on the top of the "+
    "hands.\n");

    add_item(({"skull","tiny skull"}),"It is quite grim looking.\n");

    set_ac(17+random(3));
    set_at(A_HANDS);
    KVARM(10);
    KWARM(10);
    KVOL(steel);
}
