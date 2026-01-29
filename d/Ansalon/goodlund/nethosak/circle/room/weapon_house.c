#include "/d/Ansalon/goodlund/nethosak/circle/local.h"
#include "/d/Ansalon/common/defs.h"
#include <stdproperties.h>
#include <macros.h>

inherit GUILD_IN;

void
create_guild_room()
{    
    //THE BRIEF DESCRIPTION OF THE ROOM
    set_short("The Weapon House.");

    //STANDARD DATE AND TIME DESCR + FULL DESCR.
    set_long("A feeling of calm decends upon you as you enter the room. The room is "+
       "small and low, with the walls cut from rough dark grey stone and a "+
       "wooden plank ceiling. You can see small patches of moss between the "+
       "cracks of the stone, and rows of vines hanging down from the walls. "+
       "A floor is covered with low grass and green moss, making the ground "+
       "soft and pleasant to walk upon. A scent of dried flowers seem to hang "+
       "in the air, and everything is quiet around you. "+
       "A small wooden bench. stands next to a large rack on the west wall."+
       "To the north is a small wooden door, and through a low arch to the "+
       "east, the building continues.\n");

    //AN ITEM THAT THE PLAYER CAN EXAMINE AND SEARCH.
    add_item(({"wall", "walls"}),
       "The walls are made from large roughly cut dark grey stones. In the "+
       "cracks between the stones, small patches of moss is growing. The "+
       "stones seems slightly warm to the touch.\n");

    //AN ITEM THAT THE PLAYER CAN EXAMINE AND SEARCH.
    add_item(({"ceiling"}),
       "The ceiling hangs very low, and a tall man would have a hard time "+
       "standing upright in here. It is made of wooden planks.\n"); 

    //AN ITEM THAT THE PLAYER CAN EXAMINE AND SEARCH.
    add_item(({"floor"}),
       "The soft floor is covered completely in moss and low grass.\n"); 

    //AN ITEM THAT THE PLAYER CAN EXAMINE AND SEARCH.
    add_item(({"small door", "wooden door", "door"}),
       "This is a small wooden door set in the north wall. It is made "+
       "of dark oak, it seems. It has no markings or ornamentations on "+
       "it at all, except for a small bronze keyhole.\n");

    //AN ITEM THAT THE PLAYER CAN EXAMINE AND SEARCH.
    add_item(({"green moss", "moss"}),
       "There are moss growing both on the walls and on the floor. It "+
       "is dark green, and very soft to the touch. It has an slight "+
       "earthy smell to it.\n");

    //AN ITEM THAT THE PLAYER CAN EXAMINE AND SEARCH.
    add_item(({"small bench", "bench"}),
       "This bench is small and would fit only two persons. It is "+
       "cut from thick dark oak. You feel like sitting down and "+
       "taking a rest.\n");

    //AN ITEM THAT THE PLAYER CAN EXAMINE AND SEARCH.
    add_item(({"rack", "large rack"}),
       "It is a large wooden rack, cut from thick dark oak. It is "+
       "made to hold weapons and armours, it seems. A small sign "+
       "hangs next to it with the text.\n"+
       "'Leave the war and hostility behind.'\n"+
       "'Enter and embrace the tranquility.'\n");

    //AN ITEM THAT THE PLAYER CAN EXAMINE AND SEARCH.
    add_item(({"arch", "low arch"}),
       "It is a low stone arch leading west into the building."+
       "In rough cut letters a text reads."+ 
       "'Let down your guards and "+ 
       "open your mind to all possibilities.'\n"); 

    //THE EXITS OUT OF THE ROOM.
    add_exit(GROOM + "temple_isle","west",0);
    add_exit(GROOM + "storage1","north",0);
    add_exit(GROOM + "entrance_temple(NOT_MADE)","south",0);

}