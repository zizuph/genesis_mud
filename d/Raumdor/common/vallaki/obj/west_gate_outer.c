#pragma strict types
#include "defs.h"
inherit DRAKMERE_GATE_OUTER;

void
create_gates()
{
    set_gates_id("_drakmere_west_gate");
    set_pass_command(({"e", "east"}));
    set_other_room(DRAKMERE_GATE_WEST_IN);
    ::create_gates();
}

