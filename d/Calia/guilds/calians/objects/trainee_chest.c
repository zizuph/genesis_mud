
/* 
 *  Small chest for the Calian Trainees to put
 *  things in so they aren't messing up the
 *  floor. Jaacar - April 2017
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
    set_name("chest");
    set_adj("small");
    set_short("small chest");
    set_long("The small chest is made from a beautiful mahogany and "+
        "appears that it could hold a few items. The wood is "+
        "warm and very soft to the touch. You can clean it out, "+
        "which will remove all of the items that will not save. "+
        "<clean chest>\n"); 

    add_prop(CONT_I_MAX_WEIGHT, 5000000);
    add_prop(CONT_I_MAX_VOLUME, 5000000);
    add_prop(CONT_I_WEIGHT, 500000);
    add_prop(CONT_I_VOLUME, 500000);
    add_prop(CONT_I_RIGID, 1);
    add_prop(OBJ_M_NO_GET, "The small chest cannot be taken, it is "+
        "attached to the floor.\n");
}

int
do_clean(string str)
{
    int i;
    object *obj;

    if (str != "chest")
    {
        NF("Clean what? The chest? <clean chest>\n");
        return 0;
    }
   
    obj = filter(all_inventory(),&operator(!=)(1) @ &->check_recoverable());

    for (i = 0 ; i < sizeof(obj) ; i++)
    {
        obj[i]->move(environment());
    }

    if (!sizeof(obj))
        write("There was nothing in the chest that needed to be "+
            "cleaned out.\n");
    
    else
    {        
        write("You clean " + COMPOSITE_ALL_DEAD(obj) + " out of the chest.\n");
        tell_room(TO, QCTNAME(TP) + " cleans " + COMPOSITE_ALL_DEAD(obj) + 
        " out of the chest.", TP);
    }

    return 1;
}

public int
prevent_enter(object obj)
{
    if (obj->query_prop(OBJ_I_BROKEN))
    {
        write("Why would you want to put broken things in the chest?\n");
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
