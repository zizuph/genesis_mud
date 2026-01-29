/*
 * /d/Faerun/guilds/fire_knives/obj/quest_item3.c
 *
 * Quest object.
 *
 * Coded by Nerull, 2019
 *
 */

#include "../guild.h";
#include <macros.h>
#include <ss_types.h>
#include <wa_types.h>
#include <filter_funs.h>

inherit "std/object";


int
destroy_item3(string str)
{
    if (str == "belt" || str == "golden belt" 
    || str == "massive belt" || str == "massive golden belt")
    {
        write("You destroy the massive golden belt!\n");
        set_alarm(1.0, 0.0, &remove_object());
    
        return 1;
    }
    
    return 0;
}


int check_pickup()
{
    object qitem;

    if (this_player()->query_prop(FIREKNIVES_ON_GURUQUEST) == 1)
    {
        if (objectp(qitem = present("_quest_item3", this_player())))
		{
		    return 1;
		}
        
        return 0;
    }
    
    return 1;
}



/*
 * Function name: create_object()
 * Description  : Sets up our monster.
 */
nomask void create_object()
{
    seteuid(getuid());

    set_name("_quest_item3");
    add_name("belt");
    
    set_adj("massive");
    add_adj("golden");
    
    set_short("massive golden belt");
  
    set_long("An ostentatiously thick and wide belt made "
    +"of pure gold made to be worn decoratively around the "
    +"waist over a coat or mantle in order to symbolize status.\n");
    
    add_prop(CONT_I_WEIGHT, 3400);
    add_prop(CONT_I_HEIGHT, 25);
    add_prop(OBJ_I_VOLUME, 1000);
    add_prop(OBJ_I_NO_STEAL, 1);
    add_prop(OBJ_I_NO_SELL, 1);
    add_prop(OBJ_M_NO_GET, check_pickup);
}


/*
 * Function name: init_living()
 * Description  : Enables commands for the player when encountering
 *                this npc.
 */
void init()
{
    ::init();

    add_action(destroy_item3, "destroy");
}


string
query_recover()
{
    return 0;
}
