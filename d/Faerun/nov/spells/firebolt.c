/*
 * The firebolt spell for Nov.
 *
 * 23/4/2004 - Tilorop
 *
 */
 
inherit "/d/Genesis/newmagic/spells/bolt";

#include <ss_types.h>

public void
create_bolt()
{
    set_spell_element(SS_ELEMENT_FIRE, 20);

    set_bolt_pen(300);
    set_spell_vocal(0);
    set_bolt_desc("fire");
    set_spell_desc(">Shoot a bolt of fire at a target<");
}
