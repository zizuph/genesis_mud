#include "defs.h"

inherit STD_DIR + "good_fighter";

void
create_monster()
{
    ::create_monster();
    set_name("fighter" + OB_NUM(TO));
    add_name("fighter");
}

