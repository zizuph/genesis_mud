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
    set_name("bat");
    add_name("messenger");
    set_race_name("bat");
    set_gender(G_NEUTER);
    set_adj(({"large", "black"}));
    set_short("large black bat");
    set_long("This is a large black bat, trained by drow to deliver messages. It is covered in soft, black hair and has large, leathery wings. The mouse-like face is a chocolate brown and it has small, round ears." + 
    " To send a message, simply 'send [player]'.\n");

    set_return_msg("flits up");
    set_home_msg("The " + query_short()+ " flits off and disappears.");
    set_deliver_msg("It flits off to deliver it.");
}
    