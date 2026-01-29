#include "/d/Ansalon/goodlund/nethosak/circle/local.h"
#include "/d/Ansalon/common/defs.h"
#include <stdproperties.h>
#include <macros.h>

inherit GUILD_IN;

void
create_guild_room()
{
    //THE BRIEF DESCRIPTION OF THE ROOM
    set_short("The Nest"); 

    //STANDARD DATE AND TIME DESCR + FULL DESCR.
    set_long("This large circular room is barely illuminated by the few "+
       "torches that is lit, which makes it difficult to clearly "+
       "define the walls and ceiling. You can see what looks like "+ 
       "black slimy roots covering the walls all around. The "+
       "roots have grown to make many man-sized alcoves around "+
       "the room, where members can sleep. "+
       "The floor is covered with a two inches of stale murky "+
       "water, which seems to be supplied by the dripping of water "+
       "from the roots in the ceiling. "+
       "A stench of rotting plants hangs heavily in the air. "+
       "At the southeast end of the room, is a small spiral "+
       "staircase leading up, cut from rough grey stone. At the "+
       "west end is also located a small wooden door amongst all "+
       "the dark roots. You may start your days here, by taking up "+
       "one of the free alcoves.\n");

    //AN ITEM THAT THE PLAYER CAN EXAMINE AND SEARCH.
    add_item(({"walls", "wall", "roots", "root"}),
        "The walls of this room is made up of thick black roots oozing "+
        "with a sticky slimy substance. They feel slightly warm and "+
        "pulsating to the touch. There are so many roots intertwined, "+
        "that you cannot see where they originate.\n");

    //AN ITEM THAT THE PLAYER CAN EXAMINE AND SEARCH.
    add_item(({"floor", "water"}),
        "The water is dark and murky making it impossible to see "+
        "the floor. You can feel underneath the water, what seems "+
        "like a rough stone floor. The water is tasteless but "+
        "has a strong odor of rot to it.\n");

    //AN ITEM THAT THE PLAYER CAN EXAMINE AND SEARCH.
    add_item(({"door", "wooden door", "west door"}),
        "A small wooden door with ornamentation at all. It has "+
        "no key hole and no handle. You think you can hear a "+
        "slight humming sound from beyond the door. \n");

    //AN ITEM THAT THE PLAYER CAN EXAMINE AND SEARCH.
    add_item(({"alcoves", "alcove"}),
        "A small wooden door with ornamentation at all. It has "+
        "no key hole and no handle. You think you can hear a "+
        "slight humming sound from beyond the door. \n");

    //AN ITEM THAT THE PLAYER CAN EXAMINE AND SEARCH.
    add_item(({"door", "wooden door", "west door"}),
        "A small wooden door with ornamentation at all. It has "+
        "no key hole and no handle. You think you can hear a "+
        "slight humming sound from beyond the door. \n");

    //AN ITEM THAT THE PLAYER CAN EXAMINE AND SEARCH.
    add_item(({"alcoves", "alcove"}),
        "There are numerous of these alcoves all around the room. "+
        "Some high, some low. They seem to have been naturally "+
        "grown by the roots, to form a little room high and wide "+
        "enough for a large man to lay down inside. This is where "+
        "the members come to sleep.\n");

    //AN ITEM THAT THE PLAYER CAN EXAMINE AND SEARCH.
    add_item(({"ceiling"}),
        "It is hard to see how high the ceiling exactly is, but "+
        "you can see thick dark roots hanging down from above. "+
        "A watery substance drips from them constantly.\n");

    //AN ITEM THAT THE PLAYER CAN EXAMINE AND SEARCH.
    add_item(({"northeast wall", "northeastern wall"}),
        "You move up to the northeast wall and discover a very "+
        "narrow passage at near the bottom of your feat. The "+
        "passage is pitch black and leads northward. You think "+
        "your body might fit the hole, but it will be difficult.\n");

    //THE EXITS OUT OF THE ROOM.
    add_exit(GROOM + "main_library","up",0);
    add_exit(GROOM + "b_basement","west",0);
}

