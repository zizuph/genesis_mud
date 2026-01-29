#pragma strict types
#include "defs.h"
inherit DRAKMERE_GATE_INNER;

void
create_gates()
{
    ::create_gates();
    set_gates_id("_drakmere_south_gate");
    set_pass_command(({"s", "south"}));
    set_other_room(DRAKMERE_GATE_SOUTH_OUT);
}
