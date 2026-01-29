/*
 * Shock bolt.
 *   A bolt of intense charged light is shot from the palm of the caster,
 *   and the results are given from the Shock Bolt attack table.
 *   [Elemental attack spell, Duration instant, Range: 100']
 *
 * Implementation:
 *   Uses the same attack scheme as fire bolt. Defense is only
 *   MAGIC_I_RES_LIGHT. I use the message.c attack messages.
 */

#include "defs.h"

inherit ELEMENTAL_BOLT;

create_elemental_bolt()
{
    set_elem(ELEMENT_FIRE, 10);
    set_spell_name("shock bolt");
    set_classes(([1:7]));
    set_desc(
	"Casts a bolt of intense charged light against one living.");
    set_dt(DT_LIGHT);
    set_syntax("[on] <living>");
}
