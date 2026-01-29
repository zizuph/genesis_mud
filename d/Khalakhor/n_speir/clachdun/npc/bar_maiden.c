/*
 * A barmaiden which players will have to order from
 * to recieve food and drink inside the inn
 *
 * She is a rather slow and lazy waitress and will
 * be rude to customers that don't tip her or exetremly
 * nice to who tip well.
 */
#include "local.h"
#include <ss_types.h>
#include <macros.h>
#include <language.h>
#include <const.h>
#include "/d/Khalakhor/sys/defs.h"

inherit "/d/Khalakhor/std/npc/human";

void
create_khalakhor_human()
{
    set_name("brudelna");
    set_gender(G_FEMALE);
    set_adj(({"plump", "ill-tempered"}));

}
