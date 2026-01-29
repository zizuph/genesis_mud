/*
 * The pier for the Eil Galaith shipline for Faerie
 * By Finwe, April 2005
 */
 
#include "defs.h"
#include <macros.h>
 
inherit BEACH_BASE;

void
create_beach_room()
{
    FIXEUID;
    set_short("A wide wooden pier");
    set_long(short() + ". " + s_desc_sky_outside_sky() + "It extends out " +
        "over the beach and into the water. The pier is wide and frequently " +
        "used by passengers who travel between Faerie and distant lands. " +
        "A sign hangs from a post at the end of the pier.\n" );

    add_item("sign", "It is wooden and hangs from a pole at the end of " +
        "the pier. You can probably read it.\n");
    add_cmd_item("sign", "read", "@@read_sign@@"); 


    reset_room();
    
    set_add_beach();
    set_add_forest();
    set_pier_top();


    add_exit(FOREST_DIR + "landing",  "west");

}
void
reset_room()
{
}


string read_sign()
{
    return "On the sign, painted in the common tongue, you read:\n\n" +
    "    Ship to Eil Galaith.\n" + 
    "    Fare is 40 copper coins\n" + 
    "    Youngsters travel for free\n\n";
}