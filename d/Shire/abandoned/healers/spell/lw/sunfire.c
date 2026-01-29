/*
 * Sunfire.
 *   This spell produces a sharp ray of sun. It's the equivalent of
 *   a firebolt, except it is 1.5 times stronger, and is of element
 *   life.
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
    set_elem(ELEMENT_LIFE, 10);
    set_spell_name("sunfire");
/*    set_classes(([1:20]));     */
    set_desc(
	"Produces a sharp ray of sunlight, which can be used " +
	"against a living target.\n");
    set_dt(DT_LIGHT);
    set_syntax("[on] <living>");
}
