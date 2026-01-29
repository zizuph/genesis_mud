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
    set_name("helm");
    set_short("black iron helm");
    set_adj("black");
    add_adj("iron");
    set_long("This great helm is made of some very heavy, but solid iron. "+
    "It is enameled jet black, and you see a tiny skull symbol on "+
    "the forehead section. Ugly looking horns protrude from the jaw "+
    "area, giving it a demonic look.\n");

    add_item(({"skull","tiny skull"}),"It is quite grim looking.\n");

    set_ac(20);
    set_at(A_HEAD);
    KVARM(10);
    KWARM(10);
    KVOL(iron);
}
