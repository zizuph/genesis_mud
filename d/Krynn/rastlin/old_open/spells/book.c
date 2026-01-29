/*
 * My magic book, it contains some spells deveplped to
 * test the magic system.
 * 1994 by Rastlin
 */

inherit "/d/Krynn/rastlin/open/spells/spellcasting";

#include <ss_types.h>
#include <stdproperties.h>

void
create_spells()
{
    set_name("book");
    set_short("magic book");
    set_long("A book with nightblue bindings.\n");
    add_spell("fireball", "do_fireball", "Fireball");
    add_spell("heal", "do_healing", "Healing");
    add_spell("firewall", "do_shield", "Firewall");
    add_spell("flame", "do_flame", "Flame Blade");
}

#include "/d/Calia/digit/open/fireball.h"
#include "/d/Krynn/rastlin/open/spells/spells/healing.h"
#include "/d/Krynn/rastlin/open/spells/spells/shield.h"
#include "/d/Krynn/rastlin/open/spells/spells/flame_blade.h"
