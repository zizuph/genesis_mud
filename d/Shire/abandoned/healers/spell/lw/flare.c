/*
 * Flare.
 *  A ball of light is shot from the palm of the caster and can
 *  be cast against the target as a shock bolt delivering heat
 *  criticals.
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
    set_spell_name("flare");
    set_classes(([1:12]));
    set_desc(
	"A ball of light is shot from the casters palm, and can "+
	"be cast against a target delivering heat criticals."
    );
    set_dt(DT_HEAT);
    set_dam(140);
    set_syntax("[on] <living>");
}
