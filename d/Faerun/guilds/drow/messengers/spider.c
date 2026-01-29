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
    set_name("spider");
    add_name("messenger");
    set_race_name("spider");
    set_gender(G_NEUTER);
    set_adj(({"large", "black"}));
    set_short("large black spider");
    set_long("This is a large black spider, trained by drow to deliver messages. It is covered in soft, black hair and has large, bulbous end with a red mark on it. The eight legs are large and covered with black hair." + 
    " To send a message, simply 'send [player]'.\n");

    set_return_msg("scurries up");
    set_home_msg("The " + query_short()+ " scurries off and disappears.");
    set_deliver_msg("It scurries off to deliver it.");
}
    