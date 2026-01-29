#pragma strict types
#include "defs.h"
inherit DRAKMERE_GATE_OUTER;

void
create_gates()
{
    set_gates_id("_drakmere_south_gate");
    set_pass_command(({"n", "north"}));
    set_other_room(DRAKMERE_GATE_SOUTH_IN);
    ::create_gates();
}

