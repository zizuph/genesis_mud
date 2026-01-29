/* 
 *  Cabinet for the droproom in the College Tower.
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
    set_name("cabinet");
    set_adj("large");
    add_adj("stone");
    set_short("large stone cabinet");
    set_long("This cabinet has plenty of room for storing clothes," +
       " footwear, even armours. If you <clean> it, you sort out the" +
       " items that will not last from it, placing them on the floor.\n"); 

    add_prop(CONT_I_MAX_WEIGHT, 5000000);
    add_prop(CONT_I_MAX_VOLUME, 5000000);
    add_prop(CONT_I_WEIGHT, 500000);
    add_prop(CONT_I_VOLUME, 500000);
    add_prop(CONT_I_RIGID, 1);
    add_prop(OBJ_M_NO_GET, "The large stone cabinet can't be removed" +
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

    if (str != "cabinet")
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
        write("You didn't clean any non-lasting objects from the cabinet.\n");
    }
    else
    {        
        write("You clean " + COMPOSITE_ALL_DEAD(obs) + " from the cabinet.\n");
        tell_room(TO, QCTNAME(TP) + " cleans " + COMPOSITE_ALL_DEAD(obs) + 
        " from the cabinet.", TP);
    }

    return 1;
}


public int
prevent_enter(object ob)
{
    if (!(ob->query_at()))
    {
        write("The " + ob->short() + " will not fit in the cabinet.\n");
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