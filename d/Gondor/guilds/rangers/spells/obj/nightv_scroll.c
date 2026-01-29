/*
 * /d/Gondor/guilds/rangers/spells/obj/nightv_scroll.c
 *
 * Found in /d/Gondor/common/quest/nv/wight.c
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
    add_name("nightvisionscroll");
    add_adj( ({ "nightvision" }) );
    set_file(RANGER_SPELL_TXT + "nightvision.txt");
    set_spell_name("Ways of Seeing");
    set_spell_code(SPELL_NIGHTVISION);
}

