inherit "/d/Genesis/newmagic/spells/bolt";

#include <ss_types.h>

public void
create_bolt()
{
    set_spell_element(SS_ELEMENT_WATER, 60);

    set_bolt_pen(800);
    set_bolt_desc("ice");
}
