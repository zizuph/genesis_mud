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
    set_short("black studded-leather breastplate");
    set_adj("black");
    add_adj("studded-leather");
    set_long("This is a very finely crafted breastplate made of "+
    "harden leather and quilt, covered with many silver studs. The "+
    "leather is dyed black, and a white grim-looking skull is painted "+
    "on the center.\n");
    set_ac(12);
    set_at(A_TORSO);
    KVARM(10);
    KWARM(10);
    add_prop(OBJ_I_VOLUME, 1000);
}
