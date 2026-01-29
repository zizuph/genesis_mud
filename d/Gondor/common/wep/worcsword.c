/* This is file /d/Gondor/olorin/obj/orcsword.c   */
/* The typical scimitar of an teamorc             */
/* Olorin, Nov 1992                               */

inherit "/std/weapon";

#include <stdproperties.h>
#include "/sys/wa_types.h"
#include "/sys/formulas.h"
#include <macros.h>

#define BS(message)	break_string(message, 75)

create_weapon() 
{
    int i, j;
    i = 18 + random(10);
    j = 15 + random(10);
    set_name(({"scimitar","orcsword","sword","weapon"}));
    set_pname("scimitars");
    add_pname("orcswords");
    add_pname("swords");
    set_short("scimitar");
    set_pshort("scimitars");
    set_long(BS("A heavy orc scimitar, but of exceptionally good quality. "
        + "The hilt is adorned with what looks like a crude depiction of an eye.\n"));
    set_adj("orc");
    add_adj("curved");
    add_adj("sharp");
    add_adj("heavy");
    set_default_weapon(j,i,W_SWORD,W_SLASH|W_BLUDGEON,W_ANYH,0);
    add_prop(OBJ_I_VALUE,F_VALUE_WEAPON(j,i)-500+random(250));
    add_prop(OBJ_I_WEIGHT,
	(F_WEIGHT_DEFAULT_WEAPON(21, W_SWORD) + 500 + random(1000)));
}
