inherit "/d/Kalad/std/armour.c";
#include "/d/Kalad/defs.h"

/*
 * /d/Kalad/common/guilds/khiraa/temple/obj/arms/steel_helm.c
 * Purpose    : Full, black enameled steel helm.
 * Located    : Vile, the armour makes them.
 * Created By : Sarr 17.Feb.97
 * Modified By: 
 * First Modif: Toby, 970919 (pshort fixed, random ac)
 */


void
create_armour()
{
    ::create_armour();
    set_name("boots");
    set_short("pair of black iron boots");
    set_pshort("pairs of black iron boots");
    set_adj("black");
    add_adj("iron");

    set_long("These are a pair of strong iron boots. The spikes at "+
    "the end seem to suggest that they are used for more than just "+
    "walking.\n");

    add_item(({"skull","tiny skull"}),"It is quite grim looking.\n");

    set_ac(15+random(3));
    set_at(A_FEET);
    KVARM(10);
    KWARM(10);
    KVOL(iron);
}
