/*
 *  /d/Faerun/guilds/warlocks/obj/cabinet.c
 *
 *  Old cabinet from Necromancers (layman). Still stylish.
 *
 */ 
 
#pragma strict_types

inherit "/std/receptacle.c";

#include "../guild.h"
#include "/d/Faerun/defs.h"
#include <ss_types.h>
#include <stdproperties.h>
#include <wa_types.h>


void
create_receptacle()
{
    setuid();
    seteuid(getuid());
    
    set_short("black wooden cabinet");
    set_name("cabinet");
    set_adj("black");
    add_adj("wooden");
    set_long("This is a " + query_short() 
    + " It is tall and stores drinks. " +
    "The cabinet is made from black wood.\n");
    
    add_item(({"door", "doors"}),
     "The " + query_short() + " has two doors attached to it.\n");  
    //set_no_show_composite(1);

    add_prop(OBJ_M_NO_GET, "The " + query_short() 
    + " is fixed to the floor, you cannot take it.\n");
    add_prop(CONT_I_MAX_VOLUME, 50000);
    add_prop(CONT_I_MAX_WEIGHT, 75000);
    add_prop(CONT_I_VOLUME,  4500);
    add_prop(CONT_I_WEIGHT,  5000);
    add_prop(CONT_I_RIGID,      1);
    add_prop(CONT_I_TRANSP,     0);
    add_prop(CONT_I_CLOSED, 1);
}


/* Function name: prevent_enter
 * Description  : Checks if it is a drink
 * Arguments    : object obj - the object entering
 * Returns      : 1 if not a coin, 0 if it is
 */
public int
prevent_enter(object obj)
{

    if (!IS_DRINK_OBJECT(obj))
    {
        write("You can only put drinks in the " + query_name() + ".\n");
        return 1;
    }

    return 0;
}
