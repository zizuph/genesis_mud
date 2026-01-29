inherit "/d/Kalad/std/armour.c";
#include "/d/Kalad/defs.h"

/*
 * /d/Kalad/common/guilds/khiraa/temple/obj/arms/steel_helm.c
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
    set_name("helmet");
    set_short("black studded-leather helmet");
    set_adj("black");
    add_adj("studded-leather");
    set_long("This a nice looking helmet made from leather. It is "+
    "hardened and strong, and covered with small silver studs. It "+
    "is dyed black, and over the eye holes, you see the picture "+
    "of a white grim-looking skull.\n");

    set_ac(9);
    set_at(A_HEAD);
    KVARM(10);
    KWARM(10);
    add_prop(OBJ_I_VOLUME, 500);
}
