/* updated for Earthsea connections -- Amelia 6-1-98 */
#pragma strict_types
#pragma save_binary

#include "../guild.h"

inherit TRAVELLERS_STD_DIR + "room_base";

#include <stdproperties.h>

void
create_traveller_room() 
{
    set_short("Cellar");
    set_long("The cellar of the Travellers Guild is well stocked " +
	    "with wines and brandies and vintage liqueurs from all" +
	    " over the world. A thick layer of dust lies on everything.\n"); 
    
    
    add_item(({ "stair", "stairs" }), "They have been carved from the stone.\n");
    add_item(({ "wine", "wines", "brandy", "brandies", "liqueurs"}),
        "They look very old and expensive.\nYou dont think you should " +
        "touch them.\n");
    
    add_exit("stairs", "up");
}
