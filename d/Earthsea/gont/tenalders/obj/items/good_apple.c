// a juicy red apple

#pragma strict_types

inherit "/std/food";

#include <stdproperties.h>

public void
create_food()
{
    set_name("apple");
    add_adj("macintosh");
    set_adj(({"large", "perfect", "juicy", "red"}));
    set_short("juicy red macintosh apple");
    set_long("A large juicy macintosh apple.\n");
    set_amount(30);
    add_prop(OBJ_I_WEIGHT, 100);
    add_prop(OBJ_I_VOLUME, 100);
    add_prop(OBJ_I_VALUE, 0);
}

public void
special_effect(int num_apples)
{
    object tp = this_player();
    tell_room(environment(tp), "Juice runs down " +
        tp->query_possessive() + " chin.\n", ({ tp }));
    write("Juice runs down your chin.\n");
}

public int
query_good_apple()
{
    return 1;
}
