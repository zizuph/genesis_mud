/*
 * Bree-landers
 * Finwe, June 2002
 */
inherit "/std/weapon";
#include "/d/Shire/sys/defs.h"
#include "defs.h"
#include <macros.h>
#include <stdproperties.h>
#include <formulas.h>
#include <wa_types.h>


void
create_weapon()
{
    set_name(({"longsword","sword"}));
    set_pname(({"longswords","swords"}));
    set_short("sturdy longsword");
    set_pshort("sturdy longswords");
    set_adj(({"sturdy", "long"}));
    set_long("This is a long sword, often used by men of Bree. It " +
        "is sturdy, and appears to have been forged by the " +
        "Blacksmiths as a gift to the men of Bree. This sword has " +
        "a sharp edge and looks like a very fine weapon.\n");
    	    
    set_hit(29);
    set_pen(25);
    set_wt(W_SWORD);
    set_dt(W_SLASH);
    set_hands(W_ANYH);
    
    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(29,25));
}
