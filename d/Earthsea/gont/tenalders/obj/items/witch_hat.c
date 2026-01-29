#pragma strict_types

inherit "/std/container";

#include <stdproperties.h>
#include <macros.h>

private int STRAW_IN, BIRD_IN = 0;

public void
create_container()
{
    set_name("_witch_hat_");
    add_name("hat");
    set_adj(({"witch's", "pointy", "black", "felt" }));
    set_short("tall black felt hat");
    set_long("A black felt hat with a tall crown that " +
        "comes to a point. It appears to be fairly large, and " +
        "very dark when you look inside it.\n");
    add_prop(CONT_I_WEIGHT, 500);
    add_prop(CONT_I_MAX_WEIGHT, 50000);
    add_prop(CONT_I_MAX_VOLUME, 15000);
    add_prop(CONT_I_VOLUME, 1000);
    add_prop(CONT_I_HIDDEN, 1);
    add_cmd_item((({"hat", "black felt hat", "black hat",
        "felt hat"})), "wear", VBFC_ME("wear_hat"));
}

public int
prevent_enter(object ob)
{
    if(!present(this_object(), this_player()))
    {
        write("You don't have the " + query_short() + "!\n");
        return 1;
    }

    if(ob->id("bird") || ob->id("straw"))
    {
        change_prop(CONT_I_HIDDEN, 0);

        if(ob->id("bird"))
        {
            BIRD_IN = 1;
        } else {
            STRAW_IN = 1;
        }

        return 0;
    }

    write("You can't put that in there!\n");

    return 1;
}

public mixed
wear_hat()
{
    write("The hat is too big for you!\n");
    return 1;
}

public int
query_bird_in()
{
    return BIRD_IN;
}

public int
query_straw_in()
{
    return STRAW_IN;
}

public void
leave_inv(object ob, object to)
{
    ::leave_inv(ob, to);

    if(ob->id("bird"))
    {
        BIRD_IN = 0;
    } else if(ob->id("straw")) {
        STRAW_IN = 0;
    }
}
