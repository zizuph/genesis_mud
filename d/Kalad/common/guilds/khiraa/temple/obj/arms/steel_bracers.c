inherit "/d/Kalad/std/armour.c";
#include "/d/Kalad/defs.h"

/*
 * /d/Kalad/common/guilds/khiraa/temple/obj/arms/steel_helm.c
 * Purpose    : Full, black enameled steel helm.
 * Located    : Vile, the armour makes them.
 * Created By : Sarr 17.Feb.97
 * Modified By: 
 * First Modif: Toby, 970919 (pshort fixed, random ac added)
 */


void
create_armour()
{
    ::create_armour();
    set_name("bracers");
    set_short("pair of black steel bracers");
    set_pshort("pairs of black steel bracers");
    set_adj("black");
    add_adj("steel");

    set_long("This is a strong and heavy set of bracers to wear "+
    "around the arms. They have a tiny skull on the sides.\n");

    add_item(({"skull","tiny skull"}),"It is quite grim looking.\n");

    set_ac(19+random(3));
    set_at(A_ARMS);
    KVARM(10);
    KWARM(10);
    KVOL(steel);
}
