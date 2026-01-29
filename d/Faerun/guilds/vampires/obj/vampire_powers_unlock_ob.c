/* /d/Faerun/guilds/vampires/obj/vampire_powers_unlock_ob.c
 * 
 * Nerull 2020
 */
 
inherit "/std/object.c";

#include "/d/Faerun/defs.h"
#include "../guild.h";
#include <ss_types.h>
#include <wa_types.h>
#include <formulas.h>
#include <composite.h>
#include <stdproperties.h>
#include <filter_funs.h>
#include <cmdparse.h>
#include <tasks.h>
#include <macros.h>




int check_stuff()
{
    string location=COFFIN_MANAGER->query_location(environment(this_object()));
        
        // If no coffin, we burrow the player
    if (!location || !strlen(location))
    {
     
        environment(this_object())->catch_tell("You no longer have a coffin, thus "
        +"you sense your power fades!\n");
        
        remove_object();
    }    
    
    return 1;
}


/*
 * Function name: create_paralyze
 * Description:   Set up paralyze
 */
void
create_object()
{
    set_name(({"_vampire_powers_unlock_ob"}));
    
    add_prop(OBJ_I_NO_DROP, 1);
    add_prop(OBJ_I_NO_SELL, 1);
    add_prop(OBJ_I_NO_STEAL, 1);
    
    
    set_no_show();
    
    //set_alarm(10.0, 10.0, &check_stuff());
}
