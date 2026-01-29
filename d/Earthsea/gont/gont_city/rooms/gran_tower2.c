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
        if(!guards[i])
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
    set_short("Guard lookout tower.");
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
        "shore. To the northeast you see the activity of Gont Port "+
        "stretching out below with many sailors, guards and "+
        "citizens on their daily business. There are many boats "+
        "at anchor in the harbour. Looking out the north window, "+
        "you see the village of Re Albi perched on the cliffs overlooking "+
        "the city, and it occurs to you why it is called the Falcon's "+
        "Nest. Some distance to the west where the blue of the "+
        "sea meets the blue of the sky, the hazy dreamlike shape "+
        "of the island of Oranea appears mysterious and swathed in "+
        "mist.\n");
    add_item((({"tower", "granite tower", "guard tower"})),
        "The granite guard tower looks "+
        "out over the coast.\n");
    add_item((({"west", "view west", "oranea", "Oranea"})),
        "Some distance to the west where the dark blue sea meets "+
        "the sky, you make out the dreamlike island of Oranea, "+
        "floating in a sea of mist.\n");
    add_item((({"re albi", "Re Albi", "Falcon's Nest",
        "falcon's nest", "falcons nest"})),
        "To the northwest you see the village of Re Albi perched "+
        "on a cliff overlooking Gont Port, and you realize why the "+
        "name in Hardic means the Falcon's Nest.\n");
    add_exit("w_cliff1", "east");
    reset_room();
}
