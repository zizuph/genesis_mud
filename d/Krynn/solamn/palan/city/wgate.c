/* created by Aridor 07/09/93 */

#include "../local.h"

inherit STREET_BASE

void
create_palan_room()
{
    set_short("Palanthas city gates");
    set_long("These are the gates leading into Palanthas. To your east, into " +
        "the city, you can see a straight street leading towards the center " +
        "of the city. Outside the gates the road leads towards some hills " +
        "in the west.\n");

    OUTSIDE;

    add_exit(ROOM + "street9","east","@@only_unwielded@@", 1);
    add_exit(MOOR,"west",0,1);

    add_item(({"street","city","palanthas"}),
        BS("You can see many houses to your east, which " +
            "you would consider a city. The street you are " +
            "currently standing on leads straight east into " +
            "the city.",SL));
    add_item(({"house","houses"}),BS("These houses all look like they are very " +
        "well kept. You get the impression that things are very well " +
        "under control here, and that you better behave yourself while " +
        "visiting the city.",SL));
    add_item(({"gates","walls"}),BS("These are the gates leading into Palanthas from " +
        "the east. There is a watchtower above the gates, and the city " +
        "walls extend to the north and south from the gate, allowing no " +
        "other access in to the city.",SL));
    add_item(({"watchtower","tower","watch"}),
        BS("From up in this tower you have an excellent view of who is " +
            "approaching the city, and who wants to leave. Of course YOU " +
            "don't have any access to the tower and never will.",SL));
    add_item(({"hills","mountains"}),
        BS("The hills to your west are very much lower than the mountains " +
            "surrounding Palanthas on the south and west sides.",SL));
}

int
only_unwielded()
{
    if (this_player()->query_npc())
        return 0;
    
    if (sizeof(this_player()->query_weapon(-1)))
    {
        write("The guard steps up to you and says:\n" +
            "    You have no access to the city.\n" +
            "    Offensive people are not welcome in the beautiful city of Palanthas.\n" +
            "    No weapons may be wielded within the city limits.\n");
        return 1;
    }
    write("The guard steps aside and says: You may pass. Welcome to the " + 
        "beautiful city of Palanthas. Enjoy your stay.\n");
    return 0;
}
