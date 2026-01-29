/* 
 * West alcove in the Thanarian Cathedral in Kabal
 * /d/Kalad/common/guilds/new_thanar/alcove_west
 */

#include "../local.h"

inherit THANAR_STD_ROOM; 

/*
 * Function name: create_std_thanar()
 * Description  : Constructor for the room, modify this to change room.
 */
void 
create_std_thanar()
{
    set_short("Western Alcove");
    set_long("This wide arched room stands just to the west of the "
        + "entrance to the grand cathedral of the Thanarian Order. This "
        + "state religion of Kalad holds prominence in the hearts and minds "
        + "of the human populace. This alcove is lined with paintings that "
        + "moments of truth in the history of Thanar. The walls are lined "
        + "with lanterns illuminating the area.\n");
    
    //Add the Items to the room
    add_item(({"painting", "paintings"}),
      "There are beautiful paintings that line the walls here. "+
      "There are a total of three paintings and you should be able "+
      "to look a bit closer at each one.\n");
    add_item(({"first painting", "painting one"}),
      "The painting is quite exquisite and it tells a story of "+
      "ages old. The simple brush strokes along the canvas bring "+
      "out the scene in this painting to display such truth of "+
      "history. The scene depicted is of a small male human child "+
      "being compassionate towards some lowly demi-humans.\n");
    add_item(({"second painting", "painting two"}),
      "The painting is quite exquisite and it tells a story of "+
      "ages old. The simple brush strokes along the canvas bring "+
      "out the scene in this painting to display such truth of "+
      "history. The scene depicted is of a young male human "+
      "standing at large well serving water to the lowly demi-humans.\n");
    add_item(({"third painting", "painting three"}),
      "The painting is quite exquisite and it tells a story of "+
      "ages old. The simple brush strokes along the canvas bring "+
      "out the scene in this painting to display such truth "+
      "of history. The scene depicted is of a young male human "+
      "standing in a city square preaching the compassion of Thanar and the "
      +"path that demi-humans should follow.\n");
    
    add_exit(RDIR + "centrance","east");
    
    //Adds the NPC, number of them, and then arms them.
    //add_npc(LIV +"cpriest", 2, &->arm_me());
    
    reset_room();
}

