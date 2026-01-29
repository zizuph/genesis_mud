// spur_start
// temp start loc for Knights only
// grace
// 1 May 1995

#include "../local.h"
#include <stdproperties.h>

inherit SPURRM;

void
create_spur_room()
{
    SHORT("Sleeping quarters");
    LONG("This large room feels crowded.\n"+
        "   Rows of pallets line the floor, most of them occupied.  "+
        "Exhausted Knights sleep in shifts, their worldly goods "+
        "piled at their feet.  They seem combat-ready even as they "+
        "slumber fully-dressed, with their hands caressing the "+
        "hilts of their weapons and their booted feet twitching "+
        "almost restlessly.\n   If you do not intend to sleep at "+
        "this time, it would be a kindness for you to leave so that "+
        "your fellow Knights might rest undisturbed.\n");
 
    AE(ROOM + "inn", "west", 0);

    ACI("here", "start", "@@do_start");
    AI(({"knights", "knight"}),
        "Loyal and brave, each one, and very tired from the seem"+
        "ingly endless fight against the DragonArmies.\n");
    AI(({"pallet", "pallets"}),
        "They are made of straw and wool. They do not look very "+
        "comfortable, but they are better than sleeping upon the "+
        "stones.\n");
}

int
do_start()
{
    NF("At present quarters are severely limited, so only Knights "+
        "may sleep here.\n");
    if (!MEMBER(TP) && !LAYMAN(TP))
      return 0;
    TP->set_temp_start_location(SPUR_START);
    write("This being wartime, quarters are in short supply, "+
        "but all Knights of Solamnia are welcome.\n"+
        "You will start here when next you enter the campaign, but we "+
        "cannot guarantee you housing in future. Rather, you will have "+
        "to return here each time you wish to start here, and take your "+
        "chances that we will have a pallet for you yet again.\n");
    return 1;
}


