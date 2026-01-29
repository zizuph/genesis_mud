/* Amanita poison by Jeremiah and Teth, Feb.20,96
*/

inherit "/std/poison_effect";

#include "/d/Krynn/common/defs.h"
#include <poison_types.h>
#include <ss_types.h>


void
create_poison_effect()
{
    set_damage(({ POISON_HP, 50, POISON_MANA, 40 }));
}

