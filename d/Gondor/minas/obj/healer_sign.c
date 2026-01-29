/*
 *  /d/Gondor/minas/obj/healer_sign.c
 *
 *  A small sign announcing the temporary closure of the HoH 
 *
 *  Last modified by Alto, 07 April 2001
 *
 */

inherit "/std/object";

#include <macros.h>
#include <stdproperties.h>
#include "/d/Gondor/defs.h"

create_object()
{
    set_name("sign");
    set_short("small sign is posted here");
    set_adj("small");
    set_long("The small sign reads: \n\n\n"
        + "\tThe Houses of Healing are temporarily\n"
        + "\tclosed to the public as the result of\n "
        + "\ta general quarantine. We apologize\n"
        + "\tfor the inconvenience, and anticipate\n"
        + "\tadmitting new patients soon.\n\n"
        + "\t\t\tRegretfully,\n\n"
        + "\t\t\tIoreth, Elder Healer\n\n\n");

    add_prop(OBJ_M_NO_GET,1);
}

public mixed
command_read(int m)
{
    if (m)
    {
        this_player()->more(query_long());
    }
    else
    {
        write(query_long());
    }

    return 1;
}


