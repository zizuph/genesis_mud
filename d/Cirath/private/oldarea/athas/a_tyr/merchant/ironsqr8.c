/* ironsqr8: Southeast section of Iron Square. */

inherit "/std/room";
#include "defs.h"

void
create_room()
{
    set_short("southeast of iron square");
    set_long("Replacing the usual somber feel of the rest of Iron Square, "+
             "which heads north and west, is a more vibrant atmosphere. "+
             "Located just a bit northwest of the wild Elven Market, this "+
             "corner also boasts the entrances to the public training "+
             "hall of Tyr to the south and a relatively small trading "+
             "house to the northwest. The emblem of the house hangs from "+
             "a banner near the top of the building.\n");

    add_item (({"emblem", "building", "top", "banner"}), "The emblem is "+
             "that of House Inika, a gold circle on a black field.\n");

    OUTSIDE
    ADD_SUN_ITEM
    ADD_ZIG_ITEM

    add_exit(TZ_MERCHANT+"ironsqr5.c", "north", 0, 1);
    add_exit(TZ_MARKET+"rd_mr_05.c", "southeast", 0, 1);
    add_exit(TZ_MERCHANT+"trainhll.c", "south", 0, 1);
    add_exit(TZ_MERCHANT+"ironsqr7.c", "west", 0, 1);
    add_exit(TZ_MERCHANT+"housinik.c", "northwest", "@@house_block", 1);
}
