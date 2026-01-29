/* Brigand sword by Teth, April 6, 1996 */

inherit "/std/weapon";
#include <wa_types.h>
#include <formulas.h>
#include <language.h>
#include <macros.h>
#include "../local.h"

create_weapon()
{
    set_name("rapier");
    set_short("sharp rapier");
    set_adj("sharp");
    set_pshort("sharp rapiers");
    add_name(({"weapon","sword"}));
    add_pname(({"weapons","swords"}));
    set_long("This sharp rapier is the preferred sword of brigands, " +
        "thieves and cutthroats. It is a quick and light weapon, " +
        "useful for short skirmishes and raids.\n");
    set_wf(TO);
    set_default_weapon(12, 10, W_SWORD, W_SLASH | W_IMPALE, W_ANYH);

    add_prop(OBJ_I_VOLUME, 1500);
    add_prop(OBJ_I_WEIGHT, 2000);
    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(12,10));
}




