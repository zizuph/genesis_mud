#pragma strict_types
#pragma no_clone

#include <stdproperties.h>
inherit "/std/room";

private object *guards = allocate(5);

public void
reset_room()
{
    int i = 5;

    while(i--)
    {
        if(!objectp(guards[i]))
        {
            guards[i] = clone_object("/d/Earthsea/gont/gont_city/liv/guard" + (random(4)+1));
            guards[i]->move(this_object(), 1);
            guards[i]->command("emote marches in.");
        }
    }
}

public void
create_room()
{
    add_prop(ROOM_S_MAP_FILE, "earthsea_map.txt");
    set_short("Guard lookout tower");
    set_long("You are standing in a guard "+
        "lookout tower constructed from large granite blocks. There "+
        "is a window that looks out over the sea to the south "+
        "and east, and another that looks out over the city "+
        "to the north and west. A bronze-topped roof protects "+
        "this outpost from the elements.\n");
    add_item((({"view", "magnificent view", "surrounding area",
        "windows", "window", "east window", "north window",
        "sea", "cliff", "coast", "city", "Gont Port"})),
        "The Armed Cliffs of Gont Port protect the harbour "+
        "from attack. From here you see a magnificent view of the "+
        "dark blue sea and the coast that extends west and "+
        "east from here. The cliff overlooks a white sandy beach "+
        "to the east, where you see waves lapping against the "+
        "shore. To the north you see the activity of Gont Port "+
        "stretching out below with many sailors, guards and "+
        "citizens on their daily business. There are many boats "+
        "at harbour here, but way to the east you see three "+
        "black longships with the sign of Karego At upon their "+
        "sails. Far to the north Gont Mountain stands majestic "+
        "above the city, with its forested flank reaching up to "+
        "a snowcapped peak swathed in clouds.\n");
    add_item(({"ship", "ships", "black ship", "black ships",
        "longship", "longships", "black longship", "black longships"}),
        "The black longships seem to be headed towards the harbour, " +
        "though it seems strange that the watch tower higher up the " +
        "cliff would not have spotted them earlier.\n");
    add_item(({"watch tower", "tower higher up the cliff",
        "watch tower higher up the cliff", "tower up the cliff"}),
        "Though it is hard to see from here, there is a watch " +
        "tower further up the cliff to the southwest.\n");
    add_item((({"tower", "granite tower", "guard tower"})),
        "The granite guard tower looks out over the coast.\n");
    add_exit("e_cliff1", "west");
    reset_room();
}
