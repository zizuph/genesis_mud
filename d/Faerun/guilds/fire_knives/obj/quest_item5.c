/*
 * /d/Faerun/guilds/fire_knives/obj/quest_item5.c
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
destroy_item5(string str)
{
    if (str == "mantle" || str == "fur mantle" 
    || str == "trimmed mantle" || str == "fur trimmed mantle")
    {
        write("You destroy the fur trimmed mantle!\n");
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
        if (objectp(qitem = present("_quest_item5", this_player())))
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

    set_name("_quest_item5");
    add_name("mantle");
    
    set_adj("fur");
    add_adj("trimmed");
    
    set_short("fur trimmed mantle");
  
    set_long("A comfortably thick mantle, trimmed with fur "
    +"and open in the front. Its false sleeves are slit "
    +"up above in order to allow the arms of an undercoat "
    +"to pass through.\n");
    
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

    add_action(destroy_item5, "destroy");
}


string
query_recover()
{
    return 0;
}
