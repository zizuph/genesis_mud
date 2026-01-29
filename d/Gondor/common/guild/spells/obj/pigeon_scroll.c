/*
 * /d/Gondor/common/guild/spells/obj/pigeon_scroll.c
 *
 * The scroll with the 'whistle' spell for the rangers.
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
inherit "/d/Gondor/common/guild/newspells/obj/pigeon_scroll";
#else
inherit "/d/Gondor/common/guild/spells/obj/copy_scroll.c";

#include "/d/Gondor/defs.h"

public void
create_copy_scroll()
{
    add_name("pigeonscroll");
    add_adj("pigeon");
    set_file(RANGER_DIR + "spells/text/whistle.txt");
    set_spell_name("Ways of Communing");
    set_spell_code("sp");
}
#endif
