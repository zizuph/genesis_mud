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
    set_name("scorpion");
    add_name("messenger");
    set_race_name("scorpion");
    set_gender(G_NEUTER);
    set_adj(({"large", "black"}));
    set_short("large black scorpion");
    set_long("This is a " + query_short() + ". It has been trained by the drow to deliver messages. Pale, charcoal-colored scales cover the body and its eight legs. Its two arms are extend out and in front of itself and have large pincers. The tail extends up and over the body and is crowned with a dangerous looking barb." + 
    " To send a message, simply 'send [player]'.\n");

    set_return_msg("scuttles up");
    set_home_msg("The " + query_short()+ " scuttles off and disappears.");
    set_deliver_msg("It scuttles off to deliver it.");
}
    