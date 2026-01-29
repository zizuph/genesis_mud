/*
 *  Modified by Alto, 10 June 2001
 *    Added exit to Fangorn Forest
 *
 */

inherit "/d/Gondor/rohan/plains/plain.c";

#include <macros.h>

#include "/d/Gondor/defs.h"
#define ROOM_AS_DRINK_WHERE ({"stream","river","deeping stream"})

object *inv;

public int      check_ent_kill();

void
create_plain()
{
    set_geo("open");
    set_wet("damp");
    set_grass("high dark green");
    set_land("the West Emnet");
    set_where("southern");
    set_special(1);
    set_river_name("Deeping Stream");;
    set_rhard(20);
    set_rwhere("north and west");

    set_extraline("To the north, you see the dark edge of Fangorn Forest.");


   /* Now open to Fangorn Forest */

    add_exit("/d/Gondor/fangorn/fangorn30", "north", check_ent_kill, 2, 1);

    add_exit("NotOpen/l04","west",drown);
/*
    add_exit("NotOpen/m05","north",crossing);
    add_exit("NotOpen/l04","west",crossing);
*/
    add_exit("l06","east",0,5);
    add_exit("k05","south",0,5);

}



public int
check_ent_kill()
{
    inv = deep_inventory(TP);

    if (TP->query_prop("_i_killed_ent"))
    {
        write("The trees at the forest edge seem to move together to "
            + "prevent your passage.\n");
        return 1;
    }

    if (sizeof(filter(inv, &->id("torch"))))
    {
        write("The trees at the forest edge seem to move together to "
            + "prevent your passage. Perhaps they feel you might "
            + "accidentally start a forest fire.\n");
        return 1;
    }

    
    return 0;
}


