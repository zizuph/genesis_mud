#pragma save_binary

inherit "/d/Genesis/ship/deck";

#include <stdproperties.h>
#include "/d/Shire/common/defs.h"

void
create_deck()
{
    set_short("Aboard an elegant elven ship");
    set_long("This elegant elven ship is so well-crafted it "+
    "seems to move even when it is in port. Made of the finest "+
    "timbers and woven silks, it is even more valuable for the "+
    "shining elven gems littering the outside of the ship.  A small "+
    "stairway leads down underneath the ship for refuge from the "+
    "elements.\n");

   add_item(({"gem","gems","shining elven gems","shining gems","elven gems"}),
    "The shining elven gems cover the tops of the masts all the way down to "+
    "around six feet from the deck. They also cover all the woodwork, but "+
    "also, strangely stop almost head-high from the deck. The ones that remain "+
    "seem to shine with Original light.\n");

    add_item(({"timbers","timber","wood","mast","masts","deck"}),
    "All the ship that isn't made of gem or jewel or cloth is made of wood. "+
    "The wood seems to be new, probably crafted from the forest surrounding "+
    "Grey Havens.  Even the masts and decks are single pieces of this wood.\n");

    add_item("stairway","It leads down to the cabin below.\n");

    add_item(({"silk","silks","cloth"}),
    "The silks, carefully woven by fair elf-maidens is so sheer it is translucent, "+
    "but so strong that the most powerful wind does not tear through it.\n");


     add_exit("/d/Shire/common/ship/ship3/cabin", "down", 0);

    add_prop(ROOM_I_HIDE, 50);
}