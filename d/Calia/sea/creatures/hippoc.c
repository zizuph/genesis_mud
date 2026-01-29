
 /*    Inherit file for Hippocampus

    coder(s):    Jaacar

 
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
create_hippocampus()
{
    set_race_name("hippocampus");
}

void
create_calia_npc()
{
    create_hippocampus();
}

void
attacked_by(object attacker)
{
    ::attacked_by(attacker);
    MAP_ATTACK(FIND_STR_IN_OBJECT("hippocampi", environment()), attacker);
}

