
 /*    The inherit file for water krougs

    coder(s):    Digit, Maniac

    history:    21.7.95    header added          Digit

 */

#include <filter_funs.h>
#include <cmdparse.h>
#include "defs.h"
#include GLYKDEF
#include MAP_HEADER
#include RANDOM_HEADER
#include CALIAN_HEADER
inherit CALIA_NPC;

object *met_list;

void
create_wkroug()
{
    set_race_name("water-kroug");
    add_name("kroug");
}

void
create_calia_npc()
{
    create_wkroug();
}

void
attacked_by(object attacker)
{
    ::attacked_by(attacker);
    MAP_ATTACK(FIND_STR_IN_OBJECT("water-krougs", environment()), attacker);
}

