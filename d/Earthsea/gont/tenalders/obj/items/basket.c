#pragma strict_types

inherit "/std/container";

#include <stdproperties.h>
#include <macros.h>

private int straw_in = 0, bird_in = 0;

public void
create_container()
{
    set_name("_basket_");
    add_name("basket");
    set_adj(({ "woven", "reed" }));
    set_short("woven reed basket");
    set_long("A brown basket which is constructed from woven " +
        "reeds. It is medium-sized.\n");
    add_prop(CONT_I_WEIGHT, 500);
    add_prop(CONT_I_MAX_WEIGHT, 50000);
    add_prop(CONT_I_MAX_VOLUME, 15000);
    add_prop(CONT_I_VOLUME, 1000);
    add_prop(CONT_I_HIDDEN, 1);
    add_prop(OBJ_I_VALUE, 50);
    add_prop(OBJ_M_NO_BUY, 1);
}

public int
prevent_enter(object ob)
{
    object to = this_object(), tp = this_player();

    if(!present(to, this_player()))
    {
        tp->catch_tell("You don't have the " + query_short() + "!\n");
        return 1;
    }

    if(ob->id("bird") || ob->id("straw"))
    {
        change_prop(CONT_I_HIDDEN, 0);

        if(ob->id("bird"))
        {
            bird_in = 1;
        }

        if(ob->id("straw"))
        {
            straw_in = 1;
        }

        return 0;
    }

    tp->catch_tell("You can't put that in there!\n");

    return 1;
}

public int
query_bird_in()
{
    return bird_in;
}

public int
query_straw_in()
{
    return straw_in;
}

public void
leave_inv(object ob, object to)
{
    ::leave_inv(ob, to);

    if(ob->id("bird"))
    {
        bird_in = 0;
    } else if(ob->id("straw")) {
        straw_in = 0;
    }
}
