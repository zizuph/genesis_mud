/*
 *  /d/Gondor/minas/houses/dinen3.c
 *
 *  The Rath Dinen, part of the midsection of the path.
 *
 *  Alto, 12 April 2001
 *
 */

#pragma strict_types

inherit "/d/Gondor/std/room.c";
inherit "/d/Gondor/minas/lib/dinen_funcs.c";

#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include "/d/Gondor/defs.h"
#include "/d/Gondor/std/tell.c"


#define INNER_MINAS "/d/Gondor/minas"

public int  test_dis();

public void
create_gondor()
{
    set_short("Somewhere along the Rath Dinen");
    set_long("You are somewhere along the Rath Dinen, or Silent "
        + "Street. The fog has grown so dense that you can no longer "
        + "see the path or its surroundings. To make matters worse, "
        + "you have a strong feeling that you are no longer alone.\n");

    add_exit(INNER_MINAS + "/dinen/dinen4", "southeast", test_dis);
    add_exit(INNER_MINAS + "/dinen/dinen2", "east", 0, 0, test_obv());

    /* add the common room items for the Rath Dinen path */

    add_rath_dinen_items();    

    set_tell_time(120);

    /* add the common tells for the Rath Dinen path */

    add_rath_dinen_tells();
    
    reset_room();

}   

/*
 * This function enables the random room tells.
 */

public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if(interactive(ob))
        start_room_tells();
}

/* Test discipline of player to see if they are big enough to handle it */

public int
test_dis()
{
    if (TP->query_race() == "kender")   /* let kender through anyway */
    {
        write("\nThe pathway looks very dangerous in this direction. You "
            + "wonder what possible mysteries there might be in such a "
            + "place!\n\n");
        return 0;
    }


    if ((TP->query_stat(SS_DIS)) < 95)
    {
        write("The pathway looks far too dangerous in that direction.\n");
        return 1;
    }

    else
        return 0;
}
