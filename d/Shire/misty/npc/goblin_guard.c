#include "../local.h"
inherit GOBLIN_BASE;

void create_goblin()
{
    set_base_gob(135);
    set_ran_gob(30);
    set_name("Goblin guard");
    set_ran_wep(({"club"}));
    set_ran_arm(({"shield"}));
    set_def_arm(({"mail","helm"}));
}
