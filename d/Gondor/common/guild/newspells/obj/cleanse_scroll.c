/*
 * /d/Gondor/common/guild/spells/obj/cleanse_scroll.c
 *
 * The scroll with the 'cleanse' spell for the rangers.
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


#include "/d/Gondor/defs.h"
#include "../spells.h"

inherit COPY_SCROLL;

public void
create_copy_scroll()
{
    add_name("cleansescroll");
    add_adj( ({ "cleanse", "cleansing", }) );
    set_file(RANGER_SPELL_TXT + "cleanse.txt");
    set_spell_name("Ways of Cleansing");
    set_spell_code(SPELL_CLEANSE);
}
