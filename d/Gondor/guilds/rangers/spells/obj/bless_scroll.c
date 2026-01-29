/*
 * /d/Gondor/guilds/rangers/spells/obj/bless_scroll.c
 *
 * The scroll with the 'bless' spell for the Rangers of Ithilien.
 *
 * Coded by Gwyneth, 10/20/03
 *
 * Modifaction log:
 */
#include "/d/Gondor/defs.h"
#include "../../rangers.h"

inherit COPY_SCROLL;

public void
create_copy_scroll()
{
    add_name("blessscroll");
    add_adj( ({ "bless", "blessing", }) );
    set_file(RANGER_SPELL_TXT + "bless.txt");
    set_spell_name("Ways of Blessing");
    set_spell_code(SPELL_BLESS);
}
