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
 *    Alto, February 2002. Move, no major revisions.
 */
#include "/d/Gondor/defs.h"
#include "../../rangers.h"

inherit COPY_SCROLL;

public void
create_copy_scroll()
{
    add_name("pigeonscroll");
    add_adj("pigeon");
    set_file(RANGER_SPELL_TXT + "whistle.txt");
    set_spell_name("Ways of Communing");
    set_spell_code(SPELL_WHISTLE);
}
