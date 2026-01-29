/*
 * /d/Faerun/guilds/fire_knives/obj/quest_item1.c
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
destroy_item1(string str)
{
    if (str == "hand" || str == "silver hand")
    {
        write("You destroy the silver hand!\n");
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
        if (objectp(qitem = present("_quest_item1", this_player())))
		{
		    return 1;
		}
        
        return 0;
    }
    
    return 1;
}


void
create_object()
{
    set_name("_quest_item1");
    add_name("hand");
    
    set_adj("silver");
    
    set_short("silver hand");
  
    set_long("This is the silver hand prosthetic of Johan "
    +"the Silver Hand, a retired Purple Dragon Officer. It is "
    +"rumored he lost his hand fighting against Zhentarim, "
    +"though this rumor has never been confirmed or denied.\n");
    
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

    add_action(destroy_item1, "destroy");
}


string
query_recover()
{
    return 0;
}
