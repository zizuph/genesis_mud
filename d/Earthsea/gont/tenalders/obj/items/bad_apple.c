// a juicy red apple, with a worm in it

#pragma strict_types

inherit "/std/food";

#include <stdproperties.h>
#include <macros.h>

public void
create_food()
{
    set_name("apple");
    set_adj(({ "shrivelled", "brown" }));
    set_short("shrivelled brown apple");
    set_long("A shrivelled brown apple. It doesn't look too " +
        "appetising.\n");
    set_amount(30);
    add_prop(OBJ_I_WEIGHT, 100);
    add_prop(OBJ_I_VOLUME, 100);
    add_prop(OBJ_I_VALUE, 0);

    setuid();
    seteuid(getuid());
}

public void
special_effect(int num_apples)
{
    object tp = this_player(), worm;

    setuid();
    seteuid(getuid(this_player()));

    worm = clone_object("/d/Earthsea/gont/tenalders/obj/items/worm");
    worm->move(environment(tp));

    tell_room(environment(tp), QCTNAME(tp) + " spits out a " +
        "fat green worm!\n", ({ tp }));
    write("You spit out a fat green worm!\n");
}
