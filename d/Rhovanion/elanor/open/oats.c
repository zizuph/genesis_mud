inherit "/std/food";

#include <macros.h>
#include <composite.h>

void
create_food()
{
    set_name("oats");
    add_adj("premier");
    set_long("High quality whole oats for horses and ponies\n");
    set_amount(150);
}

int query_is_horse_food() { return 1; }
