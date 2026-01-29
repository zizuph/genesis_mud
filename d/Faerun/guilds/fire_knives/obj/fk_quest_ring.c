/* /d/Faerun/guilds/fire_knives/obj/fk_quest_ring.c
*
* Quest reward wearable ring from the Fire Knives guru
* quest.
*
* Nerull 2019
*/


#include <std.h>
#include <filter_funs.h>
#include <formulas.h>
#include <language.h>
#include <macros.h>
#include <stdproperties.h>
#include <wa_types.h>
#include <files.h>

inherit "/std/object";
inherit "/lib/wearable_item"; 


void create_object() 
{
    set_name("_fk_quest_ring");
    add_name("ring");
    set_adj(({"platinum", "signet"}));
    
    set_short("platinum signet ring");
    
    set_long("This is a signet ring of one of the "
    +"noble houses of Cormyr. The ring is adorned with "
    +"tiny sapphires forming a circle where dark gray "
    +"triangular shield frames an azure dragon that blows "
    +"a golden trumpet. From your knowledge of Cormyr "
    +"Nobility this is obviously a signet ring from "
    +"the ancient House Cormaeril.\n");
    
    config_wearable_item(A_ANY_FINGER, 1, 6, this_object()); 
    
    add_prop(OBJ_M_NO_DROP, 1);
    add_prop(OBJ_M_NO_GIVE, 1);
    add_prop(OBJ_M_NO_STEAL, 1);
}


/*
 * Function name: query_auto_load
 * Description:   Makes this object autoloadable.
 * Returns:       the autoload string
 */
public string
query_auto_load()
{
    return MASTER + ":";
}


string
query_recover()
{
    return 0;
}
