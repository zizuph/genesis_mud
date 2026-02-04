/* A trainer npc for the minstrel guild. 
 *
 * Arman Dec 2019
 */

#pragma save_binary

inherit "/std/monster";
inherit "/lib/trade";

#include <macros.h>
#include <stdproperties.h>
#include "/d/Terel/common/terel_defs.h"

void
create_monster()
{
    if (!IS_CLONE) 
       return;

    set_name("tutor");
    set_adj("wizened");
    add_adj("elven");
    set_short("wizened elven tutor");
    set_race_name("elf");

    set_long("Before you stands an elderly elven Guild tutor, "
        + "skilled in teaching visiting lay minstrels ancient "
        + "languages and how to weave spellcraft in to their "
        + "songs of Power to make them more effective. Lay "
        + "minstrels may <learn> or <improve> these skills " 
        + "for a fee.\n");

    set_alignment(500);
}
