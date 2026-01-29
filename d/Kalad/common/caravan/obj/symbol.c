inherit "/std/object";
#include "/d/Kalad/defs.h"
/* by Antharanos */

create_object()
{
    set_name("symbol");
    add_name("dark sun");
    set_short("symbol of a dark sun");
    add_name("hsotoot");
    set_long("The symbol of the Holy Order of Thanar.\n");
}

void
enter_env(object to, object from)
{
    to->catch_msg("Your symbol of a dark sun just disappears!\n");
    set_alarm(0.0, 0.0, remove_object);
}
