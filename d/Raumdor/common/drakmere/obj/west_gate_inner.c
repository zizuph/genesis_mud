#pragma strict types
#include "defs.h"
inherit DRAKMERE_GATE_INNER;

void
create_gates()
{
    ::create_gates();
    set_gates_id("_drakmere_west_gate");
    set_pass_command(({"w", "west"}));
    set_other_room(DRAKMERE_GATE_WEST_OUT);
}
