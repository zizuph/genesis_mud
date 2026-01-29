/*
 * The windbolt spell for the Nov.
 *
 * 23/4/2004 - Tilorop
 *
 */
 
inherit "/d/Genesis/newmagic/spells/bolt";

#include <ss_types.h>

public void
create_bolt()
{
    set_spell_element(SS_ELEMENT_AIR, 20);

    set_bolt_pen(300);
    set_spell_vocal(0);
    set_bolt_desc("wind");
    set_spell_desc(">Shoot a bolt of wind at a target<");
}
