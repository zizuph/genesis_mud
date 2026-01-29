/*
 *  IGARD_DEEP_ARMOURY + "store_room.c"
 *
 *  A store room for the Isengard Armoury shop.
 *
 *  Last modified by Alto, 27 November 2001
 *
 */

#pragma strict_types

inherit "/std/room.c";

#include <macros.h>
#include <stdproperties.h>
#include "/d/Gondor/defs.h"
#include "../../igard_defs.h"

public string      long_func();
public int         remove_sold_item(object ob);

public void
create_room()
{
    set_short("A small storage room");
    set_long(long_func);

    add_item(({"storage room", "room", "surroundings"}), long_func);

    add_prop(ROOM_I_INSIDE, 1);

    reset_room();
}


public string
long_func()
{
    string  longtxt;

    longtxt = 
        "Not much to see here. This room does not appear to have "
        + "had any visitors recently.\n"; 

    return longtxt;
}


public int
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if(living(ob))
        {
        return 1;
        }
    set_alarm(2.0, 0.0, &remove_sold_item(ob));
    return 1;
}


public int
remove_sold_item(object ob)
{
    ob->remove_object();
    return 1;
}




