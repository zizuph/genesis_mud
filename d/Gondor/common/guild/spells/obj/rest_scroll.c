/*
 * /d/Gondor/common/guild/spells/obj/rest_scroll.c
 *
 * The scroll with the 'rest' spell for the rangers.
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

#include "../ranger_spell_defs.h"

#ifdef NEW_RANGER_MAGIC
inherit "/d/Gondor/common/guild/newspells/obj/rest_scroll";
#else
inherit "/d/Gondor/common/guild/spells/obj/copy_scroll.c";

#include "/d/Gondor/defs.h"

public void
create_copy_scroll()
{
    add_name("restscroll");
    add_adj( ({ "rest", "resting", }) );
    set_file(RANGER_DIR + "spells/text/rest.txt");
    set_spell_name("Ways of Resting");
    set_spell_code("re");
}
#endif
