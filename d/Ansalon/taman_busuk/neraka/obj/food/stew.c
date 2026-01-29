
inherit "/std/food";
#include <stdproperties.h>

create_food()
{
    set_name("stew");
    add_name("bowl");
    set_short("bowl of stew");
    set_pshort("bowls of stew");
    set_long("It is a bowl of a brownish stew, with all manner of " +
        "odds and ends in it.\n");
    set_amount(220);
}

