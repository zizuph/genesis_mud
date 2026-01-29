inherit "/std/room";

#include "/d/Emerald/defs.h"

object santos;

void
reset_room()
{
    if(!santos)
    {
        santos=clone_object(VILLAGE_DIR+"npc/santos");
        santos->move_living(" stands up from his gardening.", this_object());
    }
    return;
}

void create_room()

{
    set_short("In a garden");
    set_long("   The beauty of the garden is not lost as you continue "+
             "on through a dancing field of daisies.  It seems the gardener "+
             "here has carefully laid out each bed and tends them with care. "+
             "The smell of daisies and roses is very strong here. Unfortnatly "+
             "there are no roses in this part of the garden.\n\n");

    add_item(({"daisies", "daisy"}),"A lovely yellow flower.\n");

    add_exit(VILLAGE_DIR + "g2", "south", 0);
    add_exit(VILLAGE_DIR + "g4", "east", 0);

    reset_room();
}
