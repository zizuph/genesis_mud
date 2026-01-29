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
    set_name("mouse");
    add_name("messenger");
    set_race_name("mouse");
    set_gender(G_NEUTER);
    set_adj(({"hairy", "gray"}));
    set_short("hairy gray mouse");
    set_long("This is a hairy gray mouse. It lives in the Underdark and has been trained to deliver messages. Its fur is gray colored and looks soft, and the face is small. The mouse looks around nervously, as if trying to find a place to hide." + 
    " To send a message, simply 'send [player]'.\n");

    set_return_msg("scurries up");
    set_home_msg("The " + query_short()+ " scurries off and disappears.");
    set_deliver_msg("It scurries off to deliver it.");
}
    