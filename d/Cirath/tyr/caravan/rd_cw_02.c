/* rd_cw_02: Caravan Way section 2 (nearing gate). */

inherit "/std/room";
#include "defs.h"
inherit "/d/Cirath/std/Cirath_magic_room_std";

void create_room()
{
    ::create_room();
    set_short("west caravan way");
    set_long("Now very near to the gate, Caravan Way is virtually flooded "+
             "with people both leaving and entering the city. To the "+
             "north a small bazaar has been set up, while a strange "+
             "placard hangs before the building to the south.\n");
    add_item("people", "With the gate scant yards away, it is no wonder "+
             "that members of every race and profession in Athas can be "+
             "found within this mass.\n");
    add_item(({"placard", "sign", "standard"}), "Hanging on a piece of "+
             "sturdy cloth, the image is of a stylized eyeball, ear, and "+
             "pair of lips, all impaled on a spike.\n");
 
    OUTSIDE
    ADD_SUN_ITEM;

    add_exit(TYR_CARAVAN+"spplmrch.c", "north", 0, 1);
    add_exit(TYR_CARAVAN+"rd_cw_03.c", "east", 0, 1);
    add_exit(TYR_CARAVAN+"dragoman.c", "south", 0, 1);
    add_exit(TYR_CARAVAN+"rd_cw_01.c", "west", 0, 1);
}
