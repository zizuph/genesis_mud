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
    set_name("gloves");
    set_short("pair of black studded-leather gloves");
    set_pshort("pairs of black studded-leather gloves");
    set_adj("black");
    add_adj("studded-leather");

    set_long("These are a pair of finely crafted leather gloves. "+
    "They are dyed black, and are covered with small silver "+
    "studs.\n");

    set_ac(5);
    set_at(A_HANDS);
    KVARM(10);
    KWARM(10);
    add_prop(OBJ_I_VOLUME,100);
}
