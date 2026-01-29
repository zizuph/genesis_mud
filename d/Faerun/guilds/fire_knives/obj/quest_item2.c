/*
 * /d/Faerun/guilds/fire_knives/obj/quest_item2.c
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
destroy_item2(string str)
{
    if (str == "handkerchief" || str == "soft handkerchief" 
    || str == "crimson handkerchief" || str == "soft crimson handkerchief")
    {
        write("You destroy the soft crimson handkerchief!\n");
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
        if (objectp(qitem = present("_quest_item2", this_player())))
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

    set_name("_quest_item2");
    add_name("handkerchief");
    
    set_adj("soft");
    add_adj("crimson");
    
    set_short("soft crimson handkerchief");
  
    set_long("A square of fabric that you can use to "
    +"blow your nose, tuck in a breast pocket, or wear "
    +"tied jaintily around your neck. Of a dark red "
    +"color and soft to the touch, this one is an "
    +"addition to any noble's attire.\n");
    
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

    add_action(destroy_item2, "destroy");
}


string
query_recover()
{
    return 0;
}
