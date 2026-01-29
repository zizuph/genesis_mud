/* slum2: A place for the dregs of the earth to rob you. */

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
    set_short("southern slums");
    set_long ("Though not by much, the level of civilization in this "+
              "spot does far exceed that of the deep slums directly to "+
              "the north. It would be much safer to head northeast towards "+
              "the eastern slums or better still, west to Sul Street.\n");

    OUTSIDE
    ADD_SUN_ITEM;

    add_exit(TZ_WARREN+"rd_vr_01.c", "west", 0, 1);
    add_exit(TZ_WARREN+"slum1.c", "north", 0, 1);
    add_exit(TZ_WARREN+"slum3.c", "northeast", 0, 1);

    reset_room();
}
