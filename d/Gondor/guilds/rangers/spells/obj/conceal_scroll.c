/*
 * /d/Gondor/guilds/rangers/spells/obj/conceal_scroll.c
 *
 * The scroll with the 'conceal' spell for the Rangers of the North.
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
    add_name("concealscroll");
    add_adj( ({ "conceal", "concealing", }) );
    set_file(RANGER_SPELL_TXT + "conceal.txt");
    set_spell_name("Ways of Concealing");
    set_spell_code(SPELL_CONCEAL);
}
