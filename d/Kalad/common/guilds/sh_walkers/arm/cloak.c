/*
 * /d/Kalad/common/guilds/sh_walkers/arm/cloak.c
 * Created By :  Sarr
 * Modified By:  Rico
 * First Modif:  19.12.96
 */

inherit "/d/Kalad/std/armour";

#include "/d/Kalad/defs.h"
#include "../defs.h"

void
create_armour()
{
    set_name("cloak");
    add_adj("black");
    set_adj("hooded");
    set_short("black hooded cloak");
    set_long("This is a black cloth cloak. It looks thick and "+
        "warm. On the edge of the hood, there is a tiny symbol: "+
        "a grinning skull with two daggers crossed behind it.\n");
    set_long("This is a black, wool cloak.  It is thick and "+
        "obviously quite warm.  On side of the hood, there is "+
        "small symbol, which glitters slightly when it catches "+
        "direct sunlight.\n");

    add_item(({ "symbol", small symbol" }),
        "\n");

    set_at(A_ROBE);

    set_ac(4);

    add_prop(OBJ_I_WEIGHT,800);
    add_prop(OBJ_I_VOLUME,600);
    add_prop(OBJ_I_VALUE,70);
}
