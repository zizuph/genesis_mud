/*
 * /d/Gondor/guilds/rangers/spells/obj/elbereth_scroll.c
 *
 * The scroll with the 'elbereth' spell for the rangers.
 * Found in /d/Gondor/morgul/obj/key_hole.c
 *
 * Original version by Elessar.
 *
 * This version by Olorin, December 1996.
 *
 * Copyright (c) 1996 by Christian Markus
 *
 * Modifaction log:
 *    Alto, February 2002. Move, no major modifications.
 */
#include "/d/Gondor/defs.h"
#include "../../rangers.h"

inherit COPY_SCROLL;

public void
create_copy_scroll()
{
    add_name("elberethscroll");
    add_adj("elbereth");
    set_file(RANGER_SPELL_TXT + "elbereth.txt");
    set_spell_name("Ways of Warding against Undead");
    set_spell_code(SPELL_ELBERETH);
}
