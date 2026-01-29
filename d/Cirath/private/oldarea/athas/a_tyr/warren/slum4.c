/* slum4: A place for the dregs of the earth to rob you. */

inherit "/std/room";
#include "defs.h"

void reset_room()
{
    object npc=present("dweller", TO);
    if(!objectp(npc))
    {
        npc=clone_object (ATH_PERSON+"poor_mob");
        npc->move_living ("into the room", TO);
    }
}

void create_room()
{
    set_short("northern slums");
    set_long ("Possibly in the best condition of any area of slum in Tyr, "+
              "if such is possible, the north benefits from "+
              "close proximity to the main square. A road lies to the "+
               "northwest, while you can venture into deep "+
              "urban blight south and southwest.\n");

    OUTSIDE
    ADD_SUN_ITEM;

    add_exit(TZ_WARREN+"rd_cw_06.c", "northwest", 0, 1);
    add_exit(TZ_WARREN +"slum3.c", "southeast", 0, 1);
    add_exit(TZ_WARREN +"slum1.c", "south", 0, 1);

    reset_room();
}
