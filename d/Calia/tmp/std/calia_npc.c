/*      This is to be inherited into Calia npcs.

    coder(s):   Glykron

    history:     1. 9.93    created                         Glykron

    purpose:    to liven the calian npcs

    quests:     none
    special:    none

    to do:      none
    bug:        none known
*/

inherit "/std/monster";
#include "/d/Calia/tmp/sys/random.h"
#include "defs.h"

void
create_calia_npc()
{
}

void
create_monster()
{
    object this;

    this = THIS;
    set_name(RANDOM_WORD);
    set_adj(RANDOM_ADJS);
    create_calia_npc();
}
