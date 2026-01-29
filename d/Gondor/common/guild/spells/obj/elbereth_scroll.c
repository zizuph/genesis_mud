/*
 * /d/Gondor/common/guild/spells/obj/elbereth_scroll.c
 *
 * The scroll with the 'elbereth' spell for the rangers.
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
inherit "/d/Gondor/common/guild/newspells/obj/elbereth_scroll";
#else
inherit "/d/Gondor/common/guild/spells/obj/copy_scroll.c";

#include "/d/Gondor/defs.h"

public void
create_copy_scroll()
{
    add_name("elberethscroll");
    add_adj("elbereth");
    set_file(RANGER_DIR + "spells/text/elbereth.txt");
    set_spell_name("Ways of Warding against Undead");
    set_spell_code("ru");
}
#endif
