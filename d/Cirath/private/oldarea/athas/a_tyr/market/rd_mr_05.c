/* rd_mr_05: Market road section 5. */
 
inherit "/std/room";
#include "defs.h"
 
void create_room()
{
    set_short("northeast end of Market Road");
    set_long ("This short stretch of road has an odd feel to it, as if "
             +"torn between opposing forces. Northwest are the grim "
             +"trading houses of Iron Square, home to the largest "
             +"and most powerful merchant groups in the Tyr region. Just "
             +"to the east however, spreads the disorganised mass that is "
             +"is the Tyrian Market district. You are assaulted by the "
             +"yells of street vendors and shoppers alike from the "
             +"Market, while only silence spreads from Square.\n");
 
    OUTSIDE
    ADD_SUN_ITEM;
 
    add_exit(TZ_MERCHANT+"ironsqr8.c", "northwest", 0, 1);
    add_exit(TZ_MARKET+"shdwsqrn.c", "east", 0, 1);
    add_exit(TZ_WARREN+"rd_mr_04.c", "southwest", 0, 1);
}
