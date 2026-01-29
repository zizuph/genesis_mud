/* The quest apple used in apple quest in Krynn */

inherit "/std/food";
#include <stdproperties.h>

create_food()
{
    remove_name(query_name(1));
    set_name("apple");
    set_adj("red");
    add_name("quest_apple");
    set_long("It looks very tasty.\n");
    set_amount(110);
}

