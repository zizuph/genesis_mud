/* rd_hr_06: High road section 6: Serpine, 4-23-95. */

inherit "/std/room";
#include "defs.h"
#include "/d/Cirath/common/mobber.h"

void
reset_room()
{
    bring_room_mob("half-giant", TYR_NPC+"hgiant.c", 1, 1);
}

void
create_room()
{
    set_short("east high road");
    set_long("Along this long stretch of road leading from the Nobles "+
             "Quarter northwest to Iron Square to the south, "+
             "there is not much to see. Those born wealthy want nothing "+
             "to do with those who earned their wealth, so a sort of "+
             "neutral zone has developed. The only remarkable features "+
             "include a wall east and the rear of a large hall that "+
             "squats to the north.\n");

    add_item(({"wall"}),"It's an ugly structure meant to keep "+
        "the wealthy and the enslaved separate.\n");
    add_item(({"hall", "large hall"}), "It appears to be some sort of "+
             "gigantic dining hall or tavern.\n");

    OUTSIDE
    ADD_SUN_ITEM;

    add_exit(TYR_MERCHANT+"ironsqr1.c", "south", "@@check_guard", 1);
    add_exit(TYR_NOBLE+"rd_hr_05.c", "northwest", "@@check_guard", 1);

    reset_room();
}

public int
check_guard()
{
    object guard = present("half-giant", TO);
  if(objectp(guard))
        TP->catch_msg(QCTNAME(guard) + " glares at you as you pass.\n");
    return 0;
}
