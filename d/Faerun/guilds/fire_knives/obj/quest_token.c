/*
 * /d/Faerun/guilds/fire_knives/obj/quest_token.c
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
destroy_token()
{
    write("You destroy the platinum signet ring!\n");
    set_alarm(1.0, 0.0, &remove_object());
    
    return 1;
}


/*
 * Function name: create_object()
 * Description  : Sets up our monster.
 */
nomask void create_object()
{
    seteuid(getuid());

    set_name("_quest_token");
    add_name("ring");
    
    set_adj("platinum");
    
    set_short("platinum signet ring");
  
    set_long("This is a signet ring of one of the noble houses of "
    +"Cormyr. The ring is adorned with tiny sapphires forming a circle "
    +"where dark gray triangular shield frames an azure dragon that blows "
    +"a golden trumpet. From your knowledge of Cormyr Nobility this is "
    +"obviously a signet ring from the ancient House Cormaeril.\n");
    
    add_prop(CONT_I_WEIGHT, 3400);
    add_prop(CONT_I_HEIGHT, 25);
    add_prop(OBJ_I_NO_DROP, 1);
    add_prop(OBJ_I_NO_STEAL, 1);
    add_prop(OBJ_I_NO_SELL, 1);
}


/*
 * Function name: init_living()
 * Description  : Enables commands for the player when encountering
 *                this npc.
 */
void init()
{
    ::init();

    add_action(destroy_token, "destroy");
}


string
query_recover()
{
    return 0;
}
