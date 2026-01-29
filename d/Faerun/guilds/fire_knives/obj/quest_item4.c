/*
 * /d/Faerun/guilds/fire_knives/obj/quest_item4.c
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
destroy_item4(string str)
{
    if (str == "hat" || str == "brimmed hat" 
    || str == "broad hat" || str == "broad brimmed hat")
    {
        write("You destroy the broad brimmed hat!\n");
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
        if (objectp(qitem = present("_quest_item4", this_player())))
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

    set_name("_quest_item4");
    add_name("hat");
    
    set_adj("broad");
    add_adj("brimmed");
    
    set_short("broad brimmed hat");
  
    set_long("A broad brimmed hat made of velvet and "
    +"lined with feathers which although seemingly "
    +"uncomfortable serves as a symbol of status and wealth.\n");
    
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

    add_action(destroy_item4, "destroy");
}


string
query_recover()
{
    return 0;
}
