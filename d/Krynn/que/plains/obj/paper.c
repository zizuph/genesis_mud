
#include "../local.h"

inherit "/d/Krynn/std/furl_scroll";

void
create_scroll()
{
    set_name("piece of paper");
    add_name("paper");
    add_name("help_refugees_quest_paper");

    set_short("piece of paper");
    set_long("This is a piece of paper. There is something on it.\n");
    set_file(PAPER_CONTENT);
    add_prop(OBJ_I_WEIGHT,10);
    add_prop(OBJ_I_VOLUME,2);
    add_prop(OBJ_I_VALUE,0);

    set_furled();
}
