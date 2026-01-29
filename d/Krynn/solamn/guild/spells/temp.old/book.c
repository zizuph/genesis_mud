/*
 * My magic book, it contains some spells deveplped to
 * test the magic system.
 * 1994 by Rastlin
 */

#include "/d/Krynn/common/defs.h"
#include "local.h"

inherit SPELLCAST_BASE;

#include <ss_types.h>
#include <stdproperties.h>

void
create_spells()
{
    set_name("book");
    set_short("magic book");
    set_long("A book with nightblue bindings.\n");
    add_spell("perceive", "do_perceive", "Perceive");
}

#include SPELL_PERCEIVE

