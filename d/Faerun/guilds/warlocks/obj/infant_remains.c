/*
 * /d/Faerun/guilds/warlocks/obj/intant_remains.c
 *
 * Infant remains, quest object
 *
 * Coded by Nerull, 2018
 *
 */

#include "../guild.h";
#include <macros.h>
#include <ss_types.h>
#include <wa_types.h>
#include <filter_funs.h>

inherit "std/object";


int
destroy_remains()
{
    write("You destroy the bundle of sad skeletal "
    +"remains of an infant girl!\n");
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

    set_name("remains");
    add_name("_quest_infant_remains");
    add_name("bundle");
    add_name("skeleton");
    add_name("samara");
    add_name("infant remains");
    add_name("infant girl");
    add_name("sad remains");
    add_name("skeletal remains");
    add_name("sad skeletal remains");

    set_short("bundle of sad skeletal remains of an infant girl");
    set_pshort("bundles of sad skeletal remains of an infant girl");
    set_long("This macabre sight is almost too much to bear. Still "
    +"wearing a tiny blue mud-soaked dress, this girl "
    +"met a brutal end judging by the cuts, carvings and "
    +"humanoid bitemarks into the few bits of remaining bleeding flesh. "
    +"Toes and fingers are completely missing. You "
    +"suspect some sort of child sacrifice or maybe cannibalism. Since the "
    +"infant died recently, the perpetrator can't be very far away. Who "
    +"would do such a thing?! You should probably give the remains back to "
    +"the desperate mother. You may <destroy remains> if you wish "
    +"to rid yourself of them.\n");

    add_prop(CONT_I_WEIGHT, 200);
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

    add_action(destroy_remains, "destroy");
}


string
query_recover()
{
    return 0;
}
