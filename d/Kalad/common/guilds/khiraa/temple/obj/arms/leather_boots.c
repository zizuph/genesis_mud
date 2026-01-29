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
    set_short("pair of black studded-leather boots");
    set_pshort("pairs of black studded-leather boots");
    set_adj("black");
    add_adj("studded-leather");

    set_long("These are a pair of finely crafted boots of blackened "+
    "leather. The heels and does are reinforced by steel, and they "+
    "are covered with tiny silver studs.\n");


    set_ac(7+random(3));
    set_at(A_FEET);
    KVARM(10);
    KWARM(10);
    add_prop(OBJ_I_VOLUME,100);
}
