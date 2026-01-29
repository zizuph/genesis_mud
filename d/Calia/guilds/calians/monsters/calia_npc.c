/*      This is to be inherited into Calia npcs.

    coder(s):   Glykron

    history:    17.11.94   moved random name/adjs to calian.c    Maniac 
                1. 9.93    created                         Glykron

    purpose:    to liven the calian npcs

    quests:     none
    special:    none

    to do:      none
    bug:        none known
*/

#pragma save_binary

inherit "/std/monster";
#include "defs.h"
#include RANDOM_HEADER

void
create_calia_npc()
{
}

void
create_monster()
{

    set_name(RANDOM_WORD);
    set_adj(RANDOM_ADJS);
 
    create_calia_npc();
}
