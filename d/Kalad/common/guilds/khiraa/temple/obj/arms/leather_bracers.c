inherit "/d/Kalad/std/armour.c";
#include "/d/Kalad/defs.h"

/*
 * /d/Kalad/common/guilds/khiraa/temple/obj/arms/steel_helm.c
 * Purpose    : Full, black enameled steel helm.
 * Located    : Vile, the armour makes them.
 * Created By : Sarr 17.Feb.97
 * Modified By: 
 * First Modif: Toby, 970919 (pshort fixed,random ac)
 */


void
create_armour()
{
    ::create_armour();
    set_name("bracers");
    set_short("pair of black studded-leather bracers");
    set_pshort("pairs of black studded-leather bracers");
    set_adj("black");
    add_adj("studded-leather");

    set_long("These bands are made of strong and hardened black "+
    "leather. They are covered with small silver studs, and a "+
    "picture of a white grim-looking skull.\n");

    add_item(({"skull","tiny skull"}),"It is quite grim looking.\n");

    set_ac(7+random(3));
    set_at(A_ARMS);
    KVARM(10);
    KWARM(10);
    add_prop(OBJ_I_VOLUME, 300);
}
