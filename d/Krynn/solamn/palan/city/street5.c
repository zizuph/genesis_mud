/* created by Aridor 06/19/93 */

#include "../local.h"

inherit STREET_BASE

void
create_palan_room()
{
    set_short("Palanthas city gates");
    set_long("These are the gates leading into "
        + "Palanthas. Through the gates to the "
        + "northwest you can see people scurrying around, "
        + "whereas the road leading towards the mountains "
        + "in the southeast seems deserted.\n");
    
    add_item(({"gate","gates"}),
        "These are iron gates which can be closed in case of an " +
        "emergency. They are currently open though. The city of " +
        "Palanthas lies just beyond the gates.\n");

    add_exit(ROOM + "street2","northwest", "@@only_unwielded@@", 1);
    add_exit(VINMOUNT,"southeast", 0, 1);
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
            "    Offensive people are not welcome in the beautiful city " + 
            "of Palanthas.\n" +
            "    No weapons may be wielded within the city limits.\n");
        return 1;
    }
    write("The guard steps aside and says: You may pass. Welcome to the " + 
        "beautiful city of Palanthas. Enjoy your stay.\n");
    return 0;
    
}
