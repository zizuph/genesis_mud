///d/Avenir/common/city/zigg/obj/thorn.c
// creator(s):   Zielia 2006
// last update:
// purpose:      ritual item for Maree
// note:
// bug(s):
// to-do:
#pragma strict_types

#include <stdproperties.h>
#include <formulas.h>
#include <ss_types.h>
#include <wa_types.h>
#include "zigg.h"

inherit "/d/Avenir/inherit/weapon";

public void
create_weapon(void)
{
    set_short("large, very sharp thorn");
    set_name(({"thorn", "barb"}));
    add_adj(({"sharp", "large", "long"}));

    add_prop(OBJ_I_WEIGHT, 25);         /* 0.025 kg */
    add_prop(OBJ_I_VOLUME, 5);         /* 0.005  L  */
    add_prop(OBJ_I_VALUE,  10);

    set_wt(W_KNIFE);
    set_dt(W_IMPALE);
    set_hands(W_ANYH);
    set_hit(1);
    set_pen(1);

    set_long("A very long and thick thorn from some unknown plant. It is "+
     "extremely hard and has sharp point that looks to be stained with "+
     "blood.\n");
}
