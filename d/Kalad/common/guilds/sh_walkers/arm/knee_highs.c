/*
 * /d/Kalad/common/guilds/sh_walkers/arm/knee_highs.c
 * Created By :  Rico
 * Created On :  19.12.96
 */

inherit "/d/Kalad/std/armour";

#include "/d/Kalad/defs.h"
#include "../defs.h"

void
create_armour()
{
    set_name("boots");
    add_name("knee highs");
    add_adj("black");
    set_adj("leather");
    set_short("pair of black leather knee highs");
    set_pshort("pairs of black leather knee highs");
    set_long("This is a pair of well made, black, leather boots.  "+
        "When worn, they go up to just below the knee.  Perfect "+
        "for protecting a thief's legs from getting all scratched "+
        "while at work.\n");

    set_at(A_FEET);

    set_ac(4);
    set_am(({ -3,  2,  1 }));  /* impale, slash, bludgeon */

    add_prop(OBJ_I_WEIGHT, (600 + random(250)));
    add_prop(OBJ_I_VOLUME, (600 + random(110)));
    add_prop(OBJ_I_VALUE,  (140 + random( 35)));
}
