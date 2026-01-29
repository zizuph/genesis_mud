#include "defs.h"
#include <stdproperties.h>

inherit "/d/Shire/common/lib/effect";

int strength;

void set_strength(int s) { strength = s; }
int query_strength() { return strength; }

create_effect()
{
    set_name("_det_invis_effect_");
}

void
do_start_effect(object who)
{
    who->catch_msg(
	"Ah! You feel that you see invisible things clearer now!\n");
    ADD_PROP(who, LIVE_I_SEE_INVIS, strength);
}

void
do_stop_effect(object who)
{
    ADD_PROP(who, LIVE_I_SEE_INVIS, -strength);
    who->catch_msg("You stop seeing invisible things so well.\n");
}
