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
       "in the air. The floor is covered with a layer of hay. On the westside "+
       "is a large dark wooden door, and the entire north wall is made out of "+
       "a big oaken double door.\n"+
       "The corridor spreads out to the east, south, west through the door "+
       "and north through the oaken double doors.\n");

    //AN ITEM THAT THE PLAYER CAN EXAMINE AND SEARCH.
    add_item(({"wall", "walls"}),
       "They are dark grey and cut from large rough stones. Through the "+
       "cracks can be seen small  patches of green moss. The stone is "+
       "icy to the touch.\n");

    //AN ITEM THAT THE PLAYER CAN EXAMINE AND SEARCH.
    add_item(({"floor"}),
       "The floor is covered with a layer of hay. You can barely seen "+
       "the stone floor beneath.\n");

    //AN ITEM THAT THE PLAYER CAN EXAMINE AND SEARCH.
    add_item(({"ceiling"}),
       "A low ceiling made of rough dark grey stone. Tiny roots can "+
       "be seen hanging through the small cracks in the stones.\n");

    //AN ITEM THAT THE PLAYER CAN EXAMINE AND SEARCH.
    add_item(({"west door", "wooden door", "large door"}),
       "The large dark wooden door is set in the west wall. It has "+
       "a small bronze keyhole. "+
       "There is some writing and small carvings on it.\n");

    //AN ITEM THAT THE PLAYER CAN EXAMINE AND SEARCH.
    add_item(({"writing"}),
       "Enquire, listen and train. A cloud of darkness still "+
       "obscures your vision. Give more than you take, "+
       "and you shall progress.\n");
 
    //AN ITEM THAT THE PLAYER CAN EXAMINE AND SEARCH.
    add_item(({"carvings", "carving"}),
       "There is a small row of carvings below the writing. "+
       "It depicts a pack of leering black crows.\n");

    //AN ITEM THAT THE PLAYER CAN EXAMINE AND SEARCH.
    add_item(({"double door", "big door", "north door"}),
       "This is a big oaken double door, that fills the entire "+
       "northwall. It is richly ornamented, with reliefs depicting "+
       "rats, crows and rag clad men scouring around in a village, with "+
       "a large tower placed in the middle of the village.\n"+
       "A large keyhole is placed in the middle of the left door.\n");

    //AN ITEM THAT THE PLAYER CAN EXAMINE AND SEARCH.
    add_item(({"keyhole on large door", "keyhole on wooden door",
               "keyhole on west door"}),
       "It is so small, it is impossible to see anything through it. "+
       "It is shaped for an unusual looking key, it seems.\n");

    //AN ITEM THAT THE PLAYER CAN EXAMINE AND SEARCH.
    add_item(({"keyhole on big door", "keyhole on double door",
               "keyhole on north door"}),
       "It is almost impossible to see anything through it, but you "+
       "can make out some dark shapes moving about in the next room."+
       "It is a keyhole shaped for an unusual looking key, it seems.\n");


    //THE EXITS OUT OF THE ROOM.
    add_exit(GROOM + "meeting_room", "north",0);
    add_exit(GROOM + "crow_room", "west",0);
    add_exit(GROOM + "corridor2", "south", 0);
    add_exit(GROOM + "corridor4", "east", 0);
}