/* slum3: A place for the dregs of the earth to rob you. */

inherit "/std/room";
#include "defs.h"
inherit "/d/Cirath/std/Cirath_magic_room_std";

void reset_room()
{
    object npc=present("dweller", TO);
    if(!objectp(npc))
    {
        npc=clone_object (TYR_NPC+"poor_mob");
        npc->move_living ("into the room", TO);
    }
}

void create_room()
{
    ::create_room();
    set_short("eastern slums");
    set_long ("This is the eastern section of Tyr's sprawling slums. "+
              "Here the ragged filth of the city gathers where it will "+
              "not be noticed. Market Road retreats to the east, while "+
              "the filth worsens in virtually every westerly direction.\n");

    OUTSIDE
    ADD_SUN_ITEM;

    add_exit(TYR_WARREN+"rd_mr_04.c", "east", 0, 1);
    add_exit(TYR_WARREN+"slum4.c", "northwest", 0, 1);
    add_exit(TYR_WARREN+"slum1.c", "west", 0, 1);
    add_exit(TYR_WARREN+"slum2.c", "southwest", 0, 1);

    reset_room();
}
