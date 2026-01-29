/*
    /d/Gondor/common/distrib/distrib.c

    Coded by Gwyneth on April 20, 2000

    Individual distributor to be cloned into each Gondorian
    entry room by dmaster. Will mask init() to clone a
    single object into each player's inventory upon entry
    with a standard message sent to the player. Will set a
    prop after cloning the object in order to only give each
    player one item.
*/

inherit "/std/object";

#include "/d/Gondor/defs.h"
#include "distrib.h"
#include <filter_funs.h>
#include <macros.h>
#include <stdproperties.h>

void distribute_item();

void
create_object()
{
    set_name("distributor");
    set_pname("distributors");
    set_adj("mechanical");
    set_short("mechanical distributor");
    set_pshort("mechanical distributors");
    set_long("This is a Gondorian distributor. It clones objects " +
        "in Gondorian entry rooms.\n");

    set_no_show();

    add_prop(OBJ_I_NO_GET, 1);
    add_prop(OBJ_I_NO_GIVE, 1);
    add_prop(OBJ_I_NO_DROP, 1);
    add_prop(OBJ_I_NO_STEAL, 1);
    add_prop(OBJ_I_NO_SELL, 1);
    add_prop(OBJ_I_NO_BUY, 1);
    add_prop(OBJ_S_WIZINFO, "This is a Gondorian distributor. It " +
        "clones objects in Gondorian entry rooms, one per person.\n");
    environment(TO)->add_prop(ROOM_I_NO_CLEANUP, 1);
}

public void
init()
{
    ::init();

    distribute_item();
}

void
distribute_item()
{
    object *oblist;
    int i;

    if(interactive(TP) &&
       TP->query_prop(PLAYER_I_DISTRIB))
    {
        clone_object(DOBJ)->move(TP);
        TP->catch_tell(MESSAGE);
        TP->add_prop(PLAYER_I_DISTRIB, 1);
    }
/*
    oblist = FILTER_PLAYERS(all_inventory(environment(TO)));

    for(i = 0; i < sizeof(oblist); i++)
    {
        if(!oblist[i]->query_prop(PLAYER_I_DISTRIB))
        {
            clone_object(DOBJ)->move(oblist[i]);
            oblist[i]->catch_tell(MESSAGE);
            oblist[i]->add_prop(PLAYER_I_DISTRIB, 1);
        }
    }
*/
    return;
}

