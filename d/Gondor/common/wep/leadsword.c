/* This is file /d/Gondor/olorin/obj/leadsword.c  */
/* The sword of the orc Captain                   */
/* Olorin, Nov 1992                               */

inherit "/std/weapon";

#include <stdproperties.h>
#include "/sys/wa_types.h"
#include "/sys/formulas.h"
#include <macros.h>

#define BS(message)	break_string(message, 75)

create_weapon() 
{
    set_name(({"broadsword","orcsword","sword","weapon"}));
    set_pname("broadswords");
    add_pname("orcswords");
    add_pname("swords");
    set_short("broadsword");
    set_pshort("broadsword");
    set_long(BS("A heavy broadsword of exceptionally good quality. "
        + "You wonder where the orcs get weapons like this one.\n"));
    set_adj("orc");
    add_adj("broad");
    add_adj("sharp");
    add_adj("heavy");
    set_default_weapon(28,36,W_SWORD,W_SLASH|W_BLUDGEON,W_RIGHT,0);
    add_prop(OBJ_I_VALUE,F_VALUE_WEAPON(28,36)+random(250));
    add_prop(OBJ_I_WEIGHT,
	(F_WEIGHT_DEFAULT_WEAPON(28, W_SWORD) + 1000 + random(1000)));
}
