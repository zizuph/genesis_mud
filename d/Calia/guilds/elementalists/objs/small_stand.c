
/* 
 *  Small stand for the Elemental Clerics
 *  This will be used to hold spell components
 *  July 30th, 2003
 */


inherit "/std/container";

#include <stdproperties.h>
#include <macros.h>
#include <cmdparse.h>
#include <formulas.h>
#include <composite.h>

#include "defs.h"

void
create_container()
{
    set_name("stand");
    set_adj("small");
    set_short("small stand");
    set_long("The small stand is made from a beautiful mahogany and "+
        "has several drawers to hold different items. The wood is "+
        "warm and very soft to the touch. You can clean it out, "+
        "which will remove all of the components that will not save. "+
        "<clean stand>\n"); 

    add_prop(CONT_I_MAX_WEIGHT, 5000000);
    add_prop(CONT_I_MAX_VOLUME, 5000000);
    add_prop(CONT_I_WEIGHT, 500000);
    add_prop(CONT_I_VOLUME, 500000);
    add_prop(CONT_I_RIGID, 1);
    add_prop(OBJ_M_NO_GET, "The small stand cannot be taken, it is "+
        "attached to the floor.\n");
}

int
do_clean(string str)
{
    int i;
    object *obj;

    if (str != "stand")
    {
        NF("Clean what? The stand? <clean stand>\n");
        return 0;
    }
   
    obj = filter(all_inventory(),&operator(!=)(1) @ &->check_recoverable());

    for (i = 0 ; i < sizeof(obj) ; i++)
    {
        obj[i]->move(environment());
    }

    if (!sizeof(obj))
        write("There was nothing in the stand that needed to be "+
            "cleaned out.\n");
    
    else
    {        
        write("You clean " + COMPOSITE_ALL_DEAD(obj) + " out of the stand.\n");
        tell_room(TO, QCTNAME(TP) + " cleans " + COMPOSITE_ALL_DEAD(obj) + 
        " out of the stand.", TP);
    }

    return 1;
}

public int
prevent_enter(object obj)
{
    if (obj->query_prop(OBJ_I_BROKEN))
    {
        write("Why would you want to put broken things in the stand?\n");
        return 1;
    }

    if (obj->query_wt())
    {
        write("The stand is only for components, not weapons.\n");
        return 1;
    }

    else
    if (obj->query_at())
    {
        write("The stand is only for components, not armours.\n");
        return 1;
    }

    ::prevent_enter(obj);
}

void
init()
{
    add_action(do_clean, "clean");
    ::init();
}
