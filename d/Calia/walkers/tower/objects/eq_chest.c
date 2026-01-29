/* 
 *  Chest for the droproom in the College Tower.
 */

inherit "/std/container";

#include "defs.h"
#include <stdproperties.h>
#include <macros.h>
#include <cmdparse.h>
#include <formulas.h>
#include <composite.h>


void
create_container()
{
    set_name("chest");
    set_adj("bulky");
    add_adj("wooden");
    set_short("bulky wooden chest");
    set_long("This bulky chest has lots of space for various odds" +
        " and ends that don't belong in the rack or cabinet. If you" +
        " <clean> it, you will remove from it all the items in it" +
        " that don't save and place them on the floor.\n"); 

    add_prop(CONT_I_MAX_WEIGHT, 5000000);
    add_prop(CONT_I_MAX_VOLUME, 5000000);
    add_prop(CONT_I_WEIGHT, 500000);
    add_prop(CONT_I_VOLUME, 500000);
    add_prop(CONT_I_RIGID, 1);
    add_prop(OBJ_M_NO_GET, "The bulky wooden chest can't be removed" +
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

    if (str != "chest")
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
        write("You didn't clean any non-lasting objects from the chest.\n");
    }
    else
    {        
        write("You clean " + COMPOSITE_ALL_DEAD(obs) + " from the chest.\n");
        tell_room(TO, QCTNAME(TP) + " cleans " + COMPOSITE_ALL_DEAD(obs) + 
        " from the chest.", TP);
    }

    return 1;
}


public int
prevent_enter(object ob)
{
    if (ob->query_wt())
    {
        write("The " + ob->short() + " would fit better in the rack.\n");
        return 1;
    }
    else
    if (ob->query_at())
    {
        write("The " + ob->short() + " would fit better in the cabinet.\n");
        return 1;
    }
    else
    if (ob->query_prop(OBJ_I_BROKEN))
    {
        write("You wouldn't want to put the " + ob->short() + " in there -" +
            " it's useless!\n");
        return 1;
    }

    ::prevent_enter(ob);
}