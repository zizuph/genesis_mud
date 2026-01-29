#include "/d/Ansalon/goodlund/nethosak/circle/local.h"
#include "/d/Ansalon/common/defs.h"
#include <stdproperties.h>
#include <macros.h>

inherit GUILD_IN;

void
create_guild_room()
{    
    //THE BRIEF DESCRIPTION OF THE ROOM
    set_short("A corridor.");

    //STANDARD DATE AND TIME DESCR + FULL DESCR.
    set_long("A narrow, low corridor, barely illuminated by a few torches hanging "+
       "from the walls. The walls are made of dark grey stone, and seem "+
       "roughly cut. It is deadly silent here, while a dry heat hangs heavily "+
       "in the air. The floor is covered with a layer of hay. On the eastside "+
       "is a large wooden door. The corridor leads further north, south and east "+
       "through the door.\n");

    //AN ITEM THAT THE PLAYER CAN EXAMINE AND SEARCH.
    add_item(({"wall", "walls"}),
       "They are dark grey and cut from large rough stones. Through the "+
       "cracks can be seen small patches of green moss. The stone is icy to "+
       "the touch.\n");

    //AN ITEM THAT THE PLAYER CAN EXAMINE AND SEARCH.
    add_item(({"floor"}),
       "The floor is covered with a layer of hay. You can barely seen the "+
       "stone floor beneath.\n");

    //AN ITEM THAT THE PLAYER CAN EXAMINE AND SEARCH.
    add_item(({"ceiling"}),
       "A low ceiling made of rough dark grey stone. Tiny roots can be seen "+
       "hanging through the small cracks in the stones.\n");

    //AN ITEM THAT THE PLAYER CAN EXAMINE AND SEARCH.
    add_item(({"door", "wooden door"}),
       "The large wooden door is set in the east wall. It has a small "+
       "bronze keyhole. There is some writing and small carvings on it.\n");

    //AN ITEM THAT THE PLAYER CAN EXAMINE AND SEARCH.
    add_item(({"writing"}),
       "Watch, learn and explore. An untold number of "+
       "trials and rewards are ahead of you.\n");

    //AN ITEM THAT THE PLAYER CAN EXAMINE AND SEARCH.
    add_item(({"carvings", "carving"}),
       "There is a small row of carvings below the writing. It depicts "+
       "a small pack of grinning black rats.\n");

    //AN ITEM THAT THE PLAYER CAN EXAMINE AND SEARCH.
    add_item(({"keyhole"}),
       "It is so small, it is impossible to see anything through it. "+
       "It is shaped for an unusual looking key, it seems.\n");


    //THE EXITS OUT OF THE ROOM.
    add_exit(GROOM + "corridor3","north",0);
    add_exit(GROOM + "corridor1","south",0);
    add_exit(GROOM + "rat_room","east",0);
}