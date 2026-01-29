/*
 * /d/Gondor/common/guild/spells/obj/identify_scroll.c
 *
 * The scroll with the 'identify' spell for the rangers.
 * This spell has not been coded yet. (?)
 *
 * Original version by Elessar.
 *
 * This version by Olorin, December 1996.
 *
 * Copyright (c) 1996 by Christian Markus
 *
 * Modifaction log:
 */
#pragma strict_types

inherit "/d/Gondor/common/guild/spells/obj/magic_scroll.c";

#include "/d/Gondor/defs.h"

public void
create_copy_scroll()
{
    add_name("identifyscroll");
    add_adj( ({ "identify", }) );
    set_file(RANGER_DIR + "spells/text/identify.txt");
    set_spell(RANGER_DIR + "spells/obj/identify_ob");
    set_spell_name("Ways of Seeing");
    set_spell_code("nv");
}
