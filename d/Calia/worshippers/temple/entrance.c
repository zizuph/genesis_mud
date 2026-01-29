

#pragma save_binary

inherit "/std/room";

#include <stdproperties.h>
#include <macros.h>
#include "defs.h"
#include WORSHIP_HEADER
#include COUNCIL_HEADER


void
create_room()
{
    set_short("Entrance to a natural temple");
    set_long("You are standing in the entranceway to a natural "+
        "temple. There is grass on the ground here cut very "+
        "short. To the north you see the archway leading back "+
        "out into the open air. The walls rise up here almost "+
        "twenty feet high, and there is a roof made of grass and "+
        "straw. Two stone statues have been placed at the archway "+
        "to the north, as if put there to guard the temple. "+
        "There are two small chambers to the east and "+
        "west, and a very large chamber to the south.\n");

    add_item(({"statue","statues","stone statue","stone statues"}),
        "These two statues seem so life-like it is unbelievable. "+
        "They appear to made of granite, and stand a full two "+
        "heads taller than a normal human. They are mostly "+
        "humanoid shaped, each bearing a symbol carved upon their "+
        "chests. The eyes are perfectly cut diamonds that "+
        "seem to watch your every move.\n");

    add_item(({"symbol","symbols"}),"The symbols are the same on "+
        "each of the statues chests. It is a large circle, split "+
        "into four even sections. Each section contains a different "+
        "symbol, one for each of the four elements. In the upper left "+
        "is the symbol of fire, the upper right, the symbol for air, "+
        "while in the lower left is the symbol for earth, and the lower "+
        "right, the symbol for water.\n");

    add_item("walls","The walls are made of carefully cut "+
        "stones that are placed together.\n");

    add_item("stones","The stones are carefully cut, and placed "+
        "with great precision, held together almost magically.\n");

    add_item(({"roof","straw"}),"The roof is made "+
        "from green and brown grass and straw, giving this "+
        "place a natural camouflage from above.\n");

    add_item(({"grass","floor","ground"}),"The grass on the "+
        "ground is a beautiful green colour, each blade is "+
        "exactly the same shape and size as all of the others.\n");

    add_item(({"chamber","chambers"}),"Which chamber do you "+
        "mean? The small chamber or the large chamber?\n");

    add_item("large chamber","It is difficult to make out "+
        "many details from here, but you can see several rocks "+
        "carved in the shape of seats, and a small silver altar "+
        "in the large chamber.\n");

    add_item(({"small chamber","small chambers"}),"The small "+
        "chambers are very hard to see through the doorways. "+
        "You will have to explore them for yourself.\n");

    add_item("archway","The archway forms a perfectly shaped "+
        "half circle standing almost eight feet high, and ten feet "+
        "wide at the bottom. It is formed from bushes and "+
        "small flowers. Beyond it, you see some rocks far to "+
        "the north.\n");

    add_item(({"small flowers","flowers"}),"These flowers are "+
        "various colours. They seem to be growing from the "+
        "bushes.\n");

    add_item("bushes","The bushes are bright green in colour, and "+
        "perfectly trimmed. There are some small flowers growing "+
        "from them.\n");

    add_item("grass","The blades of grass are all cut to "+
        "exactly the same height, serving almost as a rug "+
        "of sorts. It is a beautiful dark green colour.\n");

    add_prop(ROOM_I_INSIDE,1);
    add_prop(ROOM_I_IS,1);
    add_prop(ROOM_M_NO_ATTACK,"The statues eyes burn with an "+
        "inner fire, and you feel an iron-like grip stay your "+
        "hand until the urge to fight has passed.\n");

    add_exit(WOR_TEMPLE+"archway","north",0,1);
    add_exit(WOR_TEMPLE+"w_chamber","west",0,1);
    add_exit(WOR_TEMPLE+"e_chamber","east","@@spell_banned",1);
    add_exit(WOR_TEMPLE+"s_chamber","south",0,1);
}

int
spell_banned()
{
    if (TP->query_skill(SS_PUNISHMENT) == SPELL_BANNED)
    {
        write("You have been banned from using your spells by the "+
            "Worshippers council, therefore you cannot enter the "+
            "eastern chamber to construct new tools.\n");
        return 1;
    }

    return 0;
}
