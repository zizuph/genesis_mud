inherit "/d/Kalad/std/armour.c";
#include "/d/Kalad/defs.h"

/*
 * /d/Kalad/common/guilds/khiraa/temple/obj/arms/steel_helm.c
 * Purpose    : Full, black enameled steel helm.
 * Located    : Vile, the armour makes them.
 * Created By : Sarr 17.Feb.97
 * Modified By: 
 * First Modif: Toby, 970919 (pshort fixed)
 */


void
create_armour()
{
    ::create_armour();
    set_name("pants");
    set_short("pair of black cloth pants");
    set_pshort("pairs of black cloth pants");
    set_adj("black");
    add_adj("cloth");

    set_long("These are a pair of finely crafted pants of cloth. "+
    "They are completely black, and look like they would last "+
    "a good while.\n");


    set_ac(3);
    set_at(A_LEGS);
    KVARM(10);
    KWARM(10);
    add_prop(OBJ_I_VOLUME,40);
}
