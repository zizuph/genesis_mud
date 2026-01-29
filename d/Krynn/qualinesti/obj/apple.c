/* The apple picked from the tree in Qualinesti. */

inherit "/std/food";
#include <stdproperties.h>

create_food()
{
    set_name("apple");
    add_name( ({ "fruit", "apple fruit" }) );
    set_adj("red");
    add_adj("big");
    set_short("big red apple");
    set_pshort("big red apples");
    set_long("This is a hard round fruit with a smooth red skin. It is " +
        "quite big as for the one picked from the wild growing apple tree.\n");
    set_amount(15);
}
