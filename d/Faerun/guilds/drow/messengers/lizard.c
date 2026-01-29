/*
 * Messenger for drow
 * Finwe, February 2008
 */

#include "/d/Faerun/defs.h"
#include "/d/Faerun/messengers/messengers.h"
#include <macros.h>
#include <stdproperties.h>
#include <wa_types.h>

inherit MESSENGERS;

void create_messenger()
{
    set_name("lizard");
    add_name("messenger");
    set_race_name("lizard");
    set_gender(G_NEUTER);
    set_adj(({"large", "scaly"}));
    set_short("large scaly lizard");
    set_long("This is a " + query_short() + ". It comes from the Underdark and was captured by the drow. The animal has been trained to deliver messages. The lizard is covered with large, gray scales. Spikes run from the base of the long, thick tail all the way to the top of the head." + 
    " To send a message, simply 'send [player]'.\n");

    set_return_msg("scuttles up");
    set_home_msg("The " + query_short()+ " scuttles off and disappears.");
    set_deliver_msg("It scuttles off to deliver it.");
}
    