/* Malevin poison effect by Teth Jan 1997 */

inherit "/std/poison_effect";

#include "/d/Krynn/common/defs.h"
#include <poison_types.h>
#include <ss_types.h>
#include <macros.h>


void
create_poison_effect()
{
    set_damage(({ POISON_HP, 200, POISON_MANA, 200 }));
}

string query_recover() { return MASTER; }
