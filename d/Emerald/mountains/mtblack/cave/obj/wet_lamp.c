/* This is a wet lamp. You cannot light it, and it is utterly useless. */
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
    set_name("lamp");
    set_pname("lamps");
    set_adj("wet");
    set_short("wet oil-lamp");
    set_pshort("wet oil-lamps");
    set_long("This oil-lamp is useless. Unfortunately it was damaged " +
        "beyond repair when it was exposed to water.\n");

    add_prop(OBJ_I_WEIGHT, 800);
    add_prop(OBJ_I_VOLUME, 300); /* Looks like it will not float. */
    add_prop(OBJ_I_VALUE, 0);
    add_prop(OBJ_M_NO_SELL, "The lamp is useless, and not worth anything.\n");

    add_prop(OBJ_S_WIZINFO, "Take a real lamp down into the underwater " +
        "caves in Emerald, and you will get one of these instead. " +
        "Afterall, a lamp surely should not work underwater....?\n");
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
    object lamp;
    
    if (!strlen(str))
    {
        notify_fail("What do you want to light?\n");
        return 0;
    }

    /*  use parse_command to check what player wants to light. */
    parse_command(str, this_player(), "[the] %o", lamp);
    
    /* Is this object the one being lit? */
    if (lamp == TO)
    {
        tell_room(ENV(this_player()), QCTNAME(this_player()) + " tries to " +
            "light a wet lamp. Nice try.\n", this_player() );
        write("Alas, someone carelessly allowed the lamp to get wet.\n" +
            "It has been damaged beyond repair by the water.\n");
        return 1;
    }
    else
    {
        notify_fail("What do you want to light?\n");
        return 0;
    }
}
