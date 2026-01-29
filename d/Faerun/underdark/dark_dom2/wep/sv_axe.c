/*
 *  Pickaxe for the svirfneblin
 *  -- Finwe, July 2006
 */

#include "/d/Faerun/defs.h"
#include "defs.h"
#include <macros.h>
#include <wa_types.h>
#include <formulas.h>
#include <stdproperties.h>

inherit FAERUN_WEP_BASE;

int hit = 35 + random(5),
    pen = 35 + random(5);

void create_faerun_weapon()
{
    set_name("waraxe");
    add_name("axe");
    set_adj("slender");
    set_adj("steel");
    set_short("slender steel waraxe");
    set_long("The " + short() + " is forged of steel. A large, single " +
        "blade is attached to the top of the haft. The axe is well balanced " +
        "and looks sharp.\n");
    add_item(({"blade", "large blade", "sharp blade", "large sharp blade"}),
        "The blade was forged from steel and is half-moon shaped. The edge " +
        "looks razor sharp.\n");
    add_item(({"haft", "handle"}),
        "The haft is slender but looks strong. It was forged of steel " +
        "and polished smooth.\n");

    set_default_weapon(
      hit,
      pen,
      W_AXE,
      W_BLUDGEON | W_SLASH,
      W_ANYH,
      0);

    add_prop(OBJ_I_VALUE,F_VALUE_WEAPON(hit,pen));
}
