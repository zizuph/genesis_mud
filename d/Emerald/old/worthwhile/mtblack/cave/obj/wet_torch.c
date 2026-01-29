/* This is a wet torch. You cannot light it, and it is utterly useless. */
/* Coded 07/05/96 by Tulix III.                                         */

inherit "/std/object";
#include <stdproperties.h>
#include <macros.h>
#include "/d/Emerald/tulix/t_defs.h"

#pragma strict_types

/* Prototype function */
public int do_not_light(string str);

public void
create_object()
{
    set_name("torch");
    set_pname("torches");
    set_adj("wet");
    set_short("wet torch");
    set_pshort("wet torches");
    set_long("This torch is too wet to light. It is useless.\n");

    add_prop(OBJ_I_WEIGHT, 500);
    add_prop(OBJ_I_VOLUME, 600); /* Looks like it will float. */
    add_prop(OBJ_I_VALUE, 0);
    add_prop(OBJ_M_NO_SELL, "Who would possibly want a wet torch?\n");

    add_prop(OBJ_S_WIZINFO, "Take a real torch down into the underwater " +
        "caves in Emerald, and you will get one of these instead. " +
        "Afterall, a torch surely should not work underwater....?\n");
}

public void
init()
{
    ::init();

    add_action( do_not_light, "light" );
}

public int
do_not_light(string str)
{
    object torch;
    
    if (!strlen(str))
    {
        notify_fail("What do you want to light?\n");
        return 0;
    }

    /*  use parse_command to check what player wants to light. */
    parse_command(str, this_player(), "[the] %o", torch);
    
    /* Is this object the one being lit? */
    if (torch == TO)
    {
        tell_room(ENV(this_player()), QCTNAME(this_player()) + " tries to " +
            "light a wet torch. Now that's optimism!\n", this_player() );
        write("Alas, someone carelessly allowed the torch to get wet.\n" +
            "This torch wouldn't light if a dragon breathed on it!\n");
        return 1;
    }
    else
    {
        notify_fail("What do you want to light?\n");
        return 0;
    }
}
