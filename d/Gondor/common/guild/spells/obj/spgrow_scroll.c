/*
 * /d/Gondor/common/guild/spells/obj/spgrow_scroll.c
 *
 * The scroll with the 'speedgrowth' spell for the rangers.
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

inherit "/d/Gondor/common/guild/spells/obj/copy_scroll.c";

#include "/d/Gondor/defs.h"

public void
create_copy_scroll()
{
    add_name("speedgrowthscroll");
    add_adj( ({ "speedgrowth", "speedgrowing", }) );
    set_file(RANGER_DIR + "spells/text/speedgrow.txt");
    set_spell_name("Ways of Growth");
    set_spell_code("sg");
}
