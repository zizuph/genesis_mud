
 /*    Inherit file for Tritons

    coder(s):    Digit

    history:    22.7.95    header added          Digit

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
create_triton()
{
    set_race_name("triton");
}

void
create_calia_npc()
{
    create_triton();
}

void
attacked_by(object attacker)
{
    ::attacked_by(attacker);
    MAP_ATTACK(FIND_STR_IN_OBJECT("tritons", environment()), attacker);
    MAP_ATTACK(FIND_STR_IN_OBJECT("mermaids",environment()), attacker);
    MAP_ATTACK(FIND_STR_IN_OBJECT("dragonsauri",environment()), attacker);
    MAP_ATTACK(FIND_STR_IN_OBJECT("kings",environment()), attacker);
}

void
attack_object(object ob)
{
    ::attack_object(ob);
    MAP_ATTACK(FIND_STR_IN_OBJECT("tritons", environment()), ob);
    MAP_ATTACK(FIND_STR_IN_OBJECT("mermaids", environment()), ob);
    MAP_ATTACK(FIND_STR_IN_OBJECT("dragonsauri", environment()), ob);
    MAP_ATTACK(FIND_STR_IN_OBJECT("kings", environment()), ob);
}
