#include "army.h"

inherit PLATOON;

create_platoon()
{
    set_soldier(BAAZ, 100);
    set_soldier(AURAK, 2);
    set_soldier(SIVAK, 1);

    set_platoon_type("draconian");
}
