/* ironsqr1: Northwest corner of Iron Square. */

inherit "/std/room";
#include "defs.h"
#include "/d/Cirath/std/block.h"

void
create_room()
{
    set_short("northwest of iron square");
    set_long("The buildings are larger here, and in far better shape then "+
             "in other sections of the city. Of course, the mighty "+
             "Trading Houses of Tyr that call Iron Square home would "+
             "have it no other way. Unsavory characters eye you from the "+
             "windows of every building, particularly those to the south "+
             "where the square approaches the cistern, and to the east. "+
             "The High Road is past an archway to the north, while "+
             "Caravan Way begins to the west.\n"); 

    add_item(({"characters", "character", "building", "buildings"}),
             "Working for the trading houses, they watch newcomers for "+
             "hot cargos or potential rivalries.\n");
    add_item("cistern", "From here you can just make out the gigantic "+
        "main well that provides Tyr with life-giving water.\n");

    OUTSIDE
    ADD_SUN_ITEM
    ADD_ZIG_ITEM

    add_exit(TYR_NOBLE+"rd_hr_06.c", "north", 0, 1);
    add_exit(TYR_MERCHANT+"ironsqr2.c", "east", 0, 1);
    add_exit(TYR_MERCHANT+"ironsqr4.c", "south", "@@block_exit@@", 1);
    add_exit(TYR_CARAVAN+"rd_cw_07.c", "west", 0, 1);
}
