/*
 *	File: ~hand/guards/arm/bgloves.c
 *
 *	A pair of fashionable, black, leather gloves.
 *	Quite popular with Guards of the Steel Faith.
 *
 *				~Hand 26.06.96
 *				Revision:
 */

#include "../defs.h"

inherit "/std/armour";

create_armour()
{
    set_name("gloves");
    set_adj(({ "black", "leather" }));
    set_long("\nThis is a fashionable pair of quality, black leather "+
      "gloves. They don't afford much protection from a blade, but they "+
      "are quite popular among the Guards of the Steel Faith.\n\n");

    set_at(A_HANDS);

    set_ac(2);
    /* Even so.. let's modify the protection somewhat. */
    /*        impale, slash, bludgeon     */
    set_am(({    1,      1,     -2     }));

    add_prop(OBJ_I_WEIGHT, 80);
    add_prop(OBJ_I_VOLUME, 20);
    add_prop(OBJ_I_VALUE, (45 + random(70)));
}

