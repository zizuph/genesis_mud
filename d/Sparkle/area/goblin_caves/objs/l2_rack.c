/*
 * Rack in rack rooms
 * Boreaulam, September 2012
 */
#pragma save_binary
#pragma strict_types

inherit "/std/container";

#include <stdproperties.h>
#include "defs.h"

static string *items = ({ EQUIP_DIR + "lsword", EQUIP_DIR + "leather_armour" });

void
reset_container()
{
    int clones = 5 - sizeof(all_inventory());

    while (clones-- > 0) {
        object obj = clone_object(one_of_list(items));
        obj->move(this_object(), 1);
    }
}

void
create_container()
{
    setuid();
    seteuid(getuid());

    set_name("rack");
    set_adj("large");
    set_short("large rack");
    set_long("This is a rather large rack where goblins keep their weapons and armours.\n");

    add_prop(CONT_I_MAX_WEIGHT,200000); /* lots of stuff */
    add_prop(CONT_I_MAX_VOLUME,200000);
    add_prop(CONT_I_WEIGHT,100000);
    add_prop(CONT_I_VOLUME,50000);

    add_prop(CONT_I_RIGID,1);

    add_prop(CONT_I_TRANSP,1);
    add_prop(OBJ_I_NO_GET,"The large rack is securely fastened to the ground.\n");

    reset_container();
}

/*
* Function name: prevent_leave
* Description:   Called when an object is trying to leave this container
*                to see if we allow it to leave.
* Arguments:     object ob - the object trying to leave
* Returns:       1 - The object is not allowed to leave
*                0 - The object is allowed to leave
*/
public int
prevent_leave(object ob)
{
    object room = environment();

    if (present("_rack_guard", room)) 
    { 
        write("The guard blocks you from taking " + LANG_THESHORT(ob) + ".\n"); 
        return 1;  
    } 

    return 0;
}



