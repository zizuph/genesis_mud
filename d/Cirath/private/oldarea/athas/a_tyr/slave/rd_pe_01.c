/* rd_pe_01: South end of Pandora's End. */
 
inherit "/std/room";
#include "defs.h"
 
void
create_room()
{
    set_short("pandora's End south");
    set_long("Once a major and colorful thoroughfare in the rich "
         +"sections of Tyr, the road renamed Pandora's End has "
            +"been swallowed up by the slave quarter of the city. It "
            +"now sits empty and brooding, save for abandoned "
            +"buildings and an ebony statue. An ominous corner of the "
            +"Iron Square darkens the south, while the road continues "
            +"north toward the jail of Tyr.\n");
 
    add_item(({"buildings", "building"}), "They are dark and empty. "
            +"Apparently few wished to be associated with this road.\n");
    add_item(({"statue", "ebony statue"}), "It depicts the "
            +"traitor Pandora being made chief among Kalak's Templars. "
            +"Another statue can be seen further north.\n");
 
    OUTSIDE
    ADD_SUN_ITEM
    ADD_ZIG_ITEM
 
    add_exit(TZ_SLAVE+"rd_pe_02.c", "north", 0, 1);
    add_exit(TZ_MERCHANT+"ironsqr3.c", "south", 0, 1);
}
