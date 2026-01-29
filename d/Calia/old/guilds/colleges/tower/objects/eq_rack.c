/* 
 *  Rack for the droproom in the College Tower.
 */

inherit "/std/container";

#include "defs.h"
#include <stdproperties.h>
#include <macros.h>
#include <cmdparse.h>
#include <formulas.h>
#include <composite.h>

public int clean_inventory(string str);


void
create_container()
{
    set_name("rack");
    set_adj("solid");
    add_adj("steel");
    set_short("solid steel rack");
    set_long("This rack has various fixtures for holding different" +
        " types of weapons. You could <clean> it, thereby sorting out" +
        " the weapons that will not last from it, putting them on the" +
        " floor.\n");  

    add_prop(CONT_I_MAX_WEIGHT, 5000000);
    add_prop(CONT_I_MAX_VOLUME, 5000000);
    add_prop(CONT_I_WEIGHT, 500000);
    add_prop(CONT_I_VOLUME, 500000);
    add_prop(CONT_I_RIGID, 1);
    add_prop(OBJ_M_NO_GET, "The solid steel rack can't be removed" +
        " from the floor.\n");
}

void
init()
{
    add_action("clean_inventory", "clean");
    ::init();
}

int
clean_inventory(string str)
{
    int i;
    object *obs;

    if (str != "rack")
    {
        notify_fail("Clean what?\n");
        return 0;
    }
   
    obs = filter(all_inventory() , &operator(!=)(1) @ &->check_recoverable());

    for (i = 0 ; i < sizeof(obs) ; i++)
    {
        obs[i]->move(environment());
    }

    if (!sizeof(obs))
    {
        write("You didn't clean any non-lasting objects from the rack.\n");
    }
    else
    {        
        write("You clean " + COMPOSITE_ALL_DEAD(obs) + " from the rack.\n");
        tell_room(TO, QCTNAME(TP) + " cleans " + COMPOSITE_ALL_DEAD(obs) + 
        " from the rack.", TP);
    }

    return 1;
}


public int
prevent_enter(object ob)
{
    if (!(ob->query_wt()))
    {
        write("The " + ob->short() + " will not fit in the rack.\n");
        return 1;
    }
    if (ob->query_prop(OBJ_I_BROKEN))
    {
        write("You wouldn't want to put the " + ob->short() + " in there -" +
            " it's useless!\n");
        return 1;
    }

    ::prevent_enter(ob);
}
