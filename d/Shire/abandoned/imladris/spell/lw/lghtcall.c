/*
 * Lightening Call.
 *  Caster can cause a lightening bolt to strike a target within his
 *  range, results are determined on the Lightning Bolt Attack Table.
 *  There must be a storm within 1 mile that is severe enough to
 *  cause precipitations or lightening or heavy winds.
 *  [Elemental Attack, Duration: Instant, Range: 100']
 *
 * Implementation.
 *  Since a weather system is not installed, I will check the
 *  environment for outside conditions, and then do a lightning
 *  elemental attack.
 */

#include "defs.h"

inherit ELEMENTAL_BOLT;

create_elemental_bolt()
{
    set_elem(ELEMENT_FIRE, 10);
    set_spell_name("lightning call");
    set_classes(([1:25]));
    set_desc(
	"If outside, this spell will call a lightening bolt to strike "+
	"a target from a storm nearby."
    );
    set_dt(DT_ELECTR);
    set_reverse();
    set_dam(200);
    set_syntax("[on] <living>");
}

int
start_spell_fail(string str)
{
    if(environment(caster)->query_prop(ROOM_I_INSIDE))
    {
	notify_fail("You can't cast a Lightening Call inside!\n");
	return 1;
    }
    return ::start_spell_fail(str);
}
